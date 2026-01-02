#include <iostream>

int main(){
    /* Testing the difference between const char[] and const char *ptr */

    const char plane[] = "SR71 - Blackbird";
    const char *aircraft = "Black Hawk";

    std::cout << "This works -> " << plane << '\n';
    std::cout<< "This also works --> " << aircraft << '\n';

    std::cin.get();
}