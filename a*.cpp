#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Node {
    int x, y;
    float g, h, f;  // g: cost from start, h: heuristic, f: g + h
    Node* parent;

    Node(int x = 0, int y = 0)
        : x(x), y(y), g(std::numeric_limits<float>::infinity()),
          h(0), f(0), parent(nullptr) {}
};

// Min-heap on f
struct CompareNode {
    bool operator()(const Node* a, const Node* b) const { return a->f > b->f; }
};

class AStar {
private:
    std::vector<std::vector<int>> grid;
    int rows, cols;

    // Unique integer id for a cell
    int key(int x, int y) const { return x * cols + y; }

    // Manhattan distance
    float heuristic(const Node& a, const Node& b) const {
        return static_cast<float>(std::abs(a.x - b.x) + std::abs(a.y - b.y));
    }

    bool isValid(int x, int y) const {
        return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
    }

    // 4-directional neighbors
    std::vector<Node> getNeighbors(const Node& node) const {
        static const int dx[] = {-1, 1, 0, 0};
        static const int dy[] = {0, 0, -1, 1};
        std::vector<Node> neighbors;
        for (int i = 0; i < 4; i++) {
            int nx = node.x + dx[i], ny = node.y + dy[i];
            if (isValid(nx, ny)) neighbors.emplace_back(nx, ny);
        }
        return neighbors;
    }

    std::vector<Node> reconstructPath(const Node* endNode) const {
        std::vector<Node> path;
        for (const Node* cur = endNode; cur; cur = cur->parent)
            path.push_back(*cur);
        std::reverse(path.begin(), path.end());
        return path;
    }

public:
    explicit AStar(const std::vector<std::vector<int>>& g)
        : grid(g),
          rows(static_cast<int>(g.size())),
          cols(g.empty() ? 0 : static_cast<int>(g[0].size())) {}

    std::vector<Node> findPath(const Node& start, const Node& goal) {
        if (!isValid(start.x, start.y) || !isValid(goal.x, goal.y)) return {};

        std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet;
        std::unordered_set<int> closedSet;
        std::unordered_map<int, std::unique_ptr<Node>> allNodes;  // owns all nodes

        Node* startNode = (allNodes[key(start.x, start.y)] =
                               std::make_unique<Node>(start.x, start.y)).get();
        startNode->g = 0;
        startNode->h = heuristic(*startNode, goal);
        startNode->f = startNode->h;
        openSet.push(startNode);

        while (!openSet.empty()) {
            Node* current = openSet.top();
            openSet.pop();

            if (current->x == goal.x && current->y == goal.y)
                return reconstructPath(current);

            // Skip stale duplicates left in the queue
            if (!closedSet.insert(key(current->x, current->y)).second) continue;

            for (const Node& nb : getNeighbors(*current)) {
                int nk = key(nb.x, nb.y);
                if (closedSet.count(nk)) continue;

                float tentativeG = current->g + 1;  // uniform move cost

                auto& slot = allNodes[nk];
                if (!slot) slot = std::make_unique<Node>(nb.x, nb.y);
                Node* n = slot.get();

                if (tentativeG < n->g) {
                    n->parent = current;
                    n->g = tentativeG;
                    n->h = heuristic(*n, goal);
                    n->f = n->g + n->h;
                    openSet.push(n);
                }
            }
        }
        return {};  // no path
    }

    void printPath(const std::vector<Node>& path) const {
        std::vector<std::vector<char>> display(rows, std::vector<char>(cols, '.'));

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (grid[i][j] == 1) display[i][j] = '#';

        for (const Node& n : path) display[n.x][n.y] = '*';

        if (!path.empty()) {
            display[path.front().x][path.front().y] = 'S';
            display[path.back().x][path.back().y] = 'G';
        }

        for (const auto& row : display) {
            for (char c : row) std::cout << c << ' ';
            std::cout << '\n';
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // 0 = walkable, 1 = obstacle
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

    AStar pathfinder(grid);
    Node start(0, 0), goal(7, 7);

    std::cout << "Finding path from (" << start.x << "," << start.y
              << ") to (" << goal.x << "," << goal.y << ")\n\n";

    std::vector<Node> path = pathfinder.findPath(start, goal);

    if (path.empty()) {
        std::cout << "No path found!\n";
    } else {
        std::cout << "Path found with " << path.size() << " steps:\n";
        for (size_t i = 0; i < path.size(); i++) {
            std::cout << "(" << path[i].x << "," << path[i].y << ")";
            if (i + 1 < path.size()) std::cout << " -> ";
        }
        std::cout << "\n\nGrid visualization:\n";
        pathfinder.printPath(path);
    }
    return 0;
}