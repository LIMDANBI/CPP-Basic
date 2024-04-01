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