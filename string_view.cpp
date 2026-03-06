#include <iostream>
#include <string_view>

void printSV(std::string_view str){
    std::cout << str << "\n";
}

int main(){
    std::string_view s = "Testing String View\n";
    printSV(s);

    std::string_view fruit {"Watermelon"};
    std::cout << fruit << '\n';

    fruit.remove_prefix(1);
    std::cout << fruit << '\n';

    fruit.remove_suffix(2);
    std::cout << fruit << '\n';
    return 0;
}