#include <iostream>
#include <string>
#include <vector>

#define MAX_DASH 24
#define MAX_STAR 12
class Screen{
public:
    Screen(){
      const char *star[] = {"*", "x"};
      const char *dash[] = {"-", "|"};
      
      for(int x = 0; x < MAX_STAR; x++){
            std::cout << star[x % 2];
            for(int y = 0; y < MAX_DASH; y++){
                std::cout << dash[y % 2];
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    void printScreenTypes(){
        std::vector<std::string> types = {"OLED", "IPS", "LCD", "AMOLED"};
        for(const auto& type : types){
            std::cout<< "-" << type << '\n';
        }
        std::cout << '\n';
      }
      int width = 0, height = 0;
};

int main(int argc, char *argv[]){

    Screen ScreenObj;
    ScreenObj.width = 1024;
    ScreenObj.height = 768;
    std::cout << "Display On:\n";

    std::cout << "SCREEN RES :: " << ScreenObj.width << "x" << ScreenObj.height << "\n\n";
    ScreenObj.printScreenTypes();
}