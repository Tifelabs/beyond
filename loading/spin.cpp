#include <iostream>
#include <unistd.h>

void loadingSpinner(int seconds) {
    char spinner[] = {'|', '/', '-', '\\'}; // Characters to spin
    int spins = seconds * 4; // 4 spins per second
    for (int i = 0; i < spins; i++) {
        std::cout << "\rLoading " << spinner[i % 4] << std::flush; // Cycle through | / - \
        usleep(250000); // 0.25 seconds (250,000 microseconds)
    }
    std::cout << "\rLoading Done!    \n"; // Clear the line
}

int main() {
    loadingSpinner(3); // Spin for 3 seconds
    std::cout << "Let’s go!\n";
    return 0;
}