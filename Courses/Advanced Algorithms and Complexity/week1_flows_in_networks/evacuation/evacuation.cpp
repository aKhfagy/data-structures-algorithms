#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::queue;
using std::numeric_limits;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

vector <int> compute_Gf(const FlowGraph& graph, int s, int t) {
    // This function performs BFS

    vector<int> parent(graph.size(), -1);
    queue<int> frontire;

    frontire.push(s);

    while (!frontire.empty()) {
        int node = frontire.front();
        frontire.pop();

        for (auto id : graph.get_ids(node)) {
            const FlowGraph::Edge& e = graph.get_edge(id);

            if (parent[e.to] == -1 && e.capacity > e.flow && e.to != s) {
                parent[e.to] = id;
                frontire.push(e.to);
            }
        }
    }
    
    return parent;
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    
    vector<int> parent;

    do {
        int min = numeric_limits<int>::max();

        parent = compute_Gf(graph, from, to);

        if(parent[to] != -1) {
            
            for (int u = parent[to]; u != -1; u = parent[graph.get_edge(u).from]) 
                min = std::min(min, 
                graph.get_edge(u).capacity - graph.get_edge(u).flow);
            
            flow += min;

            for (int u = parent[to]; u != -1; u = parent[graph.get_edge(u).from]) 
                graph.add_flow(u, min);
        }

    } while(parent[to] != -1);

    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
