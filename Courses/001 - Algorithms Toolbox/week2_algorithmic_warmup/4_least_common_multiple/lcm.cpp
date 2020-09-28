#include <iostream>
using ll = long long;
long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

ll gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);
}

ll lcm(int a, int b) {
  return (1ll * a * b) / gcd(a, b);
} 

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}
