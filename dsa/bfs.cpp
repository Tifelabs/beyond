#include <iostream>
#include <vector>
#include <queue>
#include <cstring>


const int N = 1e5 + 10;
std::vector<int> adj[N];
int dist[N];
bool visit[N];

void bfs(int src){
    std::memset(visit, 0, sizeof(visit));
    std::memset(dist, -1, sizeof(dist));

    std::queue<int> q;
    q.push(src);
    dist[src] = 0;
    visit[src] = true;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int v : adj[u]){
            if(!visit[v]){
                visit[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n{}, m{};
    std::cin >> n >> m;

    for(int i = 0; i < m; i++){
        int u{}, v{};
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bfs(1);

    for(int i = 1; i <= n; i++){
        std::cout << "[ " << i <<" ] = " << dist[i] <<"\n";
    }
    return 0;
}