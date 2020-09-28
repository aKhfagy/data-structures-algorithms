#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using std::vector;
using ll = long long;

ll memo[101][101];

int lcs2(vector<int>& a, vector<int>& b) {
    for (int i = 0; i <= a.size(); ++i) {
        for (int j = 0; j <= b.size(); ++j) {
            if (i == 0 || j == 0) {
                memo[i][j] = 0;
            }
            else if (a[i - 1] == b[j - 1]) {
                memo[i][j] = memo[i - 1][j - 1] + 1;
            }
            else {
                memo[i][j] = std::max(memo[i - 1][j], memo[i][j - 1]);
            }
        }
    }

    return memo[a.size()][b.size()];
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::cout << lcs2(a, b) << std::endl;
}
