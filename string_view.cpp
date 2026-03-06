#include <iostream>
#include <string_view>

void printSV(std::string_view str){
    std::cout << str << "\n";
}

int main(){
    std::string_view s = "Testing String View\n";
    printSV(s);
    return 0;
}