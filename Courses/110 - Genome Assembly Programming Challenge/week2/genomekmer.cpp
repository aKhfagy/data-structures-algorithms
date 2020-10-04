#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <map>
using namespace std;
using Graph = map<string, vector<string>>;
using Path = vector<string>;

Graph deBruijnGraph() {
    Graph graph;
    string s;

    while(cin >> s) {
        graph[s.substr(0, s.size() - 1)].emplace_back(s.substr(1));
    }

    return graph;
}

Path eulerGraph(Graph graph) {
    Path path;
    stack<string> vert;
    vert.push(graph.begin()->first);

    while(vert.size()) {
        string v = vert.top();
        if(graph[v].size()) {
            vert.push(graph[v].back());
            graph[v].pop_back();
        }
        else {
            path.emplace_back(move(v));
            vert.pop();
        }
    }

    reverse(path.begin(), path.end());

    return path;
}

int main() {
    Path path = eulerGraph(deBruijnGraph());
    cout << path.front();   
    for(int i = 1; i < path.size() - 9; ++i) {
        cout << path[i].back();
    }
    puts("");
}
