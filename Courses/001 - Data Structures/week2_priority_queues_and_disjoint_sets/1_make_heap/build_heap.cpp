#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> data_[i];
    }


    int getLeftChildForHeap(int node) {
        return 2 * node + 1;
    }

    int getRightChildForHeap(int node) {
        return (2 * node) + 2;
    }


    void minHeapify(int node) {
        int left = getLeftChildForHeap(node), right = getRightChildForHeap(node);
        int smallest = (left < data_.size() && data_[left] < data_[node]) ? left : node;
        if (right < data_.size() && data_[right] < data_[smallest])
            smallest = right;
        if (smallest != node) {
            swap(data_[node], data_[smallest]);
            swaps_.emplace_back(make_pair(node, smallest));
            minHeapify(smallest);
        }
    }

    void GenerateSwaps() {
        swaps_.clear();
        // The following naive implementation just sorts 
        // the given sequence using selection sort algorithm
        // and saves the resulting sequence of swaps.
        // This turns the given array into a heap, 
        // but in the worst case gives a quadratic number of swaps.
        //
        // TODO: replace by a more efficient implementation
        for (int node = (data_.size()) / 2; node >= 0; --node)
            minHeapify(node);
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
