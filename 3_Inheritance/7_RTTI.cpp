#include <iostream>
#include <typeinfo>

class Animal 
{
public:
    virtual ~Animal() {} // 가상함수 o -> 실행시간에 타입 조사
};

class Dog : public Animal 
{
public:
    int color;
};

void foo(Animal* p)
{
    //const std::type_info& t = typeid(p);
    const std::type_info& t = typeid(*p);
    std::cout << t.name() << std::endl;
    

    // downcasting 
    // 기반 클래스 포인터를 파생 클래스 타입으로 캐스팅 하는 것
    // Dog* pDog = static_cast<Dog*>(p);

    // 1. typeid 이용
    if ( typeid(*p) == typeid(Dog))
    {
        Dog* pDog = static_cast<Dog*>(p);
        pDog->color = 10;
        std::cout << "Dog" << std::endl;
    }

    // 2. dynamic_cast 이용
    Dog* pDog = dynamic_cast<Dog*>(p);
    
    if ( pDog != 0 )
    {
        pDog->color = 10;
    }
    std::cout << pDog << std::endl;
}

int main()
{
    Animal a; foo(&a);
    Dog    d; foo(&d);    
}