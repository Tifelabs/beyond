#include <iostream>
#include <unistd.h>

void loadingSpinner(int seconds) {
    char spinner[] = {'|', '/', '-', '\\'}; 
    int spins = seconds * 4; 
    for (int i = 0; i < spins; i++) {
        std::cout << "\rLoading " << spinner[i % 4] << std::flush;
        usleep(250000);
    }
    std::cout << "\rLoading Done!    \n"; 
}

int main() {
    loadingSpinner(3); 
    std::cout << "Let’s go!\n";
    return 0;
}