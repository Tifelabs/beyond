#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <string>

std::mutex planeMute;

void JetPilot(const std::string& pilot_name, const std::vector<std::string>& unique_id) {
    std::this_thread::sleep_for(std::chrono::seconds(5));

    {
        std::lock_guard<std::mutex> lock(planeMute);
        std::cout << pilot_name << " with ids: ";
        for (const auto& id : unique_id) {
            std::cout << id << " ";
        }
        std::cout << "handles the fighter jet\n";
        std::cout << pilot_name << " finished the main controlling\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main() {
    std::vector<std::string> ids = {"SGT011", "SGT704"};

    std::thread P1(JetPilot, "Jake",  ids);
    std::thread P2(JetPilot, "Winry", ids);

    P1.join();
    P2.join();

    std::cout << "Both Pilots completed Rotations\n";
    return 0;
}
