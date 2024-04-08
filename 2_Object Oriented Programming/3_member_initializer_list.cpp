#include <string>

class People1
{
	std::string name;
	int age;
public:
	People1(const std::string& s, int a) 
	{
		name = s; // 대입
		age = a;
	}
};

class People2
{
	std::string name;
	int age;
public:
	People2(const std::string& s, int a) 
			: name{s}, age{a} // 초기화
	{
	}
};

class Point
{
	int x;
	int y;
public:
	Point(int a, int b) : x{a}, y{b}
	{
	}
};

class Rect
{
	Point leftTop;
	Point rightBottom;
public:
	Rect(int x1, int y1, int x2, int y2)
		: leftTop{x1, y1}, rightBottom(x2, y2)
	{
	//	leftTop(x1, y1);
	}
};

int main()
{
	std::string s{"kim"};

	People1 p1(s, 20);
	People2 p2(s, 20);


    // Rect 생성자를 부르면, Point 생성자도 자동으로 불린다!!!
    Rect r(1,1,10,10);
}

