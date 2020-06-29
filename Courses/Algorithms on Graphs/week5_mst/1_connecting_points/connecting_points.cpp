#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using std::vector;
using std::priority_queue;
using std::sort;
using ld = long double;

class GraphEdge {
public:
    int start, end;
    ld dist;
    GraphEdge(int u, int v, int x1, int y1, int x2, int y2) :
        start(u), end(v) {
        dist = sqrtl((((ld)x1 - x2) * ((ld)x1 - x2)) + (((ld)y1 - y2) * ((ld)y1 - y2)));
    }

    bool operator< (const GraphEdge& edge) const {
        return dist < edge.dist;
    }

    bool operator> (const GraphEdge& edge) const {
        return dist >= edge.dist;
    }
};

vector <GraphEdge> generate_graph(vector<int> x, vector<int> y) {
    int N = x.size();
    vector <GraphEdge> edges;

    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            edges.emplace_back(GraphEdge(i, j, x[i], y[i], x[j], y[j]));

    sort(edges.begin(), edges.end());

    return edges;
}

vector <int> init_parent(int N) {
    vector <int> parent(N);

    for (int i = 0; i < N; ++i)
        parent[i] = i;

    return parent;

}

int find(int node, vector<int>& parent) {
    return parent[node] = (parent[node] == node) ? node : find(parent[node], parent);
}

void join(int u, int v, vector<int>& parent) {
    u = find(u, parent);
    v = find(v, parent);

    if (u != v)
        parent[u] = v;
}

double minimum_distance(vector<int> x, vector<int> y) {
    double result = 0.;
    int N = x.size();
    
    vector <GraphEdge> edges = generate_graph(x, y);
    vector <int> parent = init_parent(N);

    for (GraphEdge edge : edges) {

        if (find(edge.start, parent) != find(edge.end, parent)) {
            result += edge.dist;

            join(edge.start, edge.end, parent);
        }

    }

    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
