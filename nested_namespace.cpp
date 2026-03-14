#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

namespace Menu {

    void startUp() {
        std::cout << R"(
        [*] Loading Kernel Modules
        [*] Loading arch
        [*] Battery Status
        [*] Checking RAM Cache
)";
    }

    namespace startUp_Settings {

        std::vector<std::pair<int, std::string>> settings_params = {
            {1, "Time clock"},
            {2, "Bios Password"},
            {3, "Reset Bios"},
            {4, "Save"},
            {5, "Quit"},
        };

        void display() {
            std::cout << "\n";
            for (const auto& s_params : settings_params) {
                std::cout << s_params.first << ". " << s_params.second << "\n";
            }
        }
    } 
} 

int main() {
    std::thread bios(Menu::startUp);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::thread bios_settings(Menu::startUp_Settings::display);
    bios.join();
    bios_settings.join();
    std::cout << "\nStart Up Completed\n";
    std::cin.get();
    return 0;
}