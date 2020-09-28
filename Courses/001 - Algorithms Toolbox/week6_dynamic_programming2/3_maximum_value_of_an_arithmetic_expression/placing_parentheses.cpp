#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using std::vector;
using std::string;
using std::max;
using std::min;
using ll = long long;

long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    }
    else if (op == '+') {
        return a + b;
    }
    else if (op == '-') {
        //puts("HAHA");
        return b - a;
    }
    else {
        assert(0);
    }
}

ll mi[30][30] = {};
ll ma[30][30] = {};

long long get_maximum_value(const string& exp) {
    int n = exp.size() / 2 + (exp.size() & 1);

    for (int i = 0; i < n; ++i) {
        int num = exp[2 * i] - '0';
        mi[i][i] = ma[i][i] = num;
    }

    for (int s = 0; s < n - 1; ++s) {
        for (int i = 0; i < n - s - 1; ++i) {
            int j = i + s + 1;

            ll mn = LLONG_MAX, mx = LLONG_MIN;

            for (int k = i; k < j; ++k) {
                ll num[4] = { eval(mi[k + 1][j], mi[i][k], exp[k * 2 + 1]),
                        eval(mi[k + 1][j], ma[i][k], exp[k * 2 + 1]),
                        eval(ma[k + 1][j], mi[i][k], exp[k * 2 + 1]),
                        eval(ma[k + 1][j], ma[i][k], exp[k * 2 + 1]) };

                for (int t = 0; t < 4; ++t) {
                    //std::cout << num[t] << " \n"[t == 3];
                    mn = min(mn, num[t]);
                    mx = max(mx, num[t]);
                }
            }
            //std::cout << mn << ' ' << mx << '\n';
            mi[i][j] = mn;
            ma[i][j] = mx;
        }
    }
    --n;
    return ma[0][n];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
