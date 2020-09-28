#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using std::vector;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;

  int n = weights.size();

  for(int idx = 0; idx < n; ++idx) {
    if(capacity == 0)
      return value;
    
    double mx = 0;
    int pos = -1;

    for(int i = 0; i < n; ++i) {
      if(weights[i] > 0) {
        double temp = (double)values[i] / weights[i];
        if(mx < temp) {
          mx = temp;
          pos = i;
        }
      }
    }

    int weight = min(capacity, weights[pos]);

    value += weight * mx;

    weights[pos] -= weight;
    capacity -= weight;
  } 

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
