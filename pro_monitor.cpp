#include <iostream>
#include <dirent.h>
#include <fstream>
#include <unistd.h>

void displayProcesses() {
    DIR *dir = opendir("/proc");
    if (!dir) {
        std::cout << "Cannot open /proc\n";
        return;
    }

    system("clear");
    std::cout << "PID\tMemory (KB)\tProcess Name\n";
    std::cout << "------------------------------------\n";

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        // Check if directory name is a PID (numeric)
        if (entry->d_type == DT_DIR && isdigit(entry->d_name[0])) {
            std::string pid = entry->d_name;
            std::string statm_path = "/proc/" + pid + "/statm";
            std::string comm_path = "/proc/" + pid + "/comm";

            // Get memory info
            std::ifstream statm(statm_path);
            long size;  // Total program size in pages
            if (statm >> size) {
                long memory_kb = (size * sysconf(_SC_PAGESIZE)) / 1024;

                // Get process name
                std::ifstream comm(comm_path);
                std::string name;
                if (std::getline(comm, name)) {
                    std::cout << pid << "\t" << memory_kb << "\t\t" << name << "\n";
                }
            }
        }
    }
    closedir(dir);
}

int main() {
    std::cout << "Process Monitor - Press Ctrl+C to exit\n\n";
    while (true) {
        displayProcesses();
        sleep(2);  // Update every 2 seconds
    }
    return 0;
}