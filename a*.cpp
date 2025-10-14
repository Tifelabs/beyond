#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>

// Node structure for grid positions
struct Node {
int x, y;
float g, h, f;  // g: cost from start, h: heuristic, f: total
Node* parent;

Node(int x = 0, int y = 0) : x(x), y(y), g(0), h(0), f(0), parent(nullptr) {}

bool operator==(const Node& other) const {
    return x == other.x && y == other.y;
}

};

// Hash function for Node (for unordered_set/map)
struct NodeHash {
size_t operator()(const Node& n) const {
return std::hash<int>()(n.x) ^ (std::hash<int>()(n.y) << 1);
}
};

// Comparator for priority queue (min-heap based on f value)
struct CompareNode {
bool operator()(Node* a, Node* b) const {
return a->f > b->f;
}
};

// A* Pathfinding Class
class AStar {
private:
std::vector<std::vector<int>> grid;
int rows, cols;

```
// Calculate Manhattan distance heuristic
float heuristic(const Node& a, const Node& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

// Check if position is valid
bool isValid(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
}

// Get neighbors (4-directional movement)
std::vector<Node> getNeighbors(const Node& node) {
    std::vector<Node> neighbors;
    int dx[] = {-1, 1, 0, 0};  // up, down, left, right
    int dy[] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        int nx = node.x + dx[i];
        int ny = node.y + dy[i];
        if (isValid(nx, ny)) {
            neighbors.push_back(Node(nx, ny));
        }
    }
    return neighbors;
}

// Reconstruct path from end to start
std::vector<Node> reconstructPath(Node* endNode) {
    std::vector<Node> path;
    Node* current = endNode;
    while (current != nullptr) {
        path.push_back(*current);
        current = current->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}
```

public:
AStar(std::vector<std::vector<int>>& g) : grid(g) {
rows = g.size();
cols = g[0].size();
}

```
// Main A* algorithm
std::vector<Node> findPath(Node start, Node goal) {
    // Priority queue (open set)
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet;
    
    // Track visited nodes
    std::unordered_set<std::string> closedSet;
    
    // Map to store nodes
    std::unordered_map<std::string, Node*> allNodes;
    
    // Initialize start node
    Node* startNode = new Node(start.x, start.y);
    startNode->g = 0;
    startNode->h = heuristic(*startNode, goal);
    startNode->f = startNode->g + startNode->h;
    
    openSet.push(startNode);
    std::string startKey = std::to_string(start.x) + "," + std::to_string(start.y);
    allNodes[startKey] = startNode;
    
    while (!openSet.empty()) {
        // Get node with lowest f value
        Node* current = openSet.top();
        openSet.pop();
        
        std::string currentKey = std::to_string(current->x) + "," + std::to_string(current->y);
        
        // Check if reached goal
        if (current->x == goal.x && current->y == goal.y) {
            std::vector<Node> path = reconstructPath(current);
            
            // Cleanup
            for (auto& pair : allNodes) {
                delete pair.second;
            }
            
            return path;
        }
        
        // Add to closed set
        closedSet.insert(currentKey);
        
        // Check all neighbors
        std::vector<Node> neighbors = getNeighbors(*current);
        for (Node& neighbor : neighbors) {
            std::string neighborKey = std::to_string(neighbor.x) + "," + std::to_string(neighbor.y);
            
            // Skip if already evaluated
            if (closedSet.find(neighborKey) != closedSet.end()) {
                continue;
            }
            
            float tentativeG = current->g + 1;  // Cost of 1 per move
            
            Node* neighborNode;
            if (allNodes.find(neighborKey) == allNodes.end()) {
                neighborNode = new Node(neighbor.x, neighbor.y);
                allNodes[neighborKey] = neighborNode;
            } else {
                neighborNode = allNodes[neighborKey];
            }
            
            // If this path is better, update
            if (tentativeG < neighborNode->g || neighborNode->g == 0) {
                neighborNode->parent = current;
                neighborNode->g = tentativeG;
                neighborNode->h = heuristic(*neighborNode, goal);
                neighborNode->f = neighborNode->g + neighborNode->h;
                
                openSet.push(neighborNode);
            }
        }
    }
    
    // Cleanup if no path found
    for (auto& pair : allNodes) {
        delete pair.second;
    }
    
    return std::vector<Node>();  // No path found
}

// Print the grid with path
void printPath(const std::vector<Node>& path) {
    std::vector<std::vector<char>> display(rows, std::vector<char>(cols, '.'));
    
    // Mark obstacles
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                display[i][j] = '#';
            }
        }
    }
    
    // Mark path
    for (const Node& node : path) {
        display[node.x][node.y] = '*';
    }
    
    // Mark start and end
    if (!path.empty()) {
        display[path.front().x][path.front().y] = 'S';
        display[path.back().x][path.back().y] = 'G';
    }
    
    // Print
    for (const auto& row : display) {
        for (char c : row) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
}
```

};

// Main function with example usage
int main() {
// Create grid (0 = walkable, 1 = obstacle)
std::vector<std::vector<int>> grid = {
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1, 0},
{0, 0, 1, 0, 1, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 1, 0},
{0, 0, 0, 0, 1, 0, 1, 0},
{0, 1, 1, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0}
};

```
AStar pathfinder(grid);

Node start(0, 0);
Node goal(7, 7);

std::cout << "Finding path from (" << start.x << "," << start.y 
          << ") to (" << goal.x << "," << goal.y << ")\n\n";

std::vector<Node> path = pathfinder.findPath(start, goal);

if (path.empty()) {
    std::cout << "No path found!" << std::endl;
} else {
    std::cout << "Path found with " << path.size() << " steps:\n";
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << "(" << path[i].x << "," << path[i].y << ")";
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n\nGrid visualization:\n";
    pathfinder.printPath(path);
}

return 0;

}