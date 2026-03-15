#include <iostream>
#include <vector>

void passByRef(const std::vector<int> &arr){
    std::cout << arr[2] << "\n";
    for(const auto& x: arr){
        std::cout << &(x) << "\n";
    }
}

int main(){
    std::vector<int> even {2, 4, 6, 8, 10, 12};
    passByRef(even);
    return 0;
}