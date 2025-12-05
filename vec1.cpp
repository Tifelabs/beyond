#include <iostream>
#include <vector>

int main(int argc, char *argv[]){
    std::vector<float> prices = {10.0f, 90.05f, 44.3f};
    std::cout << "Size of Prices Before Modification: -> " << prices.size() << '\n';
    
    prices.push_back(4.75f);
    prices.push_back(55.2f);
    
    std::cout << "ELEMENTS\n";
    for(const auto& x : prices){
        std::cout << "$" << x << '\n';
    }
    std::cout << "\nSize of Prices After Modification: -> " << prices.size() << '\n';

    std::cin.get();
    return 0;
}