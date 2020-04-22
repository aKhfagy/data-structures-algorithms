#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using ll = long long;
using std::vector;

ll memo[int(1e6) + 1] = {};

vector<int> optimal_sequence(int n) {
    std::vector<int> sequence;

    memo[1] = 1;

    for (int i = 2; i <= n; ++i) {
        vector <int> elem;
        elem.emplace_back(i - 1);
        if ((i & 1) == 0)
            elem.emplace_back(i / 2);
        if (i % 3 == 0)
            elem.emplace_back(i / 3);

        memo[i] = memo[elem.front()] + 1;

        for (int j : elem) {
            memo[i] = std::min(memo[i], memo[j] + 1);
        }
    }

    sequence.emplace_back(n);

    while (n > 1) {
        //std::cout << n << '\n';
        vector <int> elem;
        elem.emplace_back(n - 1);
        if ((n & 1) == 0) {
            elem.emplace_back(n / 2);
        }
        if (n % 3 == 0) {
            elem.emplace_back(n / 3);
        }

        ll mn = memo[elem.front()];
        //std::cout << elem.size() << '\n';
        for (int e : elem) {
            if (mn >= memo[e]) {
                //std::cout << e << ' ';
                mn = memo[e];
                n = e;
            }
        }

        //puts("");

        sequence.emplace_back(n);
    }

    reverse(sequence.begin(), sequence.end());
    return sequence;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
}
