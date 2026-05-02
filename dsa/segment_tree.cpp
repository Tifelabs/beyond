#include <iostream>
#include <vector>

using ll = long long;

class Segment tree{
private:
    int n;
    std::vector<ll> tree;

    void build(int node, int start, int end, std::vector<int> &arr){
        if(start == end){
            tree[node] = arr[start];
            return 0;
        }

        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid, arr);
        build(2 * node + 2, mid + 1, end, arr);

        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    void update(int node, int start, int end, int idx, ll val){
        
    }
}