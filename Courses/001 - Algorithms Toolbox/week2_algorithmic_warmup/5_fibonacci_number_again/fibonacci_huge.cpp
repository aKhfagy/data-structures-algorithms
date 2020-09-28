#include <iostream>
using ll = long long;
long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

const int N = 1e5;

ll memo[N];

ll fib(ll n, ll m) {
    if(n == 0)
        return 0;
    memo[0] = 0;
    memo[1] = 1;
    int period = 2;
    for(int i = 2; i <= n; ++i, ++period) {
        memo[i] = ((memo[i - 1] % m) + (memo[i - 2] % m)) % m;
        if(memo[i - 1] == 0 && memo[i] == 1) {
            --period;
            break;
        }
    }
    return memo[n % period];
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << fib(n, m) << '\n';
}
