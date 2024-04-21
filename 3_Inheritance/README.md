# 1. Inheritance basic
- 기존 타입을 확장해서 새로운 타입을 설계하는 문법
- 코드의 중복을 줄일 수 있음
- `upcasting`, `가상함수`, `다형성`, `인터페이스` 등 다양한 개념을 활용해서 객체지향 설계 기술 사용 가능
- 기반 클래스 : Base class (Super class, Parnet class)
- 파생 클래스 : Derived class (Sub class, Child class)
- 생성자는 Base 생성자가 먼저 호출되고, 소멸자는 Derived 소멸자가 먼저 호출됨
- Base 생성자는 별도로 명시해주지 않으면, 항상 인자가 없는 디폴트 생성자가 호출됨
- 디폴트 생성자가 없는 경우, 파생 클래스 생성자에서 "Base class 생성자를 호출하는 코드"를 반드시 작성해야 함 (적는 순서에 상관 없이, base class 생성자가 먼저 실행됨)

- 언어 별 상속 문법

|||
|-|-|
|`C++`| `class Student : public Person`|
|`C#`| `class Student : Person`|
|`JAVA`| `class Student extends Person`|
|`Python`| `class Student(Person)` |

- 접근 지정자

|||
|-|-|
|`private`| 자신의 멤버 함수에서만 접근 가능 (파생 클래스 멤버 함수에서 접근 불가)|
|`protected`| 자신의 멤버 함수와 파생 클래스 멤버함수에서 접근 가능|
|`public`| 모든 함수에서 접근 가능|

```cpp
class Base
{
private:   int a;
protected: int b;
public:    int c;
};

class Derived : public Base
{
public:
    void foo()
    {
        a = 10; // error
        b = 10; // ok
        c = 10; // ok 
    }
};

int main()
{
    Derived derv;
    derv.a = 10; // error
    derv.b = 10; // error
    derv.c = 10; // ok
}
```