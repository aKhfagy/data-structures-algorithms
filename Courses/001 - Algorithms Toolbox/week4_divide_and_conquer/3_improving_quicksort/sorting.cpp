#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;
using std::vector;
using std::swap;

const int N = int(1e5);

int a[N] = {};

void partition3(int l, int r, int& m1, int& m2) {
  m1 = l, m2 = r;
  int pivot = a[l];

  for(int idx = l; idx <= r;) {
    if(a[idx] > pivot) {
      swap(a[m2], a[idx]);
      --m2;
    }
    else if(a[idx] < pivot) {
      swap(a[m1], a[idx]);
      ++m1, ++idx;
    }
    else {
      ++idx;
    }
  }
}

int partition2(int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

void randomized_quick_sort(int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  //int m = partition2(a, l, r);
  int m1, m2; partition3(l, r, m1, m2);

  randomized_quick_sort(l, m1 - 1);
  randomized_quick_sort(m2 + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  sort(a, a + n);
  for (size_t i = 0; i < n; ++i) {
    std::cout << a[i] << ' ';
  }
}
