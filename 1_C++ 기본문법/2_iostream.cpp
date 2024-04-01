#include<iostream>
#include<iomanip>
#include<print>

int main(){

    int n = 10;

    std::cout << n << "\n";

    // "%x" (계속 적용됨)
    std::cout << std::hex << n << "\n";

    std::cout << n << "\n";

    // "%d" (다시 10진수로 바꿔줌)
    std::cout << std::dec << n << "\n";

    // 10########
    std::cout << std::setw(10) << std::setfill('#') << std::left  << n  << "\n";

    // g++ 2_iostream.cpp -std=c++2b
    int a = 10;
    double b = 3.4;
    std::println("Hi");
    std::println("a = {}, b = {}", a, b);
}