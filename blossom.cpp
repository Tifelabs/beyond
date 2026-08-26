#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

struct Blossom {
    int n, match[MAXN], p[MAXN], base[MAXN], q[MAXN];
    bool used[MAXN], blossom[MAXN];
    vector<int> g[MAXN];

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int lca(int a, int b) {
        bool used[MAXN] = {};
        while (true) {
            a = base[a];
            used[a] = true;
            if (match[a] == -1) break;
            a = p[match[a]];
        }
        while (true) {
            b = base[b];
            if (used[b]) return b;
            b = p[match[b]];
        }
    }

    void markPath(int v, int b, int children) {
        while (base[v] != b) {
            blossom[base[v]] = blossom[base[match[v]]] = true;
            p[v] = children;
            children = match[v];
            v = p[match[v]];
        }
    }

    int findPath(int root) {
        memset(used, 0, sizeof(used));
        memset(p, -1, sizeof(p));
        for (int i = 0; i < n; i++) base[i] = i;

        int qh = 0, qt = 0;
        q[qt++] = root;
        used[root] = true;

        while (qh < qt) {
            int v = q[qh++];
            for (int to : g[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
                    int curbase = lca(v, to);
                    memset(blossom, 0, sizeof(blossom));
                    markPath(v, curbase, to);
                    markPath(to, curbase, v);
                    for (int i = 0; i < n; i++) {
                        if (blossom[base[i]]) {
                            base[i] = curbase;
                            if (!used[i]) {
                                used[i] = true;
                                q[qt++] = i;
                            }
                        }
                    }
                } else if (p[to] == -1) {
                    p[to] = v;
                    if (match[to] == -1) return to;
                    to = match[to];
                    used[to] = true;
                    q[qt++] = to;
                }
            }
        }
        return -1;
    }

    int maxMatching() {
        memset(match, -1, sizeof(match));
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (match[i] == -1) {
                int v = findPath(i);
                if (v != -1) {
                    ans++;
                    while (v != -1) {
                        int pv = p[v], ppv = match[pv];
                        match[v] = pv;
                        match[pv] = v;
                        v = ppv;
                    }
                }
            }
        }
        return ans;
    }
};

// Example usage
int main() {
    Blossom b;
    b.n = 4;               // vertices 0..3
    b.addEdge(0, 1);
    b.addEdge(1, 2);
    b.addEdge(2, 3);
    b.addEdge(3, 0);
    b.addEdge(0, 2);       // extra edge

    cout << "Maximum matching size: " << b.maxMatching() << endl;
    for (int i = 0; i < b.n; i++)
        if (b.match[i] > i)
            cout << i << " - " << b.match[i] << endl;

    return 0;
}