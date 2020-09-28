#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;

const int N = 1e5;

int tree[4 * N];

int build(int idx, int l, int r, vector<int> const& A) {
    if (l == r) {
        return tree[idx] = A[l];
    }

    int mid = (l + r) >> 1;

    return tree[idx] = max(
        build(idx << 1, l, mid, A),
        build(idx << 1 ^ 1, mid + 1, r, A)
    );
}

int query(int idx, int l, int r, int a, int b, vector <int> const& A) {
    if (l > b || r < a)
        return 0;
    if (l >= a && r <= b)
        return tree[idx];
    int mid = (l + r) >> 1;
    return max(
        query(idx << 1, l, mid, a, b, A),
        query(idx << 1 ^ 1, mid + 1, r, a, b, A)
    );
}

void max_sliding_window_naive(vector<int> const& A, int w) {
    build(1, 0, A.size() - 1, A);
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        //int window_max = A.at(i);
        //for (size_t j = i + 1; j < i + w; ++j)
        //    window_max = max(window_max, A.at(j));

        cout << query(1, 0, A.size() - 1, i, i + w - 1, A) << " ";
    }

    return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
