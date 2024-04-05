#include<iostream>
#include <algorithm>

void inc1(int  n) { ++n;}
void inc2(int* p) { ++(*p);}
void inc3(int& r) { ++r;}

// C 언어
void swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

// C++
namespace utils
{
	template<class T>
	inline void swap(T& r1, T& r2)
	{
		T temp = r1;
		r1 = r2;
		r2 = temp;
	}
}

int main()
{

// # example 1
	int a = 10, b = 10, c = 10;

	inc1(a);
	inc2(&b);
	inc3(c);

	std::cout << a << std::endl; // 10 (call by value)
	std::cout << b << std::endl; // 11 (call by pointer)
	std::cout << c << std::endl; // 11 (call by reference)

// # example 2
    int x = 10, y = 20;

    // swap(&x, &y);
    // utils::swap(x, y);
	std::swap(x, y);

	std::cout << x << std::endl; // 20
	std::cout << y << std::endl; // 10
}