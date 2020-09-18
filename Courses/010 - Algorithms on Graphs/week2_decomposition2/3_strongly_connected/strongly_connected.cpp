#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using std::stack;

void DFS(vector<vector<int> >& adj, vector <bool>& used, int node, stack <int>& recursion_stack) {
    if (used[node])
        return;

    used[node] = true;

    for (int child : adj[node]) {
        DFS(adj, used, child, recursion_stack);
    }

    recursion_stack.emplace(node);
}

vector <vector <int>> reverse_edges(vector<vector<int>> adj) {
    int N = adj.size();

    vector <vector <int>> adj_reverse(N);

    for (int node = 0; node < N; ++node) {
        
        for (int child : adj[node]) {
            adj_reverse[child].emplace_back(node);
        }
    }

    return adj_reverse;
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
    int N = adj.size();

    int result = 0;
    
    stack <int> recursion_stack;

    vector <vector <int>> adj_reverse = reverse_edges(adj);
    
    vector <bool> used(N, false);

    for (int node = 0; node < N; ++node)
        DFS(adj, used, node, recursion_stack);

    used = vector<bool>(N, false);

    while (!recursion_stack.empty()) {
        int node = recursion_stack.top();

        recursion_stack.pop();

        stack <int> dummy;

        if (!used[node]) {
            DFS(adj_reverse, used, node, dummy);
            ++result;
        }
    }

    return result;
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
    std::cout << number_of_strongly_connected_components(adj);
}
