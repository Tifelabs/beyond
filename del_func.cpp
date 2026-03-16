#include <iostream>

void Uptime(int secs){
    std::cout << secs << " secs\n";
}

void Uptime(char) = delete;
void Uptime(bool) = delete;

int main(){

    Uptime(30);
    Uptime('v');
    Uptime(true);

    return 0;
}