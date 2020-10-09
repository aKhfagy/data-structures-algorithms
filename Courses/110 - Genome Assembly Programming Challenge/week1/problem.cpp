#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int calc(string& a, string& b) {
    int range = 1 + a.size() - 12;
    for(int i = 0; i < range; ++i) {
        if(strncmp(b.c_str(), a.c_str() + i, a.size() - i) == 0)
            return a.size() - i;
    }

    return 0;
}

string solve(vector<string> input) {
    string genome, s = input.front(), cur;
    genome.reserve(1000);
    genome += s;
    int idx = 0;

    while(input.size() > 1) {
        cur = move(input[idx]);
        input.erase(input.begin() + idx);

        int mx = -1;
        int range = input.size();
        for(int i = 0; i < range; ++i) {
            int temp = calc(cur, input[i]);
            if(mx < temp) {
                mx = temp;
                idx = i;
            }
        }

        genome += input[idx].substr(mx);
    }

    genome.erase(0, calc(input[0], s));
    return genome;
}

int main() {
    vector<string> in;
    in.reserve(1618);
    string s;

    while(cin >> s) {
        if(in.back() != s)
            in.emplace_back(s);
    }

    cout << solve(move(in));
}