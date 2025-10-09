#include <iostream>
#include <vector>
#include <string>

#define DASH "\t + + ======================= + +\n\n"

int main(void){
    std::vector<std::string> consoles = {"PlayStation", "Xbox", "Nintendo"};

    for(std::string console : consoles){
        std::cout << console << "\n";
    }

    std::cout<< "\n\n\n";
    std::cout<< DASH;
    
    std::cout<< consoles.front() << "\n";
    std::cout<< consoles.back() << "\n";

    std::cout<< DASH;

    consoles.push_back("Atari");
    consoles.push_back("Sega");
    for(std::string console : consoles){
        std::cout << console << "\n";
    }
    return 0;
}