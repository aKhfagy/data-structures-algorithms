#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;
using namespace std;
using std::map;

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size(); 

  while(left <= right) {
    int mid = (left + right) >> 1;

    if(a[mid] == x)
      return mid;
    else if(a[mid] < x) 
      left = mid + 1;
    else 
      right = mid - 1;
  }

  return -1;
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

map <int, int> idx;

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
    idx[a[i]] = i;

  }
//  sort(a.begin(), a.end());
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    int pos = idx.count(b[i]) != 0 ? idx[b[i]] : -1;

    std::cout << pos << ' ';
  }
}
