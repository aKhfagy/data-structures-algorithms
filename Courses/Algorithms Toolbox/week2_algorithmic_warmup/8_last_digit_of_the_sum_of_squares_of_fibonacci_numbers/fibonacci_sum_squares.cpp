#include <iostream>
using ll = long long;
int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}
const int N = 1e5;

ll memo[N];

ll fib(ll n, ll m = 10) {
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

    ll num = n % period;

    ll sum = 0;

    for(int i = 0; i <= num; ++i) {
        sum += ((memo[i] * memo[i]) % m);
        sum %= m;
    }

    return sum % m;
}
int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fib(n);
}
