#include<iostream>

struct Point
{
	int x;
	int y;
};

int main()
{
	int x[5] = {1, 2, 3, 4, 5};

	auto a = x;

	decltype(x) d;
	// decltype(x) d1 = x; // error


	// uniform initialization
	int   n1 = 0;
	Point p1 = {0, 0};
	int   x1[3] = {1,2,3};

	int   n2 = {0};
	Point p2 = {0, 0};
	int   x2[3] = {1,2,3};	

	int   n3{0};
	Point p3{0, 0};
	int   x3[3]{1,2,3};		

	// prevent narrow
	int n1 = 3.4;   // ok

	int n2{3.4};	// error
	int n3 = {3.4};	// error

	char c{500};	// error
}