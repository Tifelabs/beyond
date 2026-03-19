#include <iostream>

int main(){
    int x = 15;
    int& ref = x;
    int* ptr;
    ptr = &x;

    std::cout << "The value of x is: " << x <<'\n';
    std::cout << "The memory address of x is : " << &x << '\n';
    std::cout << "Dereferencing x: " << *(&x) << '\n';
    std::cout << "Pointer to x: " << ptr << '\n';

    return 0;
}