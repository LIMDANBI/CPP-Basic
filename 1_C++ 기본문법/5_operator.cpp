#include <iostream>

int main()
{
	double n1 = 30, n2 = 20;

	bool b1 = (n1 < n2);


	auto ret = (n1 <=> n2); // C++20 

	if ( ret == 0 )
		std::cout << "n1 == n2" << std::endl;

	else if ( ret > 0 )
		std::cout << "n1 > n2" << std::endl;

	else if ( ret < 0 )
		std::cout << "n1 < n2" << std::endl;

    // std::cout << ret << std::endl;
    // data type 출력
	std::cout<< typeid(ret).name() << std::endl; // strong_ordering (weak_ordering, partial_ordering)
}