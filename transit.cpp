#include <iostream>
#include <string>
#include <vector>

namespace Coordinate {

std::string get_cord() {
    std::string cor;
    std::cin >> cor;

    std::vector<std::pair<std::string, std::string>> zone_cord = {
        {"NR", "NORTH"},
        {"ST", "SOUTH"},
        
    };

    return cor; 
}

}

int main() {

}