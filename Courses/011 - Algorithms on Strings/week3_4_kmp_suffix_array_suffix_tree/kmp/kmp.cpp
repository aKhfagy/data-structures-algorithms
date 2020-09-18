#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

vector<int> computePrefixVector(string& s) {
    int border = 0, sz = s.size();
    vector<int> ret(sz, 0);

    for (int i = 1; i < sz; ++i) {
        while (border > 0 && s[i] != s[border]) {
            border = ret[border - 1];
        }

        if (s[i] == s[border]) {
            ++border;
            ret[i] = border;
        }

        if (border == 0) {
            ret[i] = 0;
        }
    }

    return ret;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
    vector<int> result;
    string s = pattern + '$' + text;
    int sz = pattern.size(), sz_s = s.size();

    vector<int> prefix = computePrefixVector(s);

    for (int i = sz + 1; i < sz_s; ++i) {
        if (prefix[i] == sz) {
            result.emplace_back(i - 2 * sz);
        }
    }

    return result;
}

int main() {
    string pattern, text;
    cin >> pattern;
    cin >> text;
    vector<int> result = find_pattern(pattern, text);
    for (int i = 0; i < result.size(); ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}
