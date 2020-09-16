#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <queue>
#include <limits>

using std::vector;
using std::cin;
using std::cout;
using std::queue;
using std::numeric_limits;
/*
class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool>> adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

 private:
  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    int num_left = adj_matrix.size();
    int num_right = adj_matrix[0].size();
    vector<int> matching(num_left, -1);
    vector<bool> busy_right(num_right, false);
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j)
        if (matching[i] == -1 && !busy_right[j] && adj_matrix[i][j]) {
          matching[i] = j;
          busy_right[j] = true;
        }
    return matching;
  }
};
*/
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

    const size_t flights;

public:
    explicit FlowGraph(size_t n, size_t f): graph(n), flights(f) {}

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

    size_t get_flights() const {
        return flights;
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
    int n, m; cin >> n >> m;

    FlowGraph graph(n + m + 2, n);

    for(int i = 0; i < n; ++i) 
        graph.add_edge(0, i + 1, 1);
    
    for (int i = 1; i <= n; ++i) 
        for(int j = 0; j < m; ++j) {
            bool flag;
            cin >> flag;
            if(flag) 
                graph.add_edge(i, n + j + 1, 1);
        }
    
    for(int i = n + 1; i <= m + n; ++i) 
        graph.add_edge(i, n + m + 1, 1);
    
    return graph;
}

void display_result(const FlowGraph& graph) {
    int flights = graph.get_flights();

    for(int i = 1; i <= flights; ++i) {
        int crew = -1; // the default answer

        for(size_t id : graph.get_ids(i)) {
             const FlowGraph::Edge &e = graph.get_edge(id);
             
             if(e.flow == 1) {
                 crew = e.to - flights;
                 break;
             }
        }
        cout << crew << " \n"[i == flights];
    }
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

void max_flow(FlowGraph& graph, int from, int to) {
    vector<int> parent;

    do {
        int min = numeric_limits<int>::max();

        parent = compute_Gf(graph, from, to);

        if(parent[to] != -1) {
            
            for (int u = parent[to]; u != -1; u = parent[graph.get_edge(u).from]) 
                min = std::min(min, 
                graph.get_edge(u).capacity - graph.get_edge(u).flow);

            for (int u = parent[to]; u != -1; u = parent[graph.get_edge(u).from]) 
                graph.add_flow(u, min);
        }

    } while(parent[to] != -1);

}

void solve() {
    FlowGraph graph = read_data();
    max_flow(graph, 0, graph.size() - 1);
    display_result(graph);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  solve();
  return 0;
}
