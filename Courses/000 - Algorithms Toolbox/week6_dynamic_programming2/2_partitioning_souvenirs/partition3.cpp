#include <iostream>
#include <vector>
using ll = long long;

using std::vector;

ll memo[601][31];

int partition3(vector<int>& A) {

    if (A.size() < 3)
        return false;

    ll sum = 0;

    for (int x : A) {
        sum += x;
    }

    if (sum % 3 != 0)
        return false;

    sum /= 3;

    ll ret = 0;

    for (int i = 1; i <= sum; ++i) {
        for (int j = 1; j <= A.size(); ++j) {
            memo[i][j] = memo[i][j - 1];

            if (A[j - 1] <= i) {
                ll temp = memo[i - A[j - 1]][j - 1] + A[j - 1];

                if (temp > memo[i][j]) {
                    memo[i][j] = temp;
                }
            }

            ret += (memo[i][j] == sum);
        }
    }

    return ret >= 3;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cin >> A[i];
    }
    std::cout << partition3(A) << '\n';
}
