#include <iostream>
#include <cstdint>

int main() {
    int* y = nullptr;
    std::cout << "This is: " << (y ? "Not Null\n" : "Null\n");
    return 0;
}
