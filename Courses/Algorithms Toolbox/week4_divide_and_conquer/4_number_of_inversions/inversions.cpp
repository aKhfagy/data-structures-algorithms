#include <iostream>
#include <vector>

using std::vector;

long long merge(vector<int>& a, size_t left, size_t mid, size_t right) {
    int i = left, j = mid + 1, k = left;

    long long ret = 0;

    vector <int> b(a.size());

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            b[k++] = a[i++];
        }
        else {
            b[k++] = a[j++];
            ret += (mid - i + 1);
        }
    }

    while (i <= mid) {
        b[k++] = a[i++];
    }

    while (j <= right) {
        b[k++] = a[j++];
    }

    for (int t = left; t <= right; ++t) {
        a[t] = b[t];
    }

    return ret;
}

long long mergeSort(vector<int>& a, size_t left, size_t right) {
    long long number_of_inversions = 0;
    if (left == right)
        return 0;
    size_t ave = (left + right) / 2;
    number_of_inversions += mergeSort(a, left, ave);
    number_of_inversions += mergeSort(a, ave + 1, right);
    number_of_inversions += merge(a, left, ave, right);
    return number_of_inversions;
}

long long get_number_of_inversions(vector<int>& a, size_t left, size_t right) {
    return mergeSort(a, 0, right - 1);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }

    std::cout << get_number_of_inversions(a, 0, a.size()) << '\n';
}
