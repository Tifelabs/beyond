#include <iostream>
#include <unistd.h>

void loadingBar(int duration) { // Duration in seconds
    int width = 20; // Bar width in characters
    for (int i = 0; i <= 100; i += 10) { // 0% to 100%, step by 10
        int progress = (width * i) / 100; // How many # to show
        std::cout << "\r["; // \r rewrites the line
        for (int j = 0; j < width; j++) {
            if (j < progress) std::cout << "#";
            else std::cout << " ";
        }
        std::cout << "] " << i << "%" << std::flush;
        sleep(duration / 10); // Split duration across 10 steps
    }
    std::cout << "\nLoading complete!\n";
}

int main() {
    std::cout << "Starting up...\n";
    loadingBar(5); // Takes 5 seconds total
    std::cout << "Ready to roll!\n";
    return 0;
}