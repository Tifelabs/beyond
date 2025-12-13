#include <iostream>
#include <string>
#include <vector> 

namespace Console {
    std::vector<std::string> Xbox = {"Xbox 360", "Xbox One", "Xbox Series S", "Xbox Series X"};
    
    void printXboxConsoles() {         
        for(const auto& x : Xbox) {
            std::cout << x << '\n';
        }
    }
}

int main() {
    std::vector<std::string> Xbox = {"Jumanji", "GTA V", "HALO", "FORZA HORIZON"};
    
    std::cout << "Games:\n";
    for(const auto& x : Xbox) {
        std::cout << x << '\n';
    }
    
    std::cout << "\nConsoles:\n";
    Console::printXboxConsoles();       
    
    return 0;
}