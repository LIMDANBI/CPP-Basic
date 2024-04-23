# 1. Operator overloading
사용자 정의 타입의 객체에 대해서도 `+`, `-` 등의 연산자를 사용할 수 있게 하는 문법

### 1) a + b를 컴파일러가 해석하는 방법
- a, b가 모두 `primitive type`(int, double 등)인 경우, 미리 정해진 방식으로 덧셈 수행
- a, b 중 한 개라도 `사용자 정의타입`이 있는 경우, `operator+`라는 이름을 가진 약속된 함수를 호출하고, 없는 경우, + 연산을 할 수 없다는 에러 발생

### 2) `operator+`를 만드는 2가지 방법

1. 멤버가 아닌 함수로 구현 `operator+(p1, p2)`
    - 멤버가 아닌 함수에서 멤버 데이터인 x, y에 접근하려면,
    - x, y를 public 영역에 선언
    - `get_x()`, `get_y()` 멤버 함수 제공
    - `operator+`를 `friend` 함수로 등록

```cpp
class Point
{
	int x{0};
	int y{0};
public:
	Point() = default;
	Point(int x, int y) : x{x}, y{y} {}

	friend Point operator+(const Point& p1, const Point& p2);
};

Point operator+(const Point& p1, const Point& p2)
{
	Point pt{p1.x + p2.x, p1.y + p2.y};
	return pt;
}

int main()
{
	Point p1{1, 1};
	Point p2{2, 2};

	Point p3 = p1 + p2;	// operator+(p1, p2)
}
```

2. 멤버 함수로 구현 `p1.operator+(p2)`
    - `+` 연산자는 이항 연산자이지만, `operator+` 멤버 함수의 인자는 1개임
    - 상수 객체도 덧셈을 할 수 있어야 하므로, const member function으로 구현

```cpp
class Point
{
	int x{0};
	int y{0};
public:
	Point() = default;
	Point(int x, int y) : x{x}, y{y} {}

	Point operator+(const Point& p) const
	{
		Point pt{p.x + x, p.y + y};
		return pt;
	}
};

int main()
{
	const Point p1{1, 1};
	Point p2{2, 2};

	Point p3 = p1 + p2;	// p1.operator+(p2)
}
```

> 멤버 함수와 멤버가 아닌 함수를 모두 제공하면, 컴파일 에러가 발생 (반드시 둘 중 한 개만 제공해야 함)

> private 멤버에 접근하기에는 멤버함수가 좋지만, 첫번째 인자가 사용자 정의 타입이 아닌 경우는 멤버 함수로 반들 수 없음!! ex) `(int).operator+(Point)` 불가

> `+=`의 경우, 자신이 변경되므로, 비상수 함수로 재정의 해야함!
```cpp
class Point
{
	int x{0};
	int y{0};
public:
	Point() = default;
	Point(int x, int y) : x{x}, y{y} {}

	// p1 이 상수 객체라도 "p1 + p2" 할수 있어야 한다. 상수 멤버 함수로 작성
	Point operator+(const Point& p) const
	{
		Point pt{p.x + x, p.y + y};
		return pt;
	}

	// p1 이 상수 객체라면 "p1 += p2" 는 할 수 없다. "비 상수" 멤버 함수로 작성.
	Point& operator+=(const Point& p)
	{	
		x += p.x;
		y += p.x;
		return *this;
	}
};

int main()
{
	const Point p1{1, 1};
	Point p2{2, 2};


	auto ret = p1 + p2; // ok
						// p1.operator+(p2)

	p1 += p2;	// p1이 수정되어야 함.
				// error. 나와야 함
				// p1.operator+=(p2)
}
```

### 3) 연산자 재정의 주의 사항
1. 인자가 모두 primitive type인 경우는 overloading 할 수 없음 (혼란은 야기하므로,,)
2. 인자의 개수를 변경할 수 없음
3. 디폴트 파라미터를 사용할 수 없음
4. 새로운 연산자를 만들 수 없음
5. `[]`, `()` `->`, `=` 연산자는 멤버 함수로만 만들 수 있음
6. `.`, `.*`, `::`, `?:`, `sizeof`, `typeid`, `static_cast`, `dynamic_cast`, `reinterpret_cast`, `const_cast` 는 재정의 할  수 없음
7. 연산자 우선순위는 변경할 수 없음 (ex, 덧셈 보다 곱셈이 앞서는 것)
8. `+`와 `=`을 모두 재정의해도, `+=`이 자동 지원되는 것은 아님 (별도로 정의해야함)

# 2. Increment Operator
- 멤버 데이터를 수정해야 하므로 일반적으로 멤버 함수로 구현

### 1)  연산자 재정의 시 유의 사항
1. 전위형(`++p`)과 후위형(`p++`)을 구별해야함 
    - 후위형을 만들 때는 ㅎ마수 인자로 `ipt` 타입을 한개 가짐
    - 사용되지는 않지만, 전위형과 구별하기 위해
2. 전위형은 `++++p` 표현식이 가능해야 함
    - 자기 자신을 참조로 반환해야 함
    - 값을 반환하면 임시 객체가 생성됨
    ```cpp
    Point& operator++() // 참조 반환 !!
	{
		++x; ++y;	
		return *this; // 증가 후 값
	}
	Point operator++(int) // 값 반환 !!
	{
		Point temp = *this;
		++x; ++y;	
		return temp; // 증가 이전 값
	}
    ``` 
3. 후위형은 전위형을 사용해서 구현
    - 정책을 관리하는 코드는 한 곳에 있는 것이 좋음
    ```cpp
    Point& operator++()
	{
		++x; ++y;	
		return *this;
	}
	Point operator++(int)
	{
		Point temp = *this;
		//++x; ++y;	
		++(*this); // this->operator++()
		return temp;
	}
    ```
4. 전위형보다 후위형이 빠름
    - 반환 값을 사용하지 않고, 단순히 증가만 한다면 전위형을 사용하는 것이 좋음
    - 그런데, 요즘 컴파일러는 코드의 문맥을 파악해서 동일한 기계어 코드를 생성해줌 (최적화)

# 3. Assignment Operator

### 1) 복사 생성자
객체를 생성할 때 초기화 하는 것
```cpp
Point p3(p1);
Point p3 = p1;
```

### 2) 대입 연산자
객체를 생성 후에 값을 넣는 것
```cpp
p2 = p1; // p2.operator=(p1);
```

### 3) 연산자 재정의 시 유의 사항
- 멤버 함수로만 만들 수 있음
- 자신을 참조로 반환해야 함 (반환 된 값에 또 다시 대입 가능하도록)
- 자신과의 대입을 조사

### 4) 컴파일러 기본 제공
- 사용자가 만들지 않으면 컴파일러가 "모든 멤버를 복사"하도록 기본 구현 제공
- 일반적인 경우는 컴파일러 제공버전을 사용해도 되지만, 클래스 안에 포인터 멤버 등이 있으면 주의 해야 함
- 컴파일러가 대입 연산자를 만들지 못하게 하려면 함수 삭제(`delete`) 문법 사용
```cpp
Point& operator=(const Point&) = delete;
```

> `n=10` 의 결과가 다시 n이 나오는 것이 과연 좋을까? `if(n = 10)` 의 널리 알려진 버그 발생 가능성 존재 <br>
=> C++은 자신을 참조로 반환하는 것이 원칙이지만, 요즘 나오는 많은 새로운 언어는 `void` 반환

# 4. Conversion Operator
- 객체의 유효성을 if문으로 조사할 수 없을까?
- = 객체가 bool로 변환 가능해야함

### 1) 변환 연산자
- 객체가 다른 타입으로 변환이 필요할 때 호출되는 함수
- 반환 타입을 표기 하지 않음 (함수 이름 자체에 반환 타입 포함)
- 객체의 변환은 의도하지 않은 side effect가 많으므로, 되도록 `explict`를 붙이는 것이 좋음
- `explicit` 변환 연산자
    - 직접 초기화와 명시적 변환만 허용
    - 암시적 변환 허용 안됨
    - if 조건식 안에서는 사용 가능 (명시적 캐스팅 없이 가능)
- `nullptr` -> `bool` 반환 : `explicit operator bool()`과 동일하게 동작 
```cpp
class TcpConnect
{
	int state{0};
public:
	void connect() { } 

	operator bool() const 
	{
		return state != 0;
	}	
};

int main()
{
	TcpConnect tcp;
	tcp.connect();

	if ( tcp ) // tcp.operator bool()
	{
	}
}
```