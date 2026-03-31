#include <iostream>
#include <vector>
#include <string>

struct Points {
    double x{};
    double y{};
};

struct GamePhysics {
    double speed = 50.0;
    static constexpr double gravity = 9.8;

    std::vector<std::string> shapes = {"circle", "square", "triangle", "cross"};

    std::vector<std::pair<int, std::string>> effects = {
        {1, "Collision"},
        {2, "Ripple"},
        {3, "Explosion"},
        {4, "Elasticity"},
        {5, "Projectile"}
    };

    void printShapes() {
        for (const auto& s : shapes)
            std::cout << s << '\n';
    }

    void printEffects() {
        for (const auto& e : effects)
            std::cout << e.first << " " << e.second << '\n';
    }
};

int main() {
    Points coordinate;
    coordinate.x = 5;
    coordinate.y = 3;
    std::cout << "COORDINATE -> (" << coordinate.x << ", " << coordinate.y << ")\n";

    GamePhysics gp;
    std::cout << "Speed: " << gp.speed << '\n';
    std::cout << "Gravity: " << GamePhysics::gravity << '\n';

    std::cout << "Shapes:\n";
    gp.printShapes();

    std::cout << "Effects:\n";
    gp.printEffects();

    return 0;
}