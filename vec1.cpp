#include <iostream>
#include <vector>

int main(int argc, char *argv[]){
    std::vector<float> prices = {10.0, 90.05, 44.3};
    const ElementSize = prices.size();
    std::cout << "Size of Prices Before Modification\n:";
    std::cout << ElementSize;

    /* Adding Price to the Front */
    prices.front() = 10;

    for(const auto& x : prices){
        std::cout << x << '\n';
    }
}