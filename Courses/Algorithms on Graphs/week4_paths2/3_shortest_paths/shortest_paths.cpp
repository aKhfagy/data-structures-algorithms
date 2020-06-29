#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void shortest_paths(vector<vector<int> >& adj, vector<vector<int> >& cost,
    int s, vector<long long>& distance, vector<int>& reachable, vector<int>& shortest) {

    int N = adj.size();

    distance[s] = 0;
    reachable[s] = 1;

    for (int dummy = 1; dummy < N; ++dummy) {
        bool flag = false;

        for (int node = 0; node < N; ++node) {
            if (distance[node] == std::numeric_limits<long long>::max())
                continue;

            auto it = cost[node].begin();

            for (int child : adj[node]) {
                int price = *it;
                if (distance[child] > distance[node] + price) {
                    flag = true;
                    distance[child] = distance[node] + price;
                }
                ++it;
            }
        }

        if (!flag) {
            for (int pos = 0; pos < N; ++pos) {
                if (distance[pos] < std::numeric_limits<long long>::max())
                    reachable[pos] = 1;
            }
        }
    }

    for (int pos = 0; pos < N; ++pos) {
        if (distance[pos] < std::numeric_limits<long long>::max())
            reachable[pos] = 1;
    }

    for (int node = 0; node < N; ++node) {
        if (distance[node] == std::numeric_limits<long long>::max())
            continue;

        auto it = cost[node].begin();

        for (int child : adj[node]) {
            int price = *it;
            ++it;
            if (distance[child] > distance[node] + price) {

                distance[child] = distance[node] + price;

                if (reachable[child] == 2)
                    continue;

                queue <int> q;

                q.push(child);

                reachable[child] = 2;

                while (q.size()) {
                    int here = q.front();
                    q.pop();

                    for (int there : adj[here]) {
                        if (reachable[there] != 2) {
                            reachable[there] = 2;
                            q.push(there);
                        }
                    }
                }
            }
        }
    }

}

int main() {
    int n, m, s;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, std::numeric_limits<long long>::max());
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);
    shortest_paths(adj, cost, s, distance, reachable, shortest);
    for (int i = 0; i < n; i++) {
        if (reachable[i] == 0) {
            std::cout << "*\n";
        }
        else if (reachable[i] == 2) {
            std::cout << "-\n";
        }
        else {
            std::cout << distance[i] << "\n";
        }
    }
}
