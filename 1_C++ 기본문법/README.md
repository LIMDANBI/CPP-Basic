# 1. namespace
- 관련된 코드(함수, 구조체, 전역 변수 등)을 묶어서 관리

  = 서로 다른 namespace에서는 동일한 이름 사용 가능
- 하나의 프로젝트를 여러 명의 개발자가 같이 진행할 경우 충돌을 막을 수 있음

### 1) 사용 방법 3가지
1. qualfied name (완전한 이름 사용 - 권장)
```cpp
Audio::init();
```

2. using declaration(선언) 사용
```cpp
using Audio::init;
init(); //ok
reset(); // error
```

3. using directive(지시어) 사용
```cpp
using namespace Audio;
init(); // ok
reset(); // ok
```

### 2) global namespace
- 특정한 namespace에 포함되지 않은 공간
- `::` 은 global을 의미
> `init()` : 열려있는 namespace 검색 > global namespace 검색

> `::init()` : global namespace 검색 > global init()이 없는 경우 에러

### 3) 기타
- namespace는 **중첩**(nested) 될 수 있음
- alias 사용 가능
```cpp
namespce fs = std::filesystem;

fs::create_directory("C:/Test");
```
- cpp 기본 header, src 분리
```cpp
// header
namespace Video{
  void init();
}
```

```cpp
// src
#include "Video.h"
namespace Video{
  void init(){
    
  }
}
```

# 2. iostream (표준입출력)
| | C | C++|
|---|------|------|
|출력 | printf 함수 | std::cout 객체
|변수값 출력| %d, %f 필요 | format 지시어 필요 없음
|특징| | << 를 연속적으로 사용 가능
|개행| `'\n'` | `'\n'` 또는 `std::endl`
|입력| scanf 함수 | std::cin 객체
|특징| 주소를 전달(&tmp) | 주소가 아닌 변수(tmp)로 전달
|헤더파일| `<cstdio>` | `<iostream>`

### 1) io manipulator
- 입출력시의 다양한 출력(입력) 형태를 지정하는 것
- 조정자(조작자) 함수
- `<iostream>`, `<iomanip>` 등의 헤더

|||
|------|------|
|`std::dec`| 변수값을 10진수로 출력 |
|`std::hex`| 변수값을 16진수로 출력|
|`std::setw`| 문자열 출력시 개수 지정|
|`std::setfill`| 공백을 채울 문자 지정 |
|`std::left`| 왼쪽 정렬(align) |

### 2) `std::print`
- C++23에서 추가되는 새로운 출력 함수
- `std::cout`
  - 여러 개 변수 출력 시 코드가 복잡
  - 성능이 느림

```cpp
// g++ 2_iostream.cpp -std=c++2b

#include<print>
int main(){
  int a = 10;
  double b = 3.4;
  std::println("Hi");
  std::println("a = {}, b = {}", a, b);
}
```