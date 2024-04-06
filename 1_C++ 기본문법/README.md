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

 > `auto` : 변수 선언시, **우변의 표현식을 조사**하여 컴파일러가 타입을 결정 (초기값 주지 않으면 error)

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

# 4. function (함수)

### 1) default parameter 
- 함수 호출시 인자를 전달하지 않으면, 미리 지정된 인자값을 사용
- 함수의 마지막 인자부터 차례대로 디폴트 값을 지정 해야 함
- 함수를 선언과 구현으로 분리할 때는 **함수 선언부에만 티폴트 값을 표기**해야함
- 컴파일러가 컴파일 시에 함수 호출하는 코드의 함수 인자에 디폴트 값을 채워 주는 방식으로 동작

### 2) overloading
- 인자의 개수나 인자의 타입이 다르면, 동일한 이름의 함수를 여러 개 만들 수 있음 (반환 타입만 다르면 x)
- default parameter가 있는 경우는 주의! (함수 호출 시 컴파일러가 함수 인자로 보고 어느 함수가 호출될지 명확히 결정할 수 있어야 함)
- 컴파일러가 컴파일 시간에 함수의 이름을 변경하는 방식으로 동작 (`name mangling`)
> ex) `A`라는 이름의 함수를 C로 컴파일 시 `A` 그대로, C++로 컴파일 시 `_Z6Ai`와 같이 이름 변경

### 3) C/C++ 호환성 문제
- 파일별로 각각 컴파일 후, 생성된 `.o`(`.obj`) 파일을 링커가 결합
- cl, gcc 등의 컴파일러는 **확장자에 따라 언어를 결정**
- overloading의 원리인 `name mangling` 때문에 C/C++ 호환성 문제 발생 
- `extern "C"` : 함수(변수)가 C언어로 작성된 것임을 C++ 컴파일러에게 알려줄 때 사용 (name mangling 발생 방지)
- C 컴파일러는 `extern "C"`를 알지 못함 > 하나의 헤더 파일을  C/C++에서 모두 사용하려면 아래와 같이 **조건부 컴파일**을 해야함.

```h
#pragma once 

#ifdef __cplusplus
extern "C" {
#endif

	int square(int);

#ifdef __cplusplus
}
#endif
```

### 4) template
- 함수 오버로딩 시, 인자 타입과 반환 타입만 다르고, **구현이 동일(유사)한 함수를 여러개 만들어야 한다는 단점**이 존재
- 구현이 동일(유사)한 함수가 여러 개 필요하면 함수를 만들지 말고 함수를 생성하는 틀(템플릿)을 만들 수 있음
- template을 사용해서 컴파일러가 실제 함수를 생성하는 과정을 **template instantiation (템플릿 인스턴스화)** 라고 부름
- 함수 템플릿을 만들고 사용하지 않으면, 실제 함수는 생성(인스턴스화) 되지 않음 !!

```cpp
//template<typename T> 
template<class T> // 위와 완전히 동일
T square(T a)
{
	return a * a;
}

int main()
{
	square<int>(3);
	square<double>(3.4);

  // type deduction
  // 컴파일러가 함수 인자를 보고 타입을 추론
  square(3);
  square(3.4f);

  // 함수와 함수 템플릿
  printf("%p\n", &square); // error (square는 함수가 아닌 틀. 주소를 구할 수 없음)
  printf("%p\n", &square<int>); // ok (함수. 주소를 구할 수 있음)
}
```

> \* `코드 폭발(Code Bloat)` : 템플릿이 너무 많은 타입에 대해 인스턴스화 되어서 코드 메모리가 증가하는 현상

### 5) inline function
- 빠르다는 장점이 있지만, 크기가 큰 함수를 여러 번 치환하면 목적코드(실행 파일)이 커질 수 있음
- 크기가 작은 함수는 인라인 치환시 목적코드를 줄이기도 함
- 인라인 치환을 적용 하려면 `/Ob1` 옵션 사용

|||
|--|--|
|일반 함수 호출 | 함수인자를 약속된 장소에 넣고(`32bit-stack`/`64bit-register`), 함수로 이동
|인라인 함수 호출 | 함수 호출 코드를 함수의 기계어 코드로 치환

```cpp
inline int Add(int a, int b){
  return a + b;
}
```

### 6) linkage (연결)
- 인라인함수와 함수템플릿은 **함수 구현 자체를 헤더 파일**에 넣어야 함!!
- 어느 파일이 먼저 컴파일 될 지 알수 없기 때문에, 함수의 구현을 알 수 없을 수 있음  ex) test.h , test.cpp , using_test.cpp 

|||
|----|-----|
|internal linkage|심볼(함수, 변수이름)이 선언된 같은 컴파일 단위에서만 사용 가능 (인라인 함수, 템플릿)|
|external linkage|프로젝트 내의 모든 컴파일 단위애서 사용 가능 (일반 함수, 전역 변수 등)|

### 7) suffix return type (후위 반환 타입)
- 함수의 반환 타입을 함수의() 뒤쪽에 적는 표기법
- 후위 반환 타입 표기법이 반드시 필요한 경우가 있음
  - 복잡한 형태의 함수 템플릿
  - 람다 표현식

```cpp
auto add(int a, int b) -> int {
  return a + b;
}
```

```cpp
// error 
// 모든 변수는 선언 후에 사용되어야 함
template<class T1, class T2>
decltype(a+b) add(T1 a, T2 b){
  return a + b;
}

// suffixt return type
template<class T1, class T2>
auto add(T1 a, T2 b) -> decltype(a + b)

// C++14부터 지원
auto add(T1 a, T2 b){
  return a + b;
}
```

### 8) delete function
- class 문법에는 사용자가 만들지 않으면 컴파일러가 자동으로 생성하는 함수가 있음
- 컴파일러에게 자동 생성하는 함수를 만들지 못하게 하고 싶을 때 주로 사용

```cpp
int gcd(int a, int b)
{
	return b != 0 ? gcd(b, a % b) : a;
}

//double gcd(double a, double b); // 구현이 없다. 선언만

double gcd(double a, double b) = delete; // C++, 함수 삭제

int main()
{
	gcd(10, 4);

	gcd(3.3, 4.4); // 암시적 형 변환으로 gdc(int, int) 호출 될 수 있음 -> delete
}
```

### 9) C++ STL(Standard Library)
- `iterator` : 요소를 가리키는 포인터 역할의 객체(변수)

### 10) lambda expression
- 익명의 함수(객체)를 만드는 문법
- 함수이름(주소)가 필요한 위치에 함수 구현자체를 표기할 수 있는 문법
- 후위 반환 표기법(suffix return type) 사용, 컴파일러가 리턴 타입을 추로 할 수 있는 경우 생략 가능
- auto 변수에 담아서 함수처럼 사용 가능
- **람다 표현식을 사용하는 이유** :  특정 상황에서 일반 함수보다 빠르고, 지역변수를 캡쳐할 수 있는 능력이 있음 
- `[]` 기호 : 람다표현식이 시작됨을 알리는 lambda introducer
- `std::for_each` : 구간의 모든 요소를 마지막 인자로 전달된 "단항함수에 차례대로 전달"
  - 단항 함수 : 인자 1개
  - 이항 함수 : 인자 2개

```cpp
int x[5] = {1, 2, 3, 4, 5};
std::sort(x, x+5, [](int a, int b) ->  bool {return a>b;});
std::sort(x, x+5, [](int a, int b){return a>b;}); // return type 생략

auto add = [](int a, int b){return a+b;};
int ret = add(1, 2);

// 지역 변수 캡쳐
int pass = 70;
int score[5] = {95,35, 63, 72. 22};
for_each(score, score+5, [pass](int n){
  if(n < pass) cout << n << "\n";
})
```

# 5.연산자와 제어문

### 1) `range-for`문
- C++11부터 지원되는 새로운 형태의 for문
- 배열 뿐 아니라 다양한 STL 컨테이너에도 사용 가능

```cpp
for ( auto n : arr)
```

### 2) `std::views`
- C++20부터 제공
- `#include <ranges>`
- `std::views` namespace 안에 다양한 함수 제공

```cpp
#include <ranges>

for(auto a : std::views::reverse(arr)); // 거꾸로
for(auto a : std::views::take(arr, 3)); // 처음 3개
for(auto a : std::views::drop(arr, 3)); // 처음 3개 제외
for(auto a : std::views::filter(arr, func)); // 특정 조건 만족
```

### 3) init if
```cpp
// 기존
int ret = foo();
if(ret == 0) {}

// 이후
if (init ret = foo(); ret == 0){}
```

### 4) new
- 배열 형태로 메모리 할당한 경우 반드시 `delete[]` 로 해야 함
- `delete`로 해지할 경우 undefined(미정의 동작) 발생

| | C (malloc) | C++ (new) |
|---|------|------|
|정체| 함수 | 연산자 (키워드)
|인자| 할당할 메모리 크기 | 타입
|반환타입| `void*` (원하는 타임으로 캐스팅 필요) | 전달한 타입의 포인터 (캐스팅 필요 없음)
|해지방법| `free` | `delete` 또는 `delete[]`
|생성자| 호출 안됨 | 호출됨

### 5) three way comparison
- C++20부터 등장
- 0과 크기 비교만 가능함 
  - `0(같음)`
  - `양수(좌측이큼)`
  - `음수(우측이큼)`
- 어떤 타입을 비교하는지에 따라 반환 타입이 달라짐
  - strong_ordering
  - weak_ordering
  - partial_ordering

```cpp
bool res = (n1 <=> n2);

// data type 출력
std::cout<< typeid(ret).name() << std::endl; // strong_ordering
```

# 6. reference
- 이미 존재하는 변수(메모리)에 대한 추가적인 `별칭(alias)`을 부여 하는 분법
- `&` 연산자
  - 변수의 **주소를 구할** 때
  - 레퍼런스 변수를 **선언**할 때 
```cpp
int n = 10;
int* p = &n; // pointer
int& r = n; // reference
```

- 함수 인자로 reference를 사용하면 포인터보다 간결하고 안전하게 코드를 작성할 수 있음 

```cpp
int* p =  0; // null 포인터 있음
int & r; // error (null 참조 없음)
```

- `scanf("%d", &n);` : call by pointer
- `std::cin >> n;` : call by reference
- `const reference`
  - 복사본에 대한 오버헤드 없이 인자로 전달된 변수를 수정하지 않겠다는 약속
  - C++에서 가장 널리 사용되는 인자 전달 방식

```cpp
struct Rect
{
	int left;
	int top;
	int right;
	int bottom;
};

void f1(Rect r)        {}
void f2(const Rect& r) {} // 좋은 코드 

void f3(int n)        {} // 좋은 코드
void f4(const int& r) {}
```
- user define type의 경우, 일반적으로 타입의 크기가 크므로 call by reference 추천
- primitive type의 경우, 타입의 크기가 크지 않고 생성자 개념이 없으므로 call by value 추천

# 7. `nullptr`
- `null pointer`를 나타내는 literal, keyword
- 모든 타입의 포인터 변수를 초기화 하는 데 사용 가능
- 정수(실수) 초기화에 사용될 수는 없음
- bool 변수 직접 초기화와 조건문에 사용될 수 있음
- 모든 literal은 타입이 있음
- `std::nullptr_t`은 모든 타입의 포인터로 암시적 형변환 됨

||||
|-|-|-|
|`0`|정수형 리터럴|int|
|`0.0`|실수형 리터럴|double|
|`false`|bool형 리터럴(키워드)|bool|
|`nullptr`|포인터형 리터럴(키워드)|`std::nullptr_t`|

> \* 앞으로 포인터 변수를 초기화 할 때는 `0`을 사용하지 말고, `nullptr`을 사용하자!!

