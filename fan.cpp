#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void read_cpu_temp() {
    for (const auto& entry : fs::directory_iterator("/sys/class/thermal")) {
        if (entry.path().string().find("thermal_zone") != std::string::npos) {
            std::ifstream temp_file(entry.path() / "temp");
            if (temp_file.is_open()) {
                int temp;
                temp_file >> temp;
                std::cout << "CPU Temperature: " << temp / 1000.0f << " °C" << std::endl;
                temp_file.close();
            }
        }
    }
}

void read_fan_speed() {
    for (const auto& entry : fs::directory_iterator("/sys/class/hwmon")) {
        for (const auto& subentry : fs::directory_iterator(entry.path())) {
            if (subentry.path().string().find("fan") != std::string::npos &&
                subentry.path().string().find("_input") != std::string::npos) {
                std::ifstream fan_file(subentry.path());
                if (fan_file.is_open()) {
                    int rpm;
                    fan_file >> rpm;
                    std::cout << "Fan Speed: " << rpm << " RPM" << std::endl;
                    fan_file.close();
                }
            }
        }
    }
}

int main() {
    std::cout << "Checking CPU temperature...\n";
    read_cpu_temp();
    std::cout << "Checking fan speed...\n";
    read_fan_speed();
    return 0;
}