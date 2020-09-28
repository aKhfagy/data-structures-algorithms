#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using std::vector;
using std::bitset;
using ll = long long;
typedef vector<vector<ll> > Matrix;
typedef std::pair<ll, vector<ll> > Tour;

const int INF = 1e9;

struct Node {
    ll dist;
    ll parent;
    Node(): dist(INF), parent(0) {}
    Node(ll d, ll p): dist(d), parent(p) {}
}; 

struct TSP {
    ll size;
    vector <vector<Node>> cost;

    TSP(Matrix matrix): 
        size(matrix.size()), 
        cost(1 << size, vector<Node>(size)) {
            for(int i = 1; i < size; ++i) {
                cost[1 << i][i] = Node(matrix[0][i], 0);
            }
    }

    TSP() {
        
    }
};

TSP tsp;

vector <ll> getSubsets(int n) {
    vector<ll> subsets;

    bitset<16> bits = n;

    for(int i = 0; i < bits.size(); ++i) {
        if(bits[i])
            subsets.emplace_back(i + 1);
    }

    return subsets;
}

Tour backtrack(const Matrix& graph) {
    Tour tour;

    Node node;
    ll bits = (1 << ::tsp.size) - 2;

    for(int i = 1; i < ::tsp.size; ++i) {
        if(node.dist > ::tsp.cost[bits][i].dist + graph[i][0]) {
            node = Node(::tsp.cost[bits][i].dist + graph[i][0], i);
        }
    }

    if(node.dist == INF) {
        return Tour(-1, {});
    }

    tour.second.reserve(::tsp.size);

    tour.first = node.dist;

    tour.second.emplace_back(1);

    for(int i = 0; i < tsp.size - 1; ++i) {
        tour.second.emplace_back(node.parent + 1);
        node.parent = ::tsp.cost[bits][node.parent].parent;
        bits ^= (1 << (tour.second.back() - 1));
    }

    return tour;
}

Matrix read_data() {
    ll vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<ll>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        ll from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }
    return graph;
}

Tour optimal_path(const Matrix& graph) {
    ::tsp = TSP(graph);

    for(ll i = 2; i < (1 << (tsp.size - 1)); ++i) {
        if(i & (i - 1)) {
            vector<ll> subsets = getSubsets(i);
            ll bits = i * 2;

            for(ll subset : subsets) {
                ll parent = bits ^ (1 << subset);
                Node node;

                for(ll s : subsets) {
                    if(::tsp.cost[parent][s].dist + graph[s][subset] < 
                        node.dist && subset != s) {
                            node = Node(::tsp.cost[parent][s].dist 
                            + graph[s][subset], s);
                        }
                }

                ::tsp.cost[bits][subset] = node;
            }
        }
    }

    return backtrack(graph);
}

void print_answer(const std::pair<ll, vector<ll> >& answer) {
    std::cout << answer.first << "\n";
    if (answer.first == -1)
        return;
    const vector<ll>& path = answer.second;
    for (size_t i = 0; i < path.size(); ++i)
        std::cout << path[i] << " ";
    std::cout << "\n";
}

int main() {
    print_answer(optimal_path(read_data()));
    return 0;
}
