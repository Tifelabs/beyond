#include <iostream>
#include <cstdint>

int main(){

    constexpr std::uint8_t mask0{0b0000'0001}; // bit 0
    constexpr std::uint8_t mask1{0b0000'0010}; // bit 1
    constexpr std::uint8_t mask2{0b0000'0100}; // bit 2
    constexpr std::uint8_t mask3{0b0000'1000}; // bit 3
    constexpr std::uint8_t mask4{0b0001'0000}; // bit 4
    constexpr std::uint8_t mask5{0b0010'0000}; // bit 5
    constexpr std::uint8_t mask6{0b0100'0000}; // bit 6
    constexpr std::uint8_t mask7{0b1000'0000}; // bit 7

    std::uint8_t flags{0b0000'0101}; // 8 bits in size means room for 8 flags
    
    std::cout << "bits 0 is " << (static_cast<bool>(flags & mask0) ? "on\n" : "off\n");
    std::cout << "bits 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");
    std::cout << "bits 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
    std::cout << "bits 3 is " << (static_cast<bool>(flags & mask3) ? "on\n" : "off\n");
    std::cout << "bits 4 is " << (static_cast<bool>(flags & mask4) ? "on\n" : "off\n");
    std::cout << "bits 5 is " << (static_cast<bool>(flags & mask5) ? "on\n" : "off\n");
    std::cout << "bits 6 is " << (static_cast<bool>(flags & mask6) ? "on\n" : "off\n");
    std::cout << "bits 7 is " << (static_cast<bool>(flags & mask7) ? "on\n" : "off\n");
    std::cin.get();
    return 0;
}