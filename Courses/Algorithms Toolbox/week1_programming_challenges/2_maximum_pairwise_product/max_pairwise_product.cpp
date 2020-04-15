#include <iostream>
#include <vector>
#include <algorithm>
using ll = long long;

ll MaxPairwiseProduct(const std::vector<int>& numbers) {
    int n = numbers.size();
    int idx_1 = -1, idx_2 = -1, mx = -1;

    for(int i = 0; i < n; ++i) 
        if(numbers[i] > mx) {
            mx = numbers[i];
            idx_1 = i;
        }

    mx = -1;

    for(int i = 0; i < n; ++i) {
        if(idx_1 == i)
            continue;
        if(numbers[i] > mx) {
            mx = numbers[i];
            idx_2 = i;
        }
    }

    return 1ll * numbers[idx_1] * numbers[idx_2];
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
