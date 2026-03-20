#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <cerrno>
#include <cstring>
#include <sys/wait.h>
#include <cstdlib>

namespace Utils {

void separator(char c = '-', int width = 45) {
    std::cout << std::string(width, c) << '\n';
}

void printHeader(const std::string& title) {
    separator('=');
    std::cout << "  " << title << '\n';
    separator('=');
}

}

struct PrintJob {
    int job_id;
    std::string status;
};

struct Signal {
    int signal_count = 0;
    std::string priority = "NORMAL";
};

namespace Engine {

void startEngine(int countdown = 10) {
    Utils::printHeader("ENGINE START SEQUENCE");

    pid_t engine_pid = fork();

    if (engine_pid < 0) {
        std::cerr << "[ERROR] Fork failed: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    } else if (engine_pid == 0) {
        std::cout << "[CHILD]  Engine subprocess PID -> " << getpid() << '\n';
        std::cout << "[CHILD]  Performing pre-flight diagnostics...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        std::cout << "[CHILD]  Diagnostics complete.\n";
        exit(EXIT_SUCCESS);
    }

    int child_status = 0;
    waitpid(engine_pid, &child_status, 0);

    if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != 0) {
        std::cerr << "[ERROR] Child process failed.\n";
        return;
    }

    std::cout << "[PARENT] Parent PID -> " << getpid() << '\n';

    for (int i = countdown; i > 0; --i) {
        std::cout << "  Starting... [ " << std::setw(2) << i << " ]\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    Utils::separator();
    std::cout << "  >> Engine Fully Started <<\n";
    Utils::separator();
}

void offEngine() {
    Utils::printHeader("ENGINE SHUTDOWN SEQUENCE");
    std::cout << "  Initiating controlled shutdown...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "  Engine Turned Off Completely.\n";
    std::cout << "  ENGINE STATUS: [ OFF ]\n";
    Utils::separator();
}

void engineStatus() {
    Utils::printHeader("ENGINE DIAGNOSTIC REPORT");

    struct StatEntry {
        int code;
        std::string label;
        std::string description;
    };

    const std::vector<StatEntry> stats = {
        {0, "CRITICAL", "Very Bad  - Crash or catastrophic failure imminent"},
        {1, "POOR",     "Bad       - Engine not in acceptable condition"},
        {2, "WARNING",  "Caution   - Engine requires scheduled checkup"},
        {3, "FAIR",     "Advisory  - Consult technicians for brief test"},
        {4, "GOOD",     "Healthy   - Engine in good operating condition"},
        {5, "OPTIMAL",  "Approved  - All tests passed, peak performance"},
    };

    std::cout << std::left
              << std::setw(4)  << "ID"
              << std::setw(12) << "Level"
              << "Details\n";
    Utils::separator();

    for (const auto& s : stats) {
        std::cout << std::setw(4)  << s.code
                  << std::setw(12) << s.label
                  << s.description << '\n';
    }

    Utils::separator();
}

}

void PrintStatus() {
    Utils::printHeader("PRINT SUBSYSTEM");
    std::cout << "  Warming up print queue (5s)...\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    pid_t printing_pid = fork();

    if (printing_pid < 0) {
        std::cerr << "[ERROR] Fork failed: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    } else if (printing_pid == 0) {
        std::cout << "[PRINTER-CHILD] Print daemon PID -> " << getpid() << '\n';

        const std::vector<PrintJob> jobs = {
            {1, "Printing..."},
            {2, "In Progress"},
            {3, "Job Done"},
            {4, "Job Cancelled"},
            {5, "Error"},
        };

        std::cout << std::left << std::setw(8) << "JOB ID" << "STATUS\n";
        Utils::separator('-', 25);
        for (const auto& j : jobs) {
            std::cout << std::setw(8) << j.job_id << j.status << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }

        exit(EXIT_SUCCESS);
    }

    int child_status = 0;
    waitpid(printing_pid, &child_status, 0);
    std::cout << "[PRINTER-PARENT] All print jobs processed.\n";
    Utils::separator();
}

void jetEngine() {
    Utils::printHeader("JET ENGINE CONTROL PANEL");

    std::cout << "  SELECT AN OPTION:\n\n"
              << "    [1]  Start Engine\n"
              << "    [2]  Turn Off Engine\n"
              << "    [3]  Check Engine Status\n"
              << "    [4]  Check Engine Speed    (stub)\n"
              << "    [5]  Troubleshoot / Hard Reset (stub)\n\n"
              << "  > ";

    int selection = 0;
    if (!(std::cin >> selection)) {
        std::cerr << "[ERROR] Invalid input - expected an integer.\n";
        return;
    }

    std::cout << '\n';

    switch (selection) {
        case 1: Engine::startEngine();  break;
        case 2: Engine::offEngine();    break;
        case 3: Engine::engineStatus(); break;
        case 4:
        case 5:
            std::cout << "  [STUB] Feature not yet implemented.\n";
            Utils::separator();
            break;
        default:
            std::cerr << "[ERROR] '" << selection << "' is not a valid option. Please enter 1-5.\n";
            break;
    }
}

int main(int argc, char* argv[]) {
    jetEngine();

    std::thread engine_worker(Engine::engineStatus);
    std::thread print_worker(PrintStatus);

    engine_worker.join();
    print_worker.join();

    Utils::printHeader("RUNTIME COMPLETE");
    std::cout << "  All engine and print workers finished successfully.\n";
    Utils::separator('=');

    return EXIT_SUCCESS;
}