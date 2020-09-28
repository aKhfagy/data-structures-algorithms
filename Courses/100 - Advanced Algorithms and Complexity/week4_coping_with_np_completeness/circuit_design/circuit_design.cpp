#include <iostream>
#include <vector>
#include <numeric>
#include <stack>
#include <algorithm>
#include <cmath>
#include <unordered_map>
using namespace std;
struct Clause {
    int firstVar;
    int secondVar;
};

const long long MIN = numeric_limits<int>::min();

struct Node {
    int id, index, low;
    bool use;
    vector<int> edges;
    Node(): id(-1), low(MIN), index(MIN), use(false) {}
};

using Graph = unordered_map<int, Node>;

struct TwoSatisfiability {
    int numVars, ctr, here, id;
    bool flag;
    Graph graph;
    vector<bool> ans;
    stack<int> st;

    TwoSatisfiability(int n, int m) : 
        numVars(n), ctr(0), here(0),
        id(0), graph(2 * n), flag(true),
        ans(n, false) { read(m); }

    bool isSatisfiable() {
        solve();
        return flag;
    }

    void process(int node) {
        Node& cur = graph[node];
        cur.index = cur.low = ctr++;
        cur.use = true;
        st.push(node);

        for(int here : cur.edges) {
            if(graph[here].index == MIN) {
                process(here);
                cur.low = min(cur.low, graph[here].low);
            }
            else if(graph[here].use) {
                cur.low = min(cur.low, graph[here].index);
            }
        }

        if(cur.low == cur.index) {
            do {
                here = st.top(); st.pop();
                if(id == graph[-here].id) {
                    flag = false;
                    return;
                }

                graph[here].use = false;
                graph[here].id = id;
                ans[abs(here) - 1] = here < 0 ? true : false;

            } while(here != node);
            ++id;
        }
    }

    void solve() {
        for(int i = -numVars; i <= numVars; ++i) 
            if(graph[i].index == MIN && i != 0) 
                process(i);
    }

    void read(int range) {
        for (int i = 0; i < range; ++i) {
            int x, y;
            cin >> x >> y;
            graph[-x].edges.emplace_back(y);
            graph[-y].edges.emplace_back(x);
        }
    } 

};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    TwoSatisfiability twoSat(n, m);

    if (twoSat.isSatisfiable()) {
        cout << "SATISFIABLE" << endl;
        vector<bool> ans = twoSat.ans;
        int sz = ans.size();
        for(int i = 1; i <= sz; ++i) {
            cout << (ans[i - 1] ? i : -i) << " \n"[i == sz];
        }
    } else {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}
