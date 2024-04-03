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

# 3. variable (변수)

### 1) auto , decltype

 > `auto` : 변수 선언시, **우변의 표현식을 조사**하여 컴파일러가 타입을 결정

 > `decltype` : **괄호 안의 표현식**으로 타입을 결정 (함수 템플릿 등을 만들 때 주로 사용)
```cpp
int n = 10;
decltype(n) n1; // int n1;
```

```cpp
int x[5] = {1, 2, 3, 4, 5};

auto a = x; // int* a = x; 
// not int a[5] = x;

decltype(x) d; // int d[5];
decltype(x) d1 = x; // error
```

> type deduction (inference)
: 주어진 **표현식을 보고 컴파일러가 타입을 결정**하는 과정

### 2) `using`
- `typedef` : type에 대한 별칭
- `using` : type에 대한 별칭 + **template에 대한 별칭**

```cpp
using DWORD = int; // typedef int DWORD;
using PF = void(*)(int); // typedef void(*PF)(int);

DWORD n; // int n
PF p; // void(*p)(int)
```

### 3) Uniform Initialization (일관된 초기화)
- 모든 종류의 변수를 한가지 방법으로 초기화
- 중괄호 초기화(brace-init) 이라고도 부름
- Direct Initialization(직접 초기화) : `=` 없이 초기화 하는 것
- Copy Initialization(복사 초기화) : `=`을 사용해서 초기화 하는 것

```cpp
// Direct Initialization
int   x3[3]{1,2,3};

// Copy Initialization
int   x2[3] = {1,2,3};
```

### 4) C와 다른 C++ 구조체
- 구조체 멤버에 디폴트 초기값 지정 가능
- 구조체 변수 선언시 `struct` 키워드를 표기하지 않아도 됨
- 아래와 같이 요소의 값을 한줄에 꺼낼 수 있음
```cpp
auto [x, y] = pos1

int arr[3] = {1,2,3};
auto [a, b, c] = arr;
```

### 5) C++ 타입/변수 특징
- `0b` : 2진수 표기
- `0x` : 16진수 표기
- `nullptr` 로 포인터 초기화 (C++11 부터!)