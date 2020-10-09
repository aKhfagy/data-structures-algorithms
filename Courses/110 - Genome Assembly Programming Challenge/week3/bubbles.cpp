#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
using Graph = vector<set<int>>;
using V2D = vector<vector<int>>;
using Paths = map<int, map<int, vector<set<int>>>>;

int k, t;

class BubbleDetextion {
    class DeBruijn {
    public:
        Graph graph;

        DeBruijn() {
            read();
        }

    private:

        int tempK;
        int v = 0;
        map<string, int> labels;

        void addEdge(string mer) {
            string Lmer = mer.substr(0, k - 1);
            string Rmer = mer.substr(1, k - 1);
            int l, r;

            if (labels.find(Lmer) != labels.end()) {
                l = labels[Lmer];
            }
            else {
                graph.emplace_back(set<int>());
                l = labels[Lmer] = v++;
            }

            if (labels.find(Rmer) != labels.end()) {
                r = labels[Rmer];
            }
            else {
                graph.emplace_back(set<int>());
                r = labels[Rmer] = v++;
            }

            graph[l].insert(r);
        }

        void read() {
            cin >> k >> t;
            string s;
            int ctr = 0;
            while (/*++ctr != 10 && */cin >> s) {
                for (int i = 0; i < (s.size() - k + 1); ++i) {
                    addEdge(s.substr(i, k));
                }
            }
        }
    };

    int numVert;
    Graph graph;
    V2D matrix;
    set<int> in, out;
    Paths paths;
public:
    BubbleDetextion() {
        graph = DeBruijn().graph;
        numVert = graph.size();
        matrix = V2D(numVert, vector<int>(2, 0));
    }

private:
    void canidates() {
        for (int i = 0; i < numVert; ++i) {
            matrix[i][1] = graph[i].size();
            for (int node : graph[i]) {
                ++matrix[node][0];
            }
        }

        for (int i = 0; i < numVert; ++i) {
            if (matrix[i][0] > 1)
                in.insert(i);
            if (matrix[i][1] > 1)
                out.insert(i);
        }
    }

    void addPath(int root, int node, set<int>& vis) {
        if (node != root && in.find(node) != in.end()) {
            set<int> path = vis;
            path.erase(node);
            path.erase(root);
            paths[root][node].push_back(path);
        }
    }

    void DFS(int root, int node, set<int>& vis) {
        addPath(root, node, vis);

        if (vis.size() > t)
            return;

        for (int here : graph[node]) {
            if (vis.find(here) == vis.end()) {
                set<int> temp = vis;
                temp.insert(here);
                DFS(root, here, temp);
            }
        }
    }

    int cnt() {
        int num = 0;

        for (auto& firstPair : paths) {
            for (auto& secondPair : firstPair.second) {
                auto& paths = secondPair.second;
                for (int i = 0; i < paths.size(); ++i) {
                    for (int j = i + 1; j < paths.size(); ++j) {
                        bool flag = true;
                        for (int x : paths[i]) {
                            if (paths[j].find(x) != paths[j].end()) {
                                flag = false;
                                break;
                            }
                        }
                        num += flag;
                    }
                }
            }
        }

        return num;
    }

public:
    int solve() {
        canidates();
        for (int root : out) {
            set<int> vis;
            vis.insert(root);
            DFS(root, root, vis);
        }
        int bubbles = cnt();
        return bubbles;
    }
};

int main() {
    cout << BubbleDetextion().solve() << '\n';
    return 0;
}
