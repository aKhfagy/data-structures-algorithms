#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;
using std::max;
using ll = long long;

Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

int dfs(const Graph &tree, int vertex, int parent, std::vector<ll>& sum) {
    
    const Vertex& here = tree[vertex];

    if(sum[vertex] == -1) {
        if(here.children.size() == 0) {
            sum[vertex] = here.weight;
        }
        else {

            ll m1 = here.weight;
            for(int child : here.children) {
                if(child == parent)
                    continue;
                for(int grandchildren : tree[child].children){
                    if(grandchildren != vertex) {
                        m1 += dfs(tree, grandchildren, child, sum);
                    }
                }
            }

            ll m0 = 0;
            for(int child : here.children) {
                if(child != parent) {
                    m0 += dfs(tree, child, vertex, sum);
                }
            }

            sum[vertex] = max(m1, m0);
        }
    }

    return sum[vertex];
}

int MaxWeightIndependentTreeSubset(const Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    
    std::vector<ll> sum = std::vector<ll>(size, -1);

    return dfs(tree, 0, -1, sum);
}

int main() {
    const Graph graph = ReadTree();
    std::cout << MaxWeightIndependentTreeSubset(graph);
}
