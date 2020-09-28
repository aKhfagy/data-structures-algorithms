#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::vector;
using ll = long long;

ll memo[101][101][101];

int lcs3(vector<int>& a, vector<int>& b, vector<int>& c) {
    for (int i = 0; i <= a.size(); ++i) {
        for (int j = 0; j <= b.size(); ++j) {
            for (int k = 0; k <= c.size(); ++k) {
                if (i == 0 || j == 0 || k == 0)
                    memo[i][j][k] = 0;
                else if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1])
                    memo[i][j][k] = memo[i - 1][j - 1][k - 1] + 1;
                else
                    memo[i][j][k] = std::max(memo[i - 1][j][k], std::max(memo[i][j - 1][k], memo[i][j][k - 1]));
            }
        }
    }

    return memo[a.size()][b.size()][c.size()];
}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}
