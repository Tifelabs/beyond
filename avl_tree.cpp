#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <set>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height;
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

int height(Node* n) {
    return n ? n->height : 0;
}

int balanceFactor(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

void updateHeight(Node* n) {
    if (n) n->height = 1 + max(height(n->left), height(n->right));
}

// Right rotation
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// Left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; // duplicates not allowed

    updateHeight(root);
    int bf = balanceFactor(root);

    // Left Left
    if (bf > 1 && key < root->left->key)
        return rotateRight(root);

    // Right Right
    if (bf < -1 && key > root->right->key)
        return rotateLeft(root);

    // Left Right
    if (bf > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left
    if (bf < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* minValueNode(Node* node) {
    while (node->left) node = node->left;
    return node;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;

    updateHeight(root);
    int bf = balanceFactor(root);

    if (bf > 1 && balanceFactor(root->left) >= 0)
        return rotateRight(root);
    if (bf > 1 && balanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (bf < -1 && balanceFactor(root->right) <= 0)
        return rotateLeft(root);
    if (bf < -1 && balanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// ---- Added for benchmarking ----

bool contains(Node* root, int key) {
    while (root) {
        if (key == root->key) return true;
        root = key < root->key ? root->left : root->right;
    }
    return false;
}

void destroy(Node* root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

// Runs f() and returns elapsed milliseconds
template <typename F>
double timeMs(F f) {
    auto start = chrono::steady_clock::now();
    f();
    auto end = chrono::steady_clock::now();
    return chrono::duration<double, milli>(end - start).count();
}

void benchmark(int n) {
    // Generate keys up front so RNG cost isn't timed
    mt19937 rng(12345);
    uniform_int_distribution<int> dist(0, n * 10);
    vector<int> keys(n);
    for (int& k : keys) k = dist(rng);

    cout << "\nBenchmark with " << n << " random keys\n";

    // --- AVL tree ---
    Node* root = nullptr;
    size_t found = 0;

    double avlInsert = timeMs([&] {
        for (int k : keys) root = insert(root, k);
    });
    double avlSearch = timeMs([&] {
        for (int k : keys) found += contains(root, k);
    });
    double avlDelete = timeMs([&] {
        for (int i = 0; i < n / 2; i++) root = deleteNode(root, keys[i]);
    });

    cout << "AVL     insert: " << avlInsert << " ms, search: " << avlSearch
         << " ms, delete(half): " << avlDelete << " ms\n";
    destroy(root);

    // --- std::set (red-black tree) for comparison ---
    set<int> s;
    size_t found2 = 0;

    double setInsert = timeMs([&] {
        for (int k : keys) s.insert(k);
    });
    double setSearch = timeMs([&] {
        for (int k : keys) found2 += s.count(k);
    });
    double setDelete = timeMs([&] {
        for (int i = 0; i < n / 2; i++) s.erase(keys[i]);
    });

    cout << "std::set insert: " << setInsert << " ms, search: " << setSearch
         << " ms, delete(half): " << setDelete << " ms\n";

    // Print results so the compiler can't optimize the work away
    cout << "(sanity check: found " << found << " / " << found2 << ")\n";
}

// Example usage
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    root = deleteNode(root, 30);
    cout << "After deleting 30: ";
    inorder(root);
    cout << endl;

    destroy(root);

    benchmark(1000000);

    return 0;
}