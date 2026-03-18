#include <iostream>

int main(){
    int x = 10;     /* Normal interger */
    int& ref = x;   /* An Lvalue reference to interger x */

    std::cout << x << '\n';
    std::cout << ref << '\n';

    const int y = 5;
    const int& ref2 = y;
    std::cout << y << '\n';
    std::cout << ref2 << '\n';

    y = 25;
    std::cout << y << '\n'; /* Error -> y is a constant */

    return 0;
}