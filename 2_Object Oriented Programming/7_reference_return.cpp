
struct Point
{
	int x;
	int y;
};
Point pt = {1, 2};

Point f1()  // return by value
{
	return pt; // 리턴용 임시 객체가 생성되어 반환됨
}
Point& f2() // return by reference
{
	return pt;
}
int main()
{
//	f1().x = 10; // 리턴용임시객체.x = 10
				 // error
	f2().x = 10; // pt.x = 10   ok.
}