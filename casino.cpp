#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <thread>
#include <fstream>


#ifdef
#define MINIMUM_WAGER 0.20

/* Function Prototypes */
void deposit(double balance);
void withdraw(double amount);
void wager(double amount);
void display();


void display(){
    std::cout << "\t CRYLESS CASINO \n\n";
    std::cout << "Enter an Option to Proceed [1 -7] \n"
    while(1){
        std::cout << "[1]\t Deposit Money\n";
        std::cout << "[2]\t Withdraw Money\n";
        std::cout << "[3]\t Check  Balance\n";
        std::cout << "[4]\t HEADS && TAILS\n";
        std::cout << "[5]\t High or Low\n";
        std::cout << "[6]\t Set Username\n";
        std::cout << "[7]\t Quit\n";
        std::cout << "[1]\t Deposit Money\n";
    }
}

int main(){

}