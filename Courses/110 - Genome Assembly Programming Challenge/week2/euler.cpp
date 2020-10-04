#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
using namespace std;
using Graph = vector<vector<int>>;

bool degrees(const vector<int>& in, const vector<int>& out) {
    for(int i = 0; i < in.size(); ++i) {
        if(in[i] != out[i])
            return true;
    }
    return false;
}

vector<int> build(Graph& graph) {
    stack<int> vert;
    vector<int> path;
    vert.push(0);

    while(vert.size()) {
        int v = vert.top();
        if(graph[v].size()) {
            vert.push(graph[v].back());
            graph[v].pop_back();
        }
        else {
            path.emplace_back(v);
            vert.pop();
        }
    }

    reverse(path.begin(), path.end());
    path.pop_back();

    return path;
}

void read(Graph& graph, vector<int>& in, vector<int>& out) {
    int numV, numE; cin >> numV >> numE;
    graph = Graph(numV);
    in = out = vector<int>(numV);

    while(numE--) {
        int from, to; cin >> from >> to;
        --from, --to;
        graph[from].emplace_back(to);
        ++in[to];
        ++out[from];
    }
}

void solve() {
    Graph graph;
    vector<int> in, out;
    read(graph, in, out);
    if(degrees(in, out)) {
        puts("0");
    }
    else {
        vector<int> path = build(graph);
        puts("1");
        for(int here : path) {
            cout << here + 1 << ' ';
        }
        puts("");
    }
}

int main() {
    solve();
}
