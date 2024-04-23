#include <print>

class Point
{
public:
	int x{0};
	int y{0};
	Point() = default;
	Point(int x, int y) : x{x}, y{y} {}	

	Point& operator=(const Point& other) 
	{
		if (&other == this) return *this; // (안해도 괜찮지만) 자신과의 대입은 실행 x 예외 처리
		
		x = other.x;
		y = other.y;

		return *this;
	}
};

int main()
{
	Point p1{1,2};
	Point p2;

	p2 = p1;	// p2.operator=(p1)
	(p2 = p1) = p1;

	p2 = p2;

	std::println("{}, {}", p2.x, p2.y);

	int n = 0;

	(n = 10) = 20;

}