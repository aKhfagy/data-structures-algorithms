#include <iostream>
#include <cmath>
#include <algorithm>
using ll = long long;

ll memo[1001] = {};

int get_change(int m) {

    for (int i = 1; i < 1001; ++i)
        memo[i] = 1e9;

    memo[0] = 0;

    for (int i = 1; i <= m; ++i) {
        memo[i] = std::min(memo[i], memo[i - 1] + 1);
    }

    for (int i = 3; i <= m; ++i) {
        if (memo[i - 3] == 1e9) continue;
        memo[i] = std::min(memo[i], memo[i - 3] + 1);
    }

    for (int i = 4; i <= m; ++i) {
        if (memo[i - 4] == 1e9) continue;
        memo[i] = std::min(memo[i], memo[i - 4] + 1);
    }
    return memo[m];
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
