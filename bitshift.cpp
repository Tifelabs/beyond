#include <iostream>
#include <bitset>

int main(int argc, char *argv[]){

    std::bitset<4> four_bits = 0b0001;
    std::cout << "INITIAL BITS: " << four_bits << "\n";
    four_bits = ~four_bits;
    std::cout << "FLIP BITS: " << four_bits << "\n";
    std::cout << "VALUES: " << four_bits.to_ulong() << "\n\n";

    std::bitset<8> eight_bits = 0b0101;
    std::cout << "INITIAL BITS: " << eight_bits << std::"\n";
    eight_bits.set(7);
    std::cout << "LEFT SHIFT: " << (eight_bits << 1) << "\n";
    std::cout << "RIGHT SHIFT: " << (eight_bits >> 1)<< "\n";
    eight_bits.reset();
    return 0;
}