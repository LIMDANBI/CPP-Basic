#include <iostream>

class Point
{
public:
	int xpos, ypos;

	Point(int x, int y) : xpos{x}, ypos{y} {}

	void set(int x, int y) 
	{
		xpos = x;
		ypos = y;
	}
	void print() 
	{
		std::cout << xpos << ", " << ypos << std::endl;
	}
};

class Rect
{
	int x, y, w, h;
public:
	Rect(int x, int y, int w, int h)
		: x{x}, y{y}, w{w}, h{h} { } 

//	int getArea() { return w * h;} // 틀린 코드..
	int getArea() const { return w * h;}
};

//void foo(Rect r) // call by value : 복사본 오버헤드
void foo(const Rect& r)
{
	int area = r.getArea(); // ????
}



int main()
{

// 예시 1
//	Point pt(1, 2);
	const Point pt(1, 2);

//	pt.xpos = 10;   // error. public 이지만 상수이므로
//	pt.set(10, 20); // error. 
	pt.print();     // error (함수의 선언만으로 멤버의 값을 변경하는지 알 수 없음)

// 예시 2
	Rect r(1,1,10,10);  // 상수객체 아님.
	int area = r.getArea(); // ok.
	foo(r);
}