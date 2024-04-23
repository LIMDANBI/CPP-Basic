#include <print>

class Point
{
public:
	int x{0};
	int y{0};
	Point() = default;
	Point(int x, int y) : x{x}, y{y} {}	

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
};
int main()
{
	Point p{1,1};

	++++p; // ++(++p) (p.operator++()).operator++()

	std::println("{}, {}", p.x, p.y);
}