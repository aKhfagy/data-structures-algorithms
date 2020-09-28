#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;
using std::reverse;

int in[int(1e5)];

void dfs(vector<vector<int> >& adj, vector<bool>& used, vector<int>& order, int node) {
    if (used[node])
        return;

    used[node] = true;

    for (int child : adj[node])
        dfs(adj, used, order, child);

    order.emplace_back(node);
}

vector<int> toposort(vector<vector<int> > adj) {
    vector<bool> used(adj.size(), 0);
    vector<int> order;

    int n = adj.size();

    for (int node = 0; node < n; ++node) {
        if (in[node] == 0)
            dfs(adj, used, order, node);
    }

    reverse(order.begin(), order.end());

    return order;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        ++in[y - 1];
    }
    vector<int> order = toposort(adj);
    for (size_t i = 0; i < order.size(); i++) {
        std::cout << order[i] + 1 << " ";
    }
}
