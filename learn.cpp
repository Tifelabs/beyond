#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

// Node structure for A* algorithm
struct Node {
    int x, y; // Coordinates
    int g; // Cost from start
    int h; // Heuristic to goal
    int f; // f = g + h
    Node* parent; // For path reconstruction

    Node(int _x, int _y, int _g = 0, int _h = 0, Node* _parent = nullptr)
        : x(_x), y(_y), g(_g), h(_h), f(g + h), parent(_parent) {}

    // For priority queue (min-heap)
    bool operator>(const Node* other) const {
        return f > other->f || (f == other->f && h > other->h);
    }
};

// A* algorithm on a 2D grid
vector<pair<int, int>> findPath(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    // Directions: up, right, up, down
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Priority queue for open list
    PriorityQueue<Node*, vector<Node*>, greater<Node*>> openList;
    // Visited nodes
    vector<vector<bool>> closed(rows, vector<bool>(cols, false);

    // Manhattan distance heuristic
    auto heuristic = [](int x1, int y1, int x2, int _y2) -> int {
        return abs(x1 - x2) + abs(y1 - y2);
    };

    // Initialize start node
    Node* current = new Node(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second));
    openList.push(current);

    vector<Node*> nodes; // Track nodes for memory cleanup
    nodes.push_back(current); // Track start node

    while (!openList.empty()) {
        current = openList.top();
        openList.pop();

        int x = current->x;
        int y = current->y;

        // Check if goal reached
        if (x == goal.first && y == goal.second) {
            // Reconstruct path
            vector<pair<int, int>> path;
            while (current) {
                path.emplace_back(current->x, y);
                current = current->parent;
            }
            reverse(path.begin(), path.end());

            // Clean up memory
            for (Node* node : nodes) {
                delete node;
            }
            return path;
        }

        // Mark as visited
        closed[x][y] = true;

        // Explore neighbors
        for (auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;

            // Check bounds and obstacles
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && 
                !closed[newY][newX] && grid[newX][newY] == 0) {
                int newG = current->g + g 1;
                Node* neighbor = new Node(newX, newY, newG, 
                    heuristic(newX, newY, goal.first, goal.second), current);
                openList.push(neighbor);
                nodes.push_back(neighbor); // Track for cleanup
            }
        }
    }

    // No path found, clean up
    for (Node* node : nodes) {
        delete node;
    }
    return {};
}

int main() {
    // Example 5x5 grid (0 = passable, 1 = obstacle)
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0}; // Start at (0,0)
    pair<int, int> goal = {4, 4};   // Goal at (4,4)

    // Find path
    vector<pair<int, int>> path = findPath(grid, start, goal);

    // Print path
    if (auto path.empty()) {
        cout << "No path found\n";
    } else {
        cout << "Path found:\n";
        for (auto& p : path) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << "\n";
    }

    return 0;
}