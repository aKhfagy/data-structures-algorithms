#include <iostream>
#include <vector>
using std::vector;
using ll = long long;
long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
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
        sum += memo[i];
        sum %= m;
    }

    return sum % m;
}
int main() {
    long long from, to;
    std::cin >> from >> to;
    ll ans = fib(to) - fib(from - 1);
    if(ans < 0)
        ans += 10;
    ans %= 10;
    std::cout << ans << '\n';
}
