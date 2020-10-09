#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using std::vector;
using std::string;
using std::move;
using std::set;
using std::pair;
using std::map;
using Graph = map<string, set<string>>;

vector<string> read() {
    vector <string> input;
    string s;
    while(std::cin >> s)
        input.emplace_back(move(s));

    return input;
}

short checkEuler(Graph graph) {
    for(pair<string, set<string>> here : graph) {
        if(here.second.empty())
            return 2;
        if(here.second.size() > 1)
            return 3;
    }
    return 1;
}

Graph deBruijnGraph(vector<string>& input, int mer) {
    Graph graph;
    for(string s : input) {
        for(int i = 0; i + mer < s.size(); ++i) {
            graph[s.substr(i, mer - 1)].emplace(s.substr(i + 2, mer - 1));
            if(i + mer + 1 < s.size())
                graph[s.substr(i + 2, mer - 1)];
        }
    }
    return graph;
}

int BS(vector<string> input, int l, int r) {
    while(l <= r) {
        int mid = (l + r) / 2;
        short check = checkEuler(deBruijnGraph(input, mid));
        if(check == 1) { // one
            return mid;
        } else if(check == 2) { // no
            r = mid - 1;
        }
        else { // many
            l = mid + 1;
        }
    }
    return -1;
}

int main() {
    vector<string> input = read();
    int mer = input.front().size();
    std::cout << BS(input, 0, mer) << '\n';
    return 0;
}
