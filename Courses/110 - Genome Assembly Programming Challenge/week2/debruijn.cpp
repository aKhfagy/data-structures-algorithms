#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <string>
#include <stack>
#include <map>
#include <set>
using namespace std;
using Graph = map<string, set<string>>;
using Path = vector<string>;

Graph deBruijnGraph(const int K) {
    Graph graph;
    int n = 1 << K;

    for(int i = 0; i < n; ++i) {
        string temp[] = {
            bitset<16>{i}.to_string().substr(16 - K, K - 1),
            bitset<16>{i * 2 % n}.to_string().substr(16 - K),
            bitset<16>{i * 2 % n + 1}.to_string().substr(16 - K)
        };

        graph[temp[0]].emplace(temp[1].substr(0, K - 1));
        graph[temp[0]].emplace(temp[2].substr(0, K - 1));
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
            vert.push(*graph[v].begin());
            graph[v].erase(graph[v].begin());
        }
        else {
            path.emplace_back(v);
            vert.pop();
        }
    }

    reverse(path.begin(), path.end());

    return path;
}

void display(Path path, const int K) {
    for(int i = 0; i < path.size() - 1; ++i) {
        cout << path[i].substr(0, path[i].size() - K);
    }
    puts("");
}

int main() {
    int k; cin >> k;
    display(eulerGraph(deBruijnGraph(k)), k - 2);
}
