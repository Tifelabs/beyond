#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

// Clear Screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


//Menu
void displayMenu(){
    clearScreen();
    std::cout << "\t\t [--- SELECT CONSOLE ---]\n";
    std::cout << "[1] -- PS2\n";
    std::cout << "[2] -- PSP\n";
    std::cout << "[3] -- GBA\n";
    std::cout << "[4] -- NES\n";
    std::cout << "****************\n";
    std::cout << "[Enter Option: ]\n";
}

// Function to handle invalid input
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to pause and wait for user input
void waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
    clearInputBuffer();
}

int main() {
    bool running = true;
    int choice;

    while (running) {
        displayMenu();
        
        // Get user input
        if (!(std::cin >> choice)) {
            clearInputBuffer();
            std::cout << "Invalid input! Please enter a number.\n";
            waitForEnter();
            continue;
        }

        clearInputBuffer(); 

        // Process user choice
        switch (choice) {
            case 1:
                clearScreen();
                std::cout << "Loading pcsx2 Emulator....\n";
                waitForEnter();
                break;
            }
        }
    }