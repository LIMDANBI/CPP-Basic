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

# 2. upcasting
- 기반 클래스 포인터로 파생 클래스의 객체를 가리킬 수 있음
- 기반 클래스 포인터로는 기반 클래스의 멤버만 접근할 수 있음
- 파생 클래스의 고유 멤버에 접근하려면 명시적으로 캐스팅 해야함
- 동종을 처리하는 함수, 동종을 보관하는 컨테이너를 사용하는 경우 많이 활용됨

```cpp
class Shape
{
public:
    int color;
};

class Rect : public Shape
{
public:
    int x, y, w, h;
};

int main()
{
    Rect rect;

    Shape* p = &rect; 
    
    p->color = 0; // ok
    p->x = 0;     // error
    static_cast<Rect*>(p)->x = 0; // ok
    
}
```

# 3. virtual function

### 1) `override` 
기반 클래스 멤버 함수를 파생 클래스에서 다시 만드는 것

### 2) `함수 바인딩(function binding)` 
`p->cry()` 표현식을 "어느 함수와 연결"할지를 결정하는 과정

1) static binding (early binding)
    - 컴파일러가 "컴파일 시간에 함수 호출"을 결정
    - 컴파일러는 p가 실제로 어느 객체를 가리키는지는 컴파일 시간에 알 수 없음
    - **따라서, 포인터 타입만을 가지고 함수 호출을 결정**
    - C++, C# (의 non virtual function)
    - 빠르지만, 논리적이지 않음

2) dynamic binding (late binding)
    - 컴파일 시간에 p가 가리키는 곳을 조사하는 기계어 코드를 생성
    - "실행 시간에 p가 가리키는 곳을 조사 후 실제 메모리에 있는 객체에 따라 함수 호출 결정"
    - Java, python 등 대부분의 객체 지향 언어 
    - C++, C#의 virtual function 
    - 느리지만, 논리적임

### 3) virtual function
- 함수 선언부에 `virtual`이 붙은 함수로, 함수 바인딩 시 dynamic binding을 지원함
- ex) `virtual void Draw()`

> 모든 파생클래스의 공통의 특징은 반드시 기반 클래스에도 있어야 한다
(그래야 기반 클래스 포인터 타입으로 객체를 관리할 때, 해당 특징을 사용할 수 있다.)

> 기반 클래스 함수 중 파생클래스가 재정의하게 되는 함수는 반드시 "가상함수로 만들어야" 한다.

```cpp
Shape s; s.Draw(); // Shape::Draw
Rect r;  r.Draw(); // Rect::Draw

Shape* p = &r;     //
p->Draw();         // Shape::Draw
```

### 4) virtual destructor
- 가상 함수를 재정의 할 때는 `virtual`을 붙여도 되고, 붙이지 않아도 되지만, 가독성을 위해 붙이는게 좋음  
- 가상 클래스의 소멸자는 반드시 가상 함수가 되어야 함 (단, 의도적으로 하지 않는 경우도 있음)
- 가상 함수 재정의 시 `override`를 붙이는 것이 안전함 (함수 이름에 오타가 있어도, 새로운 것을 정의한다고 생각하여 에러가 발생하지 않으므로)

```cpp
Base *p = new Derived;
delete p; // Base 소멸자 호출
// 포인터 타입이 아닌 p가 가리키는 메모리를 조사 후 호출해야 함 
// 따라서, 기반 클래스의 소멸자를 가상함수로!!
```

```cpp
void foo(Shape* p, Shape& 1, Shape s){
    p-›draw(); // draw rect 
    r.draw(); // draw rect 
    s.draw(); // draw shape (복사본 객체가 생성되었으므로)
}

int main(){
    Rect r;
    foo(&r, r, r);
}
```

```cpp
// Rect , Circle이 Shpae을 상속 받은 경우
vector<Shape*> v1; // Rect, Circle을 보관하는 벡터
vector<Shape> v2; // Rect, Circle이 아닌, Shape을 보과하는 벡터
```

# 4. abstract class
### 1) pure virtual function (순수 가상 함수) 
구현이 없고, `=0`으로 끝나는 가상함수

### 2) abstract class (추상 클래스) 
순수 가상함수가 한 개 이상 있는 클래스
- 객체를 생성할 수 없음
- 포인터 변수는 만들 수 있음
- 객체를 생성할 수 있게 하려면 반드시 순수 가상함수를 override해서 구현부를 제공해야 함
- 즉 추상 클래스의 의도는, 파생 클래스에게 "특정 멤버 함수를 반드시 만들라고 지시"하기 위한 것

### 3) 가상 함수 vs 순수 가상함수
- 가상 함수 : 파생 클래스가 반드시 재정의할 필요는 없음 (재정의 하지 않으면 기본 구현 제공)
- 순수 가상 함수 : 파생 클래스가 반드시 구현을 제공해야 함

# 5. interface
- "지켜야 하는 규칙(순수 가상함수)"만 가진 것
- abstract class는 "지켜야하는 규칙 + 다른 멤버도 있는 경우"
- 결국 기반 클래스로 사용되므로 반드시 "가상 소멸자" 사용

### 1) Open-Closed Principle (개방-폐쇄 원칙)
- 확장에 대해 열려 있어야하고, 수정에 대해서는 닫혀 있어야 함
- 새로운 요소가 추가 되어도 기존 요소가 변경되지 않도록 설계해야 한다는 원칙

### 2) 강한 결합 vs 약한 결합
- 강한 결합 (tightly coupling)
    - 객체가 다른 객체와 강하게 결합되어 있는 것
    - 교체가 불가능하고 확장성 없는 경직된 디자인
- 약한 결합 (loosely coupling)
    - 객체가 다른 객체와 약하게 결합되어 있는 것 (인터페이스를 사용해서 통신)
    - 교체가 가능하고 확장성 있는 유연한 디자인

# 6.가상함수의 원리
- 가상 함수의 원리는 컴파일러 마다 다를 수 있고, 컴파일러 버전에 따라 다를 수도 있음
- 일반적으로, 객체당 한개의 가상함수 테이블을 가리키는 포인터 멤버를 추가하여 관리함
- 가상함수가 선언된 순서를 가지고 검색하며, 가상 함수 호출 시 주소를 꺼내서 호출하므로 약간의 지연이 발생함
- 인라인 치환은 컴파일 타임에 결정 되고, 어느 가상함수를 사용할지는 실행 시간에 결정되므로 인라인 치환이 될 수 없음
- 디폴트 파라미터는 컴파일 시간에 값을 채우므로 가상함수 override 시에는 절대 디폴트 값을 변경하면 안됨 (가상함수에서는 디폴트 파라미터를 사용하지 않는 것이 좋음)

# 7. RTTI (Run Time Type Information)
- 실행 시간에 객체의 타입을 조사하는 기술
- 특정 조건에서는 컴파일 시간에도 조사 가능
- `#include <typeinfo>` 헤더 사용
- `typeid()` 연산자를 사용해서, `const std::type_info&` 형태로 얻을 수 있음
- `const std::type_info&` 의 경우 사용자가 직접 객체를 만들 수는 없고, const 형태의 반환값으로 참조만 가능
- `const std::type_info&` 객체의 `name()` 멤버함수 사용
- 아래와 같은 식으로 타입 조사
    - `typeid(n1)`
    - `typeid(int)`
    - `typeid(3+4.2)`
- 가상 함수가 없는 경우 (non-polymorphic type) 컴파일 시간에 타입 결정
- 가상 함수가 있는 경우 (polymorphic type) 실행시간에 메모리를 조사해서 결정

```cpp
#include <iostream>
#include <typeinfo>

int main()
{
    auto n1 = 10;
    
    const std::type_info& t1 = typeid(n1);
    const std::type_info& t2 = typeid(int);
    
    if ( t1 == t2 ) // if(typeid(n1) == typeid(int)) 도 가능
    {
        std::cout << "same" << std::endl;
    }
    
    if ( t1.hash_code() == t2.hash_code() )
    {
        std::cout << "same" << std::endl;
    }
    
    std::cout << t1.name() << std::endl;
}
```

`downcsting`
- 기반 클래스 포인터를 파생 클래스 타입으로 캐스팅 하는 것
- 안전하지 않을 수 있음

`static_cast`
- 잘못된 downcasting을 조사 할 수 없음
- 단, 컴파일 시간에 캐스팅을 수행하므로 오버헤드가 없음

`dynamic_cast`
- 잘못된 downcasting을 하면 0 반환 
- 실행시간에 캐스팅을 수행하므로 약간의 오버헤드가 있음
- 반드시 하나 이상의 가상 함수를 가져야 사용할 수 있음