#include <iostream>
#include <vector>

using std::vector;
using std::pair;

vector<vector<int> > adj;

bool vis[int(1e3)] = {};

bool DFS(int node, int goal) {
    if (node == goal)
        return true;

    if (vis[node])
        return false;

    vis[node] = true;

    bool flag = false;

    for (int child : adj[node]) {
        flag |= DFS(child, goal);
    }

    return flag;
}

int reach(int x, int y) {
    return DFS(x, y);
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    adj = vector <vector<int>>(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int x, y;
    std::cin >> x >> y;
    std::cout << reach(x - 1, y - 1);
}
