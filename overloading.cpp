#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

void printJob(int &x, int &time) {
    std::cout << "How many Print Jobs: \n";
    std::cin >> x;
    time = 60;
    std::cout << "Total Time Taken: " << x * time << " secs\n";
}

void printJob(std::vector<std::string> printerType) {
    printerType = {"HP", "DELL", "SAMSUNG", "KONICA"};
    std::cout << "Currently Using Printer -> " << printerType[2] << "\n";
    int total_proc = 5;
    while (total_proc--) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Printing....\n";
    }
    std::cout << "Process Finished\n";
}

int main() {
    int jobs, timePerJob;
    printJob(jobs, timePerJob);

    std::vector<std::string> types;
    printJob(types);

    std::cout << "Finished Printing Job\n";
}