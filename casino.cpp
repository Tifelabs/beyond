#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <map>
#include <thread>
#include <fstream>

#define MINIMUM_WAGER 0.20

/* Function Prototypes */
double deposit(double balance, double amount);
double withdraw(double balance, double amount);
void wager(double amount);
void display(double& balance);

double deposit(double balance, double amount){
    if(amount < 50.0){
        std::cout << "Can't Deposit less than $50\n";
        return balance;
    }
    balance += amount;
    return balance;
}

double withdraw(double balance, double amount){
    if(amount > balance){
        std::cout << "Insufficient funds\n";
        return balance;
    }
    balance -= amount;
    return balance;
}

void display(double& balance){
    bool running = true;
    while(running){
        std::cout << "\t CRYLESS CASINO \n\n";
        std::cout << "Enter an Option to Proceed [1 -7] \n";
        std::cout << "[1]\t Deposit Money\n";
        std::cout << "[2]\t Withdraw Money\n";
        std::cout << "[3]\t Check  Balance\n";
        std::cout << "[4]\t HEADS && TAILS\n";
        std::cout << "[5]\t High or Low\n";
        std::cout << "[6]\t Set Username\n";
        std::cout << "[7]\t Quit\n";

        int choice{};
        std::cin >> choice;
        std::cout << "\033[2J\033[1;1H";

        if(choice == 1){
            std::cout << "[++ DEPOSIT ++]\n";
            std::cout << "Enter amount to deposit [$50+]\n";
            double amount;
            std::cin >> amount;
            balance = deposit(balance, amount);
        }
        else if(choice == 2){
            std::cout << "[++ WITHDRAW ++]\n";
            std::cout << "Enter amount to withdraw\n";
            double amount;
            std::cin >> amount;
            balance = withdraw(balance, amount);
        }
        else if(choice == 3){
            std::cout << "Balance: $" << balance << "\n";
        }
        else if(choice == 7){
            running = false;
        }
    }
}

int main(){
    double balance = 0.0;
    display(balance);
}