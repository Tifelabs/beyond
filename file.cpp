#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <iomanip>

namespace fs = std::filesystem;

void printHeader(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

// 1. Write to File (Overwrite)
void writeToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file for writing!\n";
        return;
    }

    std::cout << "Enter text (type 'END' on new line to stop):\n";
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "END") break;
        file << line << '\n';
    }
    file.close();
    std::cout << "Data written successfully!\n";
}

/* Append to File */
void appendToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file for appending!\n";
        return;
    }

    std::cout << "Enter text to append (type 'END' to stop):\n";
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "END") break;
        file << line << '\n';
    }
    file.close();
    std::cout << "Data appended successfully!\n";
}

/* Read File By Line */
void readFileLines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file!\n";
        return;
    }

    printHeader("FILE CONTENT");
    std::string line;
    int lineNum = 1;
    while (std::getline(file, line)) {
        std::cout << std::setw(3) << lineNum++ << ": " << line << '\n';
    }
    file.close();
}

// 4. Read Entire File at Once
std::string readEntireFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file!\n";
        return "";
    }

    auto size = file.tellg();
    std::string content(size, ' ');
    file.seekg(0);
    file.read(&content[0], size);
    file.close();
    return content;
}

/* Binary Write */
void writeBinary(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open binary file!\n";
        return;
    }

    struct Record {
        char name[50];
        int id;
        double salary;
    };

    Record rec{"John Doe", 101, 75000.50};
    file.write(reinterpret_cast<char*>(&rec), sizeof(rec));
    file.close();
    std::cout << "Binary data written!\n";
}

// 6. Binary Read
void readBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open binary file!\n";
        return;
    }

    struct Record {
        char name[50];
        int id;
        double salary;
    };

    Record rec;
    file.read(reinterpret_cast<char*>(&rec), sizeof(rec));

    printHeader("BINARY DATA");
    std::cout << "Name   : " << rec.name << "\n";
    std::cout << "ID     : " << rec.id << "\n";
    std::cout << "Salary : $" << rec.salary << "\n";

    file.close();
}

/* File Info */
void fileInfo(const std::string& filename) {
    if (!fs::exists(filename)) {
        std::cout << "File does not exist!\n";
        return;
    }

    printHeader("FILE INFORMATION");
    std::cout << "Filename     : " << filename << "\n";
    std::cout << "Size         : " << fs::file_size(filename) << " bytes\n";
    std::cout << "Extension    : " << fs::path(filename).extension() << "\n";
    std::cout << "Last Modified: " << fs::last_write_time(filename) << "\n";
    std::cout << "Is Regular   : " << (fs::is_regular_file(filename) ? "Yes" : "No") << "\n";
}

int main() {
    std::string filename = "demo_file.txt";
    std::string binFilename = "data.bin";

    int choice;
    do {
        std::cout << "\n========================================\n";
        std::cout << "          C++ FILE HANDLING DEMO\n";
        std::cout << "========================================\n";
        std::cout << "1. Write to File (Overwrite)\n";
        std::cout << "2. Append to File\n";
        std::cout << "3. Read File Line by Line\n";
        std::cout << "4. Read Entire File at Once\n";
        std::cout << "5. Write Binary Data\n";
        std::cout << "6. Read Binary Data\n";
        std::cout << "7. Show File Information\n";
        std::cout << "8. Check if File Exists\n";
        std::cout << "9. Delete File\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();  // Clear newline

        switch (choice) {
            case 1: writeToFile(filename); break;
            case 2: appendToFile(filename); break;
            case 3: readFileLines(filename); break;
            case 4: 
                std::cout << readEntireFile(filename) << std::endl;
                break;
            case 5: writeBinary(binFilename); break;
            case 6: readBinary(binFilename); break;
            case 7: fileInfo(filename); break;
            case 8:
                std::cout << (fs::exists(filename) ? "File exists." : "File does not exist.") << "\n";
                break;
            case 9:
                if (fs::exists(filename) && fs::remove(filename)) {
                    std::cout << "File deleted successfully!\n";
                } else {
                    std::cout << "Failed to delete file.\n";
                }
                break;
            case 0: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}