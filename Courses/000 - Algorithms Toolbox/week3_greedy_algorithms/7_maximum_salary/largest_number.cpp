#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

/*
7
5 581 57 569 532 52 517

test case that I suspect made it fail
*/

bool comp(string& a, string& b) {
  string temp_1 = a + b;
  string temp_2 = b + a;
  return temp_1 > temp_2;
}

string largest_number(vector<string> a) {
  sort(a.begin(), a.end(), comp);
  std::stringstream ret;
  for (size_t i = 0; i < a.size(); i++) {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main() {
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
