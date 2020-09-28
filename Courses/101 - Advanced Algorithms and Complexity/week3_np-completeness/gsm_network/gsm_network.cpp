#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        
        cout << (3 * edges.size() + numVertices) << ' ' << (numVertices * 3) << '\n';

        int ctr = 1;

        while(numVertices--) {
            cout << ctr++ << ' ' << ctr++ << ' ' << ctr++ << " 0\n";
        }

        for (const Edge& e : edges) {
            for(int i = 1; i <= 3; ++i)
                cout << -((e.from - 1) * 3 + i) << ' ' << -((e.to - 1) * 3 + i) << " 0\n";
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
