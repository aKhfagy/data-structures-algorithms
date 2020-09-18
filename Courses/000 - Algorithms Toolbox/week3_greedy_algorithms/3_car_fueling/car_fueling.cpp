#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    int ret = 0;

    int idx = 0, n = stops.size();

    stops.insert(stops.begin(), 0);

	stops.emplace_back(dist);

//    sort(stops.begin(), stops.end());

    while(idx <= n) {
        int new_node = idx;
        
        //cout << idx << '\n';
        
        while(new_node <= n && stops[new_node + 1] - stops[idx] <= tank) {
            ++new_node;
        }

        if(idx == new_node) 
            return -1;

		if(new_node <= n)
	        ++ret;

        idx = new_node;
    }

    return ret;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
