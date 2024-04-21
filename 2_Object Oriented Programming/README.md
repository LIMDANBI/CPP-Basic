# 1. OOP 기본 개념
- 필요한 타입을 설계
- 상태를 나타내는 데이터와 상태를 조작하는 함수를 묶어서 타입을 설계 
- = 보다 안전하고, 사용하기 쉬운 타입을 설계 할 수 있음
- `C`언어는 구조체 안에 함수를 넣을 수 없고, `C++`은 구조체 안에 함수를 넣을 수 있음
- 멤버 함수는 **객체의 개수에 상관없이 코드 메모리에 한 개**만 만들어짐


### 1) 접근 지정자
- 멤버 데이터를 외부에서 직접 접근하면 객체가 잘못된 상태가 될 수도 있음
- 멤버 데이터는 "외부의 잘못된 사용으로부터 보호"하는 것이 안전함
- 구조체는 접근 지정자 생략시 `public`
- 클래스는 접근 지정자 생략시 `private`

|||
|-|-|
|`private`|멤버 함수에서만 접근 가능|
|`public`|모든 함수에서 접근 가능|
|`protected`|멤버 함수와 파생 클래스 멤버 함수에서 접근 가능|

> **캡슐화(Encapsulation)** <br>
\- 멤버 데이터는 private 영역에 두고, 외부의 잘못된 사용으로 부터 보호 <br>
\- 멤버 데이터의 변경은 잘 정의된 규칙을 가진 멤버 함수를 통해서만 변경 가능하도록 함


### 2) Constructor/Destructor
- 생성자는 반환 타입을 표기하지 않고, 값을 반환할 수 없음
- 생성자는 함수 오버로딩을 지원함
- 사용자가 생성자를 한 개도 만들지 않으면 컴파일러가 디폴트 생성자를 제공함
- `malloc`은 생성자를 부를 수 없고, `new`는 생성자를 부를 수 있음
- 객체 생성시, 멤버의 생성자가 먼저 호출되고, 객체 자신의 생성자가 호출됨

||||
|-|-|-|
|생성자|`클래스이름()` 모양의 함수| 객체를 생성할 때 자동으로 호출되는 함수
|소멸자|`~클래스이름()` 모양의 함수| 객체가 파괴 될 때 자동으로 호출되는 함수

# 2. Vector
- C++언어의 표준 라이브러리
- 대부분 템플릿으로 되어 있음
- Standard Template Library
- 크기 변경이 가능한 동적 배열
- 사용법은 배열과 거의 동일함

# 3. member initializer list
- 생성자에서 멤버 데이터를 초기화 할 때는 "멤버 초기화 리스트(member initializer list)"를 사용하는 것이 좋음
- 반드시 member initializer list를 사용해야 하는 경우
    - 멤버 데이터로 **상수나 참조자가 있는 경우** (반드시 초기화 되어야 함)
    - **디폴트 생성자가 없는 타입이 멤버로 있는 경우**

```cpp
class People
{
    std::string name;
    int age;
public:
    People(const std::string& s, int a) : name{s}, age{a} // 이렇게 초기화 하자!!
    {
        // 이렇게 하지말고,
        name = s; // 초기화가 아니라 대입 ..!!
        age = a;
    }
}
```
- 초기화 코드가 놓인 순서가 아니라, 멤버 데이터가 선언된 순서 대로 초기화 됨!!!
```cpp
class Point
{
public:
//	int x;
	int y;
	int x;

	Point() : y{10}, x{y}
	{
	}
};
```
- 선언과 구현 파일로 나누어 클래스를 작성할 때, 멤버 초기화 리스트는 **구현 파일**에 작성
- 생성자 블록 안에서는 멤버에 접근하려면 `this->멤버이름`을 사용해야 함 (멤버 초기화 리스트의 경우는 필요 없음)
- (참고) 컴파일러의 멤버 초기화 리스트를 해석
```cpp
#include <iostream>

int g = 0;

class Point
{
public:
//	int x{0}; // int x = 0;
	int x{++g};
	int y{0};

	Point() {}
	Point(int a)        : x{a} {}
	Point(int a, int b) : x{a}, y{b} {}
};

int main()
{
	Point pt1;     // 0, 0
	Point pt2(1);  // 1, 0

	std::cout << pt1.x << ", " << pt1.y << std::endl;
	std::cout << pt2.x << ", " << pt2.y << std::endl;

	std::cout << g << std::endl; // 1
}
```

# 4. explicit constructor
- Dircet Initialization만 가능하고, Copy Initialization(`=` 사용)은 사용할 수 없음
- "암시적 변환의 용도로 사용될 수 없다" (명시적 변환은 사용가능) = 말이 안되는 코드가 에러가 나도록!!
- 인자의 개수가 없거나 여러 개인 경우도 `explicit`를 붙일 수 있음
- `explicit(bool)` : C++20에서 추가된 문법, 주로 클래스 템플릿을 만들 때 템플릿 인자에 따라서 explicit 여부를 결정하기 위해 사용함

```cpp
class Vector
{
public:
	explicit Vector(int size){}
};

Vector v1(10);   // ok
Vector v2 = 10;  // error
```

# 5. static member
### 1)  static member data
- 프로그램이 처음 시작될 때 (객체를 생성하지 않아도) 메모리에 놓이게 됨
- 객체 생성시 static member data는 객체의 메모리에 포함되지 않음
- 모든 객체가 하나의 static member data를 공유함 (접근 지정자를 사용할 수 있는 전역 변수 느낌)
- `클래스 이름::static멤버이름` 으로 접근 (객체 이름으로 접근하는 것은 가능하지만 권장 x)
- private 영역에 있는 경우, `static 멤버함수`로 접근
- static 멤버 변수의 외부 선언은 구현파일(`.cpp`)에 있어야 함
- 다음의 경우에는 외부 선언 없이 클래스 내부에서 초기화 가능
```cpp
struct Object
{
//	static int data1 = 0; // error
	static int data2;     // ok

	static const int data3 = 0;     // ok
	static constexpr int data4 = 0; // ok
		
	inline static int data5 = 0;
};
```
### 2) static member function
- 객체 없이 호출 가능한 멤버 함수
- 객체이름 또는 클래스이름으로 접근 가능 (클래스 이름으로 접근하는 것을 권장)
- static 멤버 함수에서는 static 멤버(데이터, 함수)만 접근 할 수 있음
- 외부 정의는 구현 파일에 만들어야 함
- static 키워드는 함수 선언부에만 표기해야 함

# 6. this