#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::map;

bool get_majority_element(vector<int> &a) {
  
  int n = a.size();

  map <int, int> freq;
  
  for(int num : a) {
    ++freq[num];
    if(freq[num] > (n >> 1)) {
      return true;
    }
  }

  return false;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a)) << '\n';
}
