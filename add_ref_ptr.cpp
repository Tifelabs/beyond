#include <iostream>
#include <string>

void passByVal(std::string val){
    std::cout << val << '\n';
}

void passByRef(const std::string& ref){
    std::cout << ref << '\n';
}

void passByAddress(const std::string *ptr){
    std::cout << *ptr << '\n';
}

int main(){
    std::string str = "Testing";

    passByVal(str);
    passByRef(str);
    passByAddress(&str);
    return 0;
}