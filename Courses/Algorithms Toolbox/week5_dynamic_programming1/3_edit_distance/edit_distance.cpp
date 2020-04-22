#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using ll = long long;
using std::string;

ll memo[101][101];

int edit_distance(const string& str1, const string& str2) {
    for (int i = 0; i < 101; ++i) {
        for (int j = 0; j < 101; ++j) {
            memo[i][j] = 2e9;
        }
    }

    for (int i = 0; i <= str1.size(); ++i)
        memo[i][0] = i;

    for (int i = 0; i <= str2.size(); ++i)
        memo[0][i] = i;

    for (int i = 1; i <= str1.size(); ++i) {
        for (int j = 1; j <= str2.size(); ++j) {
            memo[i][j] = std::min(memo[i - 1][j] + 1, 
                std::min(memo[i][j - 1] + 1, memo[i - 1][j - 1] + (str1[i - 1] != str2[j - 1])));
        }
    }

    return memo[str1.size()][str2.size()];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
