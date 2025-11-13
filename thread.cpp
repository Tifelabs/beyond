#include <iostream>
#include <string>
#include <thread>
#include <chrono>

bool is_Finished = false;

void DoWork() {
    /* Thread ID */
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;

    while (!is_Finished) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "Testing\n";
    }
}

int main() {
    // Start the worker thread
    std::thread worker(DoWork);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Signal the worker thread to stop
    is_Finished = true;

    // Wait for the worker thread to finish
    worker.join();

    std::cout << "Worker thread has finished\n";

    return 0;
}