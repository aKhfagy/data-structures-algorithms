#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using ll = long long;

template <class T>
class Node {
public:
    T idx;
    T dist;

    Node(): idx(0), dist(0) {}
    Node(T i, T d) : idx(i), dist(d) {}

    bool operator< (const Node& node) const {
        return dist < node.dist;
    }

    bool operator> (const Node& node) const {
        return dist >= node.dist;
    }
};

int distance(vector<vector<int> >& adj, vector<vector<int> >& cost, int s, int t) {
    int N = adj.size();

    vector <ll> dist(N, 2e18);

    dist[s] = 0;

    priority_queue <Node<ll>> pq;

    pq.push(Node<ll>(s, 0));

    while (pq.size()) {
        Node<ll> node = pq.top();
        pq.pop();

        for (int i = 0; i < adj[node.idx].size(); ++i) {
            int child = adj[node.idx][i];

            if (dist[child] > dist[node.idx] + cost[node.idx][i]) {
                dist[child] = dist[node.idx] + cost[node.idx][i];
                pq.push(Node<ll>(child, dist[child]));
            }
        }
    }

    return dist[t] == 2e18 ? -1 : dist[t];
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
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
}
