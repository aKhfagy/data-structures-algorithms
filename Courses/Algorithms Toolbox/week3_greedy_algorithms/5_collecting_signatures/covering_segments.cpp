#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int first, second;

  bool operator < (Segment& obj) {
    return second <= obj.second;
  }
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;

  sort(segments.begin(), segments.end());

  int start = segments[0].second, n = segments.size();

  points.emplace_back(start);

  for(int i = 1; i < n; ++i) {
    if(start >= segments[i].first && start <= segments[i].second)
      continue;

    start = segments[i].second;
    points.emplace_back(start);
  }

  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].first >> segments[i].second;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
