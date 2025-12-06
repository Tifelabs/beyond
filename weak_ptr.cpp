#include <iostream>
#include <string>
#include <memory>

int main(int argc, char *argv[]){
    
    /* Creating BootMenu */
    std::shared_ptr<std::string> Menu = std::make_shared<std::string>("\nBOOT MENU\n");

    std::cout << "Select Option to Load" << *Menu << "\n\n";
    std::cout << "Boot Selection [S/N] --selection\n";

    /* -----  weak references ----- */
    std::weak_ptr<std::string> MainUser = Menu;
    std::weak_ptr<std::string> GuestUser = Menu;

    /* ----- First test (menu still alive) ----- */
    std::cout << "\nTesting use case:\n";
    if (auto test = MainUser.lock()) {
        std::cout << "Main User can test" << *test << '\n';
    }
    if (auto test = GuestUser.lock()) {
        std::cout << "Guest User checking In" << *test << '\n';
    }

    // ----- Simulate a crash -----
    std::cout << "\nBLUE SCREEN OF DEATH!\n";
    Menu.reset();              

    // ----- Second test (menu is gone) -----
    std::cout << "\nRunning Another TestCase:\n";
    if (auto test = MainUser.lock()) {
        std::cout << "Main User Active" << *test << '\n';
    } else {
        std::cout << "NO BOOTLOADER FOR MAIN\n";
    }

    if (auto test = GuestUser.lock()) {
        std::cout << "Guest User checking In" << *test << '\n';
    } else {
        std::cout << "NO BOOTLOADER FOR GUEST\n";
    }

    return 0;
}