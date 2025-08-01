#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

// Particle class to store position and movement
class Particle {
public:
    double x, y;
    Particle(double x_pos, double y_pos) : x(x_pos), y(y_pos) {}
    
    void move() {
        // Random movement in x and y directions (-0.5 to 0.5)
        x += (rand() / (double)RAND_MAX) - 0.5;
        y += (rand() / (double)RAND_MAX) - 0.5;
        
        // Keep particles within bounds [0, 100]
        x = std::max(0.0, std::min(100.0, x));
        y = std::max(0.0, std::min(100.0, y));
    }
};

// Simulation class to manage particles
class Simulation {
private:
    std::vector<Particle> particles;
    const int width = 20;  // Display width
    const int height = 20; // Display height
    
public:
    Simulation(int num_particles) {
        // Initialize particles at random positions
        for (int i = 0; i < num_particles; ++i) {
            double x = rand() % 100;
            double y = rand() % 100;
            particles.emplace_back(x, y);
        }
    }
    
    void update() {
        for (auto& particle : particles) {
            particle.move();
        }
    }
    
    void display() {
        // Clear console (works on Unix-like systems)
        std::cout << "\033[2J\033[1;1H";
        
        // Create a simple grid
        std::vector<std::vector<char>> grid(height, std::vector<char>(width, '.'));
        
        // Place particles on grid
        for (const auto& particle : particles) {
            int grid_x = static_cast<int>(particle.x * width / 100.0);
            int grid_y = static_cast<int>(particle.y * height / 100.0);
            if (grid_x >= 0 && grid_x < width && grid_y >= 0 && grid_y < height) {
                grid[grid_y][grid_x] = '*';
            }
        }
        
        // Print grid
        for (const auto& row : grid) {
            for (char cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << '\n';
        }
        std::cout << std::flush;
    }
    
    void run(int steps) {
        for (int i = 0; i < steps; ++i) {
            update();
            display();
            // Sleep for 100ms to make animation visible
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

int main() {
    // Seed random number generator
    srand(static_cast<unsigned>(time(0)));
    
    // Create simulation with 5 particles
    Simulation sim(5);
    
    // Run for 100 steps
    sim.run(100);
    
    return 0;
}