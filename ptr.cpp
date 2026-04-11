#include <iostream>

int main(){
    short value = 7;
    short otherValue = 3;

    short *ptr = &value;
    
    std::cout << &value << '\n';
    std::cout << value << '\n';
    std::cout << ptr << '\n';
    std::cout << *ptr << '\n';
    return 0;
}