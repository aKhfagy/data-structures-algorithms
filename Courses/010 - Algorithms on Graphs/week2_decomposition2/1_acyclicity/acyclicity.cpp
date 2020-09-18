#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool dfs(vector<vector<int> >& adj, vector <bool> &used, vector <bool>& recursion_stack, int node) {
    if (used[node])
        return false;

    used[node] = true;
    recursion_stack[node] = true;

    bool flag = false;

    for (int child : adj[node]) {
        if (!used[child] && dfs(adj, used, recursion_stack, child))
            return true;
        else if (recursion_stack[child])
            return true;
    }

    recursion_stack[node] = false;

    return flag;
}

int acyclic(vector<vector<int> >& adj) {
    
    int N = adj.size();

    vector <bool> used(N, false);
    vector <bool> recursion_stack(N, false);

    for (int node = 0; node < N; ++node)
        if (dfs(adj, used, recursion_stack, node))
            return 1;

    return 0;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << acyclic(adj);
}
