#include <iostream>
#include <vector>

using std::vector;
using std::pair;

vector<vector<int> > adj;

bool vis[int(1e3)] = {};

void DFS(int node) {
    if (vis[node])
        return;

    vis[node] = true;

    for (int child : adj[node]) {
        DFS(child);
    }

}

int number_of_components() {
    int res = 0, n = adj.size();
    
    for (int node = 0; node < n; ++node) {
        if (!vis[node]) {
            ++res;
            DFS(node);
        }
    }

    return res;
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
    std::cout << number_of_components();
}
