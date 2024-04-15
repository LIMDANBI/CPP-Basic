class Vector
{
public:
	explicit Vector(int size){}
};
void foo(Vector v)
{
}

class Object
{
public:
	Object() {}
	explicit Object(int a, int b) {}
};
void foo2( Object obj ) {}

int main()
{
	Vector v1(10);   // ok
	Vector v2 = 10;  // error
	Vector v3{10};   // ok
	Vector v4 = {10};// error 

	v1 = 20; 	// error

	foo(v1); // ok
	foo(10); // error

	Object o1;
	Object o2{};
	Object o3 = {};

	Object o4(1,2);
	Object o5{1,2};
	Object o6 = {1,2};

	foo2({});    // Object obj = {}
	foo2({1,2});
}


