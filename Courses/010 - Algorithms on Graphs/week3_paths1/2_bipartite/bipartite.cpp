#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> >& adj) {

    int N = adj.size();

    queue <int> frontier;

    vector <int> color(N, -1);

    frontier.emplace(0);

    color[0] = 1;

    while (!frontier.empty()) {
        int node = frontier.front();
        frontier.pop();

        for (int child : adj[node]) {
            if (color[child] == -1) {
                color[child] = color[node] ^ 1;
                frontier.emplace(child);
            }
            else if (color[child] == color[node]) {
                return 0;
            }
        }
    }

    return 1;
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
    std::cout << bipartite(adj);
}
