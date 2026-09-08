#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

#define MINIMUM_WAGER 0.20

/* Function Prototypes */
double deposit(double balance, double amount);
double withdraw(double balance, double amount);
void username();
void changeUsername();
void headsAndTails(double& balance);
void highOrLow(double& balance);
void display(double& balance);

/* Deposit */
double deposit(double balance, double amount) {
    if (amount < 50.0) {
        std::cout << "Can't deposit less than $50\n";
        return balance;
    }
    balance += amount;
    std::cout << "Successfully deposited $" << amount << "\n";
    return balance;
}

/* Withdraw */
double withdraw(double balance, double amount) {
    if (amount > balance) {
        std::cout << "Insufficient funds\n";
        return balance;
    }
    if (amount <= 0) {
        std::cout << "Invalid amount\n";
        return balance;
    }
    balance -= amount;
    std::cout << "Successfully withdrew $" << amount << "\n";
    return balance;
}

/* Set / Create Username */
void username() {
    std::string name;
    std::ofstream file("username.txt");
    if (!file) {
        std::cerr << "Error creating username file\n";
        return;
    }
    std::cout << "Enter Username: ";
    std::cin >> name;
    file << name;
    file.close();
    std::cout << "Username registered successfully!\n";
}

/* Change or Delete Username */
void changeUsername() {
    int option = 0;
    std::cout << "Select Operation\n";
    std::cout << "\t[1] Change Username\n";
    std::cout << "\t[2] Delete Username\n";
    std::cout << "Choice: ";
    std::cin >> option;

    switch (option) {
        case 1: {
            std::cout << "Previous Username:\n";
            std::ifstream Rfile("username.txt");
            if (!Rfile) {
                std::cerr << "No username found or error opening file\n";
                return;
            }
            std::string name;
            while (std::getline(Rfile, name)) {
                std::cout << name << "\n";
            }
            Rfile.close();

            std::cout << "\nEnter new username: ";
            username();          // re-use the set function
            break;
        }
        case 2: {
            std::cout << "Are you sure you want to delete the username?\n";
            std::cout << "Enter [Y]es or [N]o: ";
            char opt;
            std::cin >> opt;
            if (opt == 'Y' || opt == 'y') {
                if (std::remove("username.txt") == 0) {
                    std::cout << "Username deleted successfully\n";
                } else {
                    std::cout << "No username file found or deletion failed\n";
                }
            } else {
                std::cout << "Returning to menu...\n";
            }
            break;
        }
        default:
            std::cout << "Invalid option\n";
            break;
    }
}

/* Game 1: Heads & Tails */
void headsAndTails(double& balance) {
    if (balance < MINIMUM_WAGER) {
        std::cout << "Insufficient balance to play (minimum $" << MINIMUM_WAGER << ")\n";
        return;
    }

    double wager;
    std::cout << "Enter wager amount (min $" << MINIMUM_WAGER << "): ";
    std::cin >> wager;

    if (wager < MINIMUM_WAGER || wager > balance) {
        std::cout << "Invalid wager\n";
        return;
    }

    char choice;
    std::cout << "Choose [H]eads or [T]ails: ";
    std::cin >> choice;
    choice = toupper(choice);

    if (choice != 'H' && choice != 'T') {
        std::cout << "Invalid choice\n";
        return;
    }

    // Generate random result
    srand(static_cast<unsigned>(time(0)));
    char result = (rand() % 2 == 0) ? 'H' : 'T';

    std::cout << "Coin landed on: " << (result == 'H' ? "Heads" : "Tails") << "\n";

    if (choice == result) {
        balance += wager;
        std::cout << "You won $" << wager << "!\n";
    } else {
        balance -= wager;
        std::cout << "You lost $" << wager << "\n";
    }
    std::cout << "Current balance: $" << balance << "\n";
}

/* Game 2: High or Low */
void highOrLow(double& balance) {
    if (balance < MINIMUM_WAGER) {
        std::cout << "Insufficient balance to play (minimum $" << MINIMUM_WAGER << ")\n";
        return;
    }

    double wager;
    std::cout << "Enter wager amount (min $" << MINIMUM_WAGER << "): ";
    std::cin >> wager;

    if (wager < MINIMUM_WAGER || wager > balance) {
        std::cout << "Invalid wager\n";
        return;
    }

    srand(static_cast<unsigned>(time(0)));
    int number = rand() % 100 + 1;   // 1–100

    char choice;
    std::cout << "A number between 1 and 100 has been generated.\n";
    std::cout << "Will it be [H]igh (51-100) or [L]ow (1-50)? ";
    std::cin >> choice;
    choice = toupper(choice);

    if (choice != 'H' && choice != 'L') {
        std::cout << "Invalid choice\n";
        return;
    }

    bool isHigh = number > 50;
    std::cout << "The number was: " << number << "\n";

    if ((choice == 'H' && isHigh) || (choice == 'L' && !isHigh)) {
        balance += wager;
        std::cout << "You won $" << wager << "!\n";
    } else {
        balance -= wager;
        std::cout << "You lost $" << wager << "\n";
    }
    std::cout << "Current balance: $" << balance << "\n";
}

/* Main Menu */
void display(double& balance) {
    bool running = true;
    while (running) {
        std::cout << "\n\t===== CRYLESS CASINO =====\n\n";
        std::cout << "Enter an option [1-8]:\n";
        std::cout << "[1] Deposit Money\n";
        std::cout << "[2] Withdraw Money\n";
        std::cout << "[3] Check Balance\n";
        std::cout << "[4] Heads & Tails\n";
        std::cout << "[5] High or Low\n";
        std::cout << "[6] Set Username\n";
        std::cout << "[7] Change / Delete Username\n";
        std::cout << "[8] Quit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;

        // Clear input buffer in case of bad input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        // Simple screen clear (works on most terminals)
        std::cout << "\033[2J\033[1;1H";

        switch (choice) {
            case 1: {
                std::cout << "[++ DEPOSIT ++]\n";
                std::cout << "Enter amount to deposit [$50+]: ";
                double amount;
                std::cin >> amount;
                balance = deposit(balance, amount);
                break;
            }
            case 2: {
                std::cout << "[++ WITHDRAW ++]\n";
                std::cout << "Enter amount to withdraw: ";
                double amount;
                std::cin >> amount;
                balance = withdraw(balance, amount);
                break;
            }
            case 3:
                std::cout << "Current Balance: $" << balance << "\n";
                break;
            case 4:
                headsAndTails(balance);
                break;
            case 5:
                highOrLow(balance);
                break;
            case 6:
                username();
                break;
            case 7:
                changeUsername();
                break;
            case 8:
                std::cout << "Thanks for playing! Goodbye.\n";
                running = false;
                break;
            default:
                std::cout << "Invalid option. Please choose 1-8.\n";
                break;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // seed once
    double balance = 0.0;
    display(balance);
    return 0;
}