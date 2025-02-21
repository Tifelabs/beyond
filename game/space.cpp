#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

using namespace std;

// Game settings
const int SCREEN_WIDTH = 40;
const int SCREEN_HEIGHT = 20;

// Player structure
struct Player {
    int x, y;
    char symbol = '^';
};

// Enemy structure
struct Enemy {
    int x, y;
    char symbol = 'V';
};

// Bullet structure
struct Bullet {
    int x, y;
    char symbol = '|';
};

// Function to check if a key is pressed (non-blocking)
bool kbhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

// Function to get a single character (non-blocking)
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void clearScreen() {
    system("clear"); // Linux screen clear
}

void drawGame(vector<vector<char>>& screen, Player& player, vector<Enemy>& enemies, vector<Bullet>& bullets) {
    // Clear screen buffer
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            screen[i][j] = ' ';
        }
    }

    // Draw player
    screen[player.y][player.x] = player.symbol;

    // Draw enemies
    for (const auto& enemy : enemies) {
        screen[enemy.y][enemy.x] = enemy.symbol;
    }

    // Draw bullets
    for (const auto& bullet : bullets) {
        screen[bullet.y][bullet.x] = bullet.symbol;
    }

    // Print screen
    clearScreen();
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            cout << screen[i][j];
        }
        cout << endl;
    }
}

int main() {
    // Seed random number generator
    srand(time(0));

    // Initialize game objects
    Player player{SCREEN_WIDTH / 2, SCREEN_HEIGHT - 1};
    vector<Enemy> enemies;
    vector<Bullet> bullets;
    vector<vector<char>> screen(SCREEN_HEIGHT, vector<char>(SCREEN_WIDTH, ' '));

    bool gameRunning = true;
    int enemySpawnTimer = 0;

    // Set terminal to non-blocking input
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    // Game loop
    while (gameRunning) {
        // Handle input
        if (kbhit()) {
            char input = getch();
            switch (input) {
                case 'a':
                case 'A':
                    if (player.x > 0) player.x--;
                    break;
                case 'd':
                case 'D':
                    if (player.x < SCREEN_WIDTH - 1) player.x++;
                    break;
                case ' ': // Space to shoot
                    bullets.push_back({player.x, player.y - 1});
                    break;
                case 'q':
                case 'Q':
                    gameRunning = false;
                    break;
            }
        }

        // Spawn enemies
        enemySpawnTimer++;
        if (enemySpawnTimer >= 20) {
            enemies.push_back({rand() % SCREEN_WIDTH, 0});
            enemySpawnTimer = 0;
        }

        // Update bullets
        for (int i = bullets.size() - 1; i >= 0; i--) {
            bullets[i].y--;
            if (bullets[i].y < 0) {
                bullets.erase(bullets.begin() + i);
            }
        }

        // Update enemies
        for (int i = enemies.size() - 1; i >= 0; i--) {
            enemies[i].y++;
            if (enemies[i].y >= SCREEN_HEIGHT) {
                enemies.erase(enemies.begin() + i);
                continue;
            }

            // Check collision with bullets
            for (int j = bullets.size() - 1; j >= 0; j--) {
                if (bullets[j].x == enemies[i].x && bullets[j].y == enemies[i].y) {
                    enemies.erase(enemies.begin() + i);
                    bullets.erase(bullets.begin() + j);
                    break;
                }
            }
        }

        // Check player collision
        for (const auto& enemy : enemies) {
            if (enemy.x == player.x && enemy.y == player.y) {
                gameRunning = false;
            }
        }

        // Draw everything
        drawGame(screen, player, enemies, bullets);

        // Control game speed
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    cout << "Game Over!" << endl;
    return 0;
}