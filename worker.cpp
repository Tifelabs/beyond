#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <string>

bool is_Finished = false;

std::string DoWork(){
    std::cout << "Thread ID:: " << std::this_thread::get_id() << "\n";

    while(!is_Finished){
    static std::vector<std::string> console = {"Xbox","Playstation","SteamDeck","Nintendo"};
    for(int i = 0; i < console.size(); i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << console[i] << " Architecture\n";
    }
  }
  exit(0);
}


int main (int argc, char *argv[]){

    std::thread worker(DoWork);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    is_Finished = true;

    worker.join();
    std::cout <<"Worker thread has Stopped\n";

    std::cin.get();
}