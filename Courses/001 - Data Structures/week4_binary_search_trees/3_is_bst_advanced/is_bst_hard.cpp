#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::vector;
using std::set;
using std::stack;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

vector<Node> tree;

vector <int> in_order() {
    vector<int> result;
    set <int> process;
    stack <int> not_yet;

    process.insert(-1);
    not_yet.push(0);

    while (not_yet.size()) {
        int i = not_yet.top();

        int left = tree[i].left;
        int right = tree[i].right;
        int key = tree[i].key;

        if (process.find(left) == process.end()) {
            not_yet.push(left);

            if (key == tree[left].key) {
                throw "BinarySearchTreeError";
            }
        }

        else {

            result.emplace_back(key);

            process.insert(i);

            not_yet.pop();

            if (right != -1)
                not_yet.push(right);

        }

    }

    return result;
}

bool IsBinarySearchTree() {
    if (tree.empty()) 
        return true;
    
    vector<int> traversed;

    try {
        traversed = in_order();
    }
    catch (...) {
        return false;
    }

    int n = tree.size();

    if (n != traversed.size())
        return false;

    vector <int> keys(n);

    for (int i = 0; i < n; ++i)
        keys[i] = tree[i].key;

    sort(keys.begin(), keys.end());

    return keys == traversed;
}

int main() {
    int nodes;
    cin >> nodes;
    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }
    if (IsBinarySearchTree()) {
        cout << "CORRECT" << endl;
    }
    else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
