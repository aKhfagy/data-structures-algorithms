#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::multiset;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
    multiset <int, std::greater<int>> st;

public:

    void Push(int value) {
        stack.push_back(value);
        st.insert(value);
    }

    void Pop() {
        assert(stack.size());
        st.erase(st.find(stack.back()));
        stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        //for (auto i : st) {
        //    cout << i << ' ';
        //}
        //puts("");
        return *st.begin();
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}