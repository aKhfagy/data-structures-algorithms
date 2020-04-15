#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  
  int num = 1, temp = 0;

  while(temp + num <= n) {
    temp += num;
    summands.emplace_back(num);
    ++num;
  }
  
  summands.back() += abs(n - temp);

  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
