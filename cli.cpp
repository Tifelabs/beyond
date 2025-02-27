#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>

// ANSI color codes for beauty
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define BOLD    "\033[1m"

// Clear console (cross-platform)
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Get current time as a string
std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::string timeStr = std::ctime(&currentTime);
    return timeStr.substr(0, timeStr.length() - 1); // Remove trailing newline
}

int main() {
    bool running = true;
    int secondsElapsed = 0;

    std::cout << BOLD << BLUE << "Welcome to the Beautiful Real-Time CLI!" << RESET << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Brief intro pause

    while (running) {
        clearConsole();

        // Header
        std::cout << BOLD << GREEN << "╔════════════════════════════════════╗" << RESET << std::endl;
        std::cout << BOLD << GREEN << "║       Real-Time Clock CLI         ║" << RESET << std::endl;
        std::cout << BOLD << GREEN << "╚════════════════════════════════════╝" << RESET << std::endl;

        // Display current time
        std::cout << YELLOW << "Current Time: " << RESET << getCurrentTime() << std::endl;

        // Elapsed seconds with a pulsing effect
        std::cout << RED << "Seconds Elapsed: " << BOLD << (secondsElapsed % 2 == 0 ? BLUE : YELLOW) 
                  << secondsElapsed << RESET << std::endl;

        // Instructions
        std::cout << BLUE << "\nCommands: [q]uit" << RESET << std::endl;

        // Update every second
        secondsElapsed++;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Check for user input (non-blocking)
        if (std::cin.peek() != EOF) {
            char input;
            std::cin >> input;
            if (input == 'q' || input == 'Q') {
                running = false;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    clearConsole();
    std::cout << BOLD << RED << "Thank you for using the CLI! Goodbye!" << RESET << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}