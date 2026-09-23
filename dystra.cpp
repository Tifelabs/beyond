#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to, weight;
};

vector<int> dijkstra(int src, const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    dist[src] = 0;

    // min-heap of (distance, node)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue; // stale entry, skip

        for (const auto& edge : graph[u]) {
            int v = edge.to, w = edge.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    int n = 6;
    vector<vector<Edge>> graph(n);

    auto addEdge = [&](int u, int v, int w) {
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // undirected
    };

    addEdge(0, 1, 4);
    addEdge(0, 2, 1);
    addEdge(2, 1, 2);
    addEdge(1, 3, 5);
    addEdge(2, 3, 8);
    addEdge(3, 4, 3);
    addEdge(4, 5, 1);

    vector<int> dist = dijkstra(0, graph);

    for (int i = 0; i < n; i++)
        cout << "Distance to " << i << ": " << dist[i] << "\n";
}