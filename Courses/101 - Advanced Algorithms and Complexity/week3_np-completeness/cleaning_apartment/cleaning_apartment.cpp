#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertHampathToSat {
    int numVertices;
    int numEdges;
    long long numStream;
    vector<Edge> edges;
    vector<vector<bool>> flags;
    vector<vector<int>> nums;
    string stream;

    ConvertHampathToSat(int n, int m) :
        numVertices(n),
        numEdges(m),
        edges(m),
        flags(n, vector<bool>(n, false)),
        nums(n, vector<int>(n)),
        numStream(0) {  
        int ctr = 1;
        for(int i = 0; i < numVertices; ++i)
            for(int j = 0; j < numVertices; ++j)
                nums[i][j] = ctr++;
    }

    void readEdges() {
        for (int i = 0; i < numEdges; ++i) {
            cin >> edges[i].from >> edges[i].to;
            flags[edges[i].from - 1][edges[i].to - 1] = true;
            flags[edges[i].to - 1][edges[i].from - 1] = true;
        }
    }

    void eachVertixInPath() {
        for(int i = 0; i < numVertices; ++i, ++numStream) {
            for(int j = 0; j < numVertices; ++j) 
                stream += to_string(nums[i][j]) + ' ';
            stream += "0\n";
        }
    }

    void eachVertixInPathNoRepeated() {
        for(int i = 0; i < numVertices; ++i) 
            for(int j = 0; j < numVertices; ++j) 
                for(int k = i + 1; k < numVertices; ++k, ++numStream)
                    stream += to_string(-nums[i][j]) + ' ' + to_string(-nums[k][j]) + " 0\n";
    }

    void eachPathVertixOccupied() {
        for(int i = 0; i < numVertices; ++i, ++numStream) {
            for(int j = 0; j < numVertices; ++j) 
                stream += to_string(nums[j][i]) + ' ';
            stream += "0\n";
        }
    }

    void eachPathVertixOccupiedNoRepeated() {
        for(int i = 0; i < numVertices; ++i) 
            for(int j = 0; j < numVertices; ++j) 
                for(int k = j + 1; k < numVertices; ++k, ++numStream)
                    stream += to_string(-nums[i][j]) + ' ' + to_string(-nums[i][k]) + " 0\n";
    }

    void verticiesNonAdjacentInPath() {
        for(int i = 0; i < numVertices; ++i)
            for(int j = 0; j < numVertices; ++j)
                if(!flags[i][j] && i != j)
                    for(int k = 0; k < numVertices - 1; ++k, ++numStream)
                        stream += to_string(-nums[i][k]) + ' ' + to_string(-nums[j][k + 1]) + " 0\n";
    }

    void printEquisatisfiableSatFormula() {
        stream.reserve(400000);

        eachVertixInPath();
        eachVertixInPathNoRepeated();
        eachPathVertixOccupied();
        eachPathVertixOccupiedNoRepeated();
        verticiesNonAdjacentInPath();

        cout << numStream << ' ' << numVertices * numVertices << '\n' << stream;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);

    converter.readEdges();
    converter.printEquisatisfiableSatFormula();

    return 0;
}
