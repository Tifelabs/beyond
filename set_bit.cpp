#include <iostream>
#include <cstdint>

int main(){

    constexpr uint8_t mask0{1 << 0}; // bit 0
    constexpr uint8_t mask1{1 << 1}; // bit 1
    constexpr uint8_t mask2{1 << 2}; // bit 2
    constexpr uint8_t mask3{1 << 3}; // bit 3
    constexpr uint8_t mask4{1 << 4}; // bit 4
    constexpr uint8_t mask5{1 << 5}; // bit 5
    constexpr uint8_t mask6{1 << 6}; // bit 6
    constexpr uint8_t mask7{1 << 7}; // bit 7

    std::uint8_t flags{0b0000'0101};

    std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");
    flags |= mask1;
    std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

    return 0;
}