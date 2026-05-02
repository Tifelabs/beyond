#include <iostream>
#include <vector>

using ll = long long;
class SegmentTree {
private:
    int n;
    std::vector<ll> tree;

    void build(int node, int start, int end, std::vector<int> &arr){
        if(start == end){
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid, arr);
        build(2 * node + 2, mid + 1, end, arr);

        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    void update(int node, int start, int end, int idx, ll val){
        if(start == end){
            tree[node] = val;
            return;
        }

        int mid = (start + end) / 2;

        if(idx <= mid)
            update(2 * node + 1, start, mid, idx, val);
        else    
            update(2 * node + 2, mid + 1, end, idx, val);

        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    ll query(int node, int start, int end, int l, int r){
        if(r < start || end < l){
            return 0;
        }
        if(l <= start && end <= r){
            return tree[node];
        }

        int mid = (start + end) / 2;
        ll leftSum = query(2 * node + 1, start, mid, l, r);
        ll rightSum = query(2 * node + 2, mid + 1, end, l, r);

        return leftSum + rightSum;
    }

public:
    SegmentTree(std::vector<int>& arr){
        n = arr.size();
        tree.resize(4 * n + 10, 0);
        build(0, 0, n - 1, arr);
    }

    void update(int idx, ll val){
        update(0, 0, n - 1, idx, val);    
    }

    ll query(int left, int right){
        return query(0, 0, n - 1, left, right);
    }
};

int main(){
    std::vector<int> arr = {1, 3, 5, 7, 9, 11};

    SegmentTree st(arr);

    std::cout << "Sum of range [1, 4]: " << st.query(1, 4) << "\n";
    st.update(2, 10);
    std::cout << "After Update, Sum of range [1 - 4]: " << st.query(1, 4) << "\n";
    return 0;
}