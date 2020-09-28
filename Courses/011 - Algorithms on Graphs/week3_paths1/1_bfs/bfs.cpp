#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> >& adj, int s, int t) {

    int N = adj.size();

    queue <int> frontier;

    vector <bool> used(N, false);
    vector <long long> depth(N, 0);

    used[s] = true;
    frontier.emplace(s);

    while (!frontier.empty()) {
        int node = frontier.front();
        frontier.pop();

        if (node == t)
            return depth[node];

        for (int child : adj[node]) {
            if (!used[child]) {
                used[child] = true;
                depth[child] = depth[node] + 1;
                frontier.emplace(child);
            }
        }
    }


    return -1;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}
