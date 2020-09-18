#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using ll = long long;
using std::vector;

ll memo[int(1e4) + 1][300];

int optimal_weight(int W, const vector<int>& w) {

    for (int i = 1; i <= w.size(); ++i) {
        for (int j = 1; j <= W; ++j) {
            memo[j][i] = memo[j][i - 1];

            if (w[i - 1] <= j) {
                memo[j][i] = std::max(memo[j][i], memo[j - w[i - 1]][i - 1] + w[i - 1]);
            }
        }
    }

    return memo[W][w.size()];
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}
