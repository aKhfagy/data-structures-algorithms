#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using std::vector;

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());

    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    for (int i = 0; i < points.size(); i++) {
        int x, y;
        for (x = 0; x < starts.size(); x++) {
            if (starts[x] > points[i]) {
                break;
            }
        }

        for (y = 0; y < ends.size(); y++) {
            if (ends[y] >= points[i]) {
                break;
            }
        }
        cnt[i] = x - y;
    }


    return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        std::cin >> starts[i] >> ends[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        std::cin >> points[i];
    }
    //use fast_count_segments
    vector<int> cnt = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        std::cout << cnt[i] << ' ';
    }
}
