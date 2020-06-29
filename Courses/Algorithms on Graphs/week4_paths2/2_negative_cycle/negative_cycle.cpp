#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> >& adj, vector<vector<int> >& cost) {
    int N = adj.size();
    adj.emplace_back(vector<int>(N));
    cost.emplace_back(vector<int>(N, 0));

    for (int i = 0; i < N; ++i)
        adj[N][i] = i;

    vector <int> dist(N + 1, 2e8);

    dist[N] = 0;

    for (int dummy = 1; dummy <= N; ++dummy) {
        bool flag = false;

        for (int node = 0; node <= N; ++node) {
            int idx = 0;

            auto it = cost[node].begin();

            for (int child : adj[node]) {
                int price = *it;
                if (dist[child] > dist[node] + price) {
                    flag = true;
                    dist[child] = dist[node] + price;
                }
                ++it;
            }
        }

        if (flag && (dummy == N))
            return 1;
    }

    return 0;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle(adj, cost);
}
