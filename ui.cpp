#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>

// Function to clear the console screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to display the main menu
void displayMenu() {
    clearScreen();
    std::cout << "=== CLI User Interface ===\n";
    std::cout << "1. Option 1 - Say Hello\n";
    std::cout << "2. Option 2 - Do Math\n";
    std::cout << "3. Option 3 - Show Info\n";
    std::cout << "4. Exit\n";
    std::cout << "=========================\n";
    std::cout << "Enter your choice (1-4): ";
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

        clearInputBuffer(); // Clear remaining input

        // Process user choice
        switch (choice) {
            case 1:
                clearScreen();
                std::cout << "Hello, World!\n";
                waitForEnter();
                break;

            case 2:
                clearScreen();
                {
                    double num1, num2;
                    std::cout << "Enter first number: ";
                    std::cin >> num1;
                    std::cout << "Enter second number: ";
                    std::cin >> num2;
                    std::cout << "Result: " << num1 + num2 << "\n";
                    waitForEnter();
                }
                break;

            case 3:
                clearScreen();
                std::cout << "System Information:\n";
                std::cout << "- CLI Demo v1.0\n";
                std::cout << "- Built with C++\n";
                waitForEnter();
                break;

            case 4:
                clearScreen();
                std::cout << "Goodbye!\n";
                running = false;
                break;

            default:
                clearScreen();
                std::cout << "Invalid choice! Please select 1-4.\n";
                waitForEnter();
                break;
        }
    }

    return 0;
}