#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

std::map<std::string, std::string> flights;
std::mutex flights_mutex;

void BookFlight(const std::string& url){ 
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::string result = "Fake booking";
    std::lock_guard<std::mutex> guard(flights_mutex);
    flights[url] = result;
}

int main(){
    std::thread first_worker(BookFlight, "http://Tifeflights.com");
    std::thread second_worker(BookFlight, "http://Tife.com");
    
    first_worker.join();
    second_worker.join();
    
    /* Accessing Flight function without lock */
    for(const auto& [url, x] : flights){
        std::cout << url << " --> " << x << '\n';
    }
    
    std::cin.get();
    return 0;
}