#include <iostream>
#include <cstdint>

int main(){

    constexpr std::uint8_t mask0{1 << 0}; // bit 0
    constexpr std::uint8_t mask1{1 << 1}; // bit 1
    constexpr std::uint8_t mask2{1 << 2}; // bit 2
    constexpr std::uint8_t mask3{1 << 3}; // bit 3
    constexpr std::uint8_t mask4{1 << 4}; // bit 4
    constexpr std::uint8_t mask5{1 << 5}; // bit 5
    constexpr std::uint8_t mask6{1 << 6}; // bit 6
    constexpr std::uint8_t mask7{1 << 7}; // bit 7

    std::uint8_t flags{0b0000'0101}; // 8 bit size

    std::cout << "bit 2 is " <<(static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
    flags ^= mask2; // Flip bit 2
    std::cout << "bit 2 is " <<(static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
    flags ^= mask2; // Flip bit 2
    std::cout << "bit 2 is " <<(static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
    std::cin.get();
    return 0;
}