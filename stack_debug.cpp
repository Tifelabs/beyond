#include <iostream>

void a(){
    std::cout << "Function a() called\n";
}

void b(){
    std::cout << "Function b() called\n"
    a()
}

int main(){
    a();
    b();
    return 0;
}