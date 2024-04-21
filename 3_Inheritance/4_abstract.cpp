class Shape
{
public:
	virtual ~Shape() {}	

	virtual void draw() = 0;
};

class Rect : public Shape
{
public:
	virtual void draw() {}
};

int main()
{
//	Shape  s;	// error	
	Shape* p;	// ok

    Rect r;
}