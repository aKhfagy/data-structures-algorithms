#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::set;
using std::stack;
using std::cin;
using std::cout;

class TreeOrders {
    int n;
    vector <int> key;
    vector <int> left;
    vector <int> right;

public:
    void read() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }


    vector <int> in_order() {
        vector<int> result;
        set <int> process;
        stack <int> not_yet;

        process.insert(-1);
        not_yet.push(0);

        while (not_yet.size()) {
            int i = not_yet.top();

            if (process.find(left[i]) == process.end()) 
                not_yet.push(left[i]);
            
            else {
                
                result.emplace_back(key[i]);

                process.insert(i);

                not_yet.pop();

                if (right[i] != -1) 
                    not_yet.push(right[i]);

            }

        }

        return result;
    }

    vector <int> pre_order() {
        vector<int> result;
        stack<int> not_yet;

        not_yet.push(0);

        while (not_yet.size()) {

            int i = not_yet.top();

            not_yet.pop();

            result.emplace_back(key[i]);

            if (right[i] != -1)
                not_yet.push(right[i]);

            if (left[i] != -1)
                not_yet.push(left[i]);

        }

        return result;
    }

    vector <int> post_order() {
        vector<int> result;
        set <int> process;
        stack <int> not_yet;

        process.insert(-1);
        not_yet.push(0);

        while (not_yet.size()) {
            int i = not_yet.top();

            bool right_exists = process.find(right[i]) != process.end();
            bool left_exists = process.find(left[i]) != process.end();

            if (right_exists && left_exists) {
                result.emplace_back(key[i]);

                not_yet.pop();

                process.insert(i);
            }
            else {
                
                if (!right_exists)
                    not_yet.push(right[i]);

                if (!left_exists)
                    not_yet.push(left[i]);

            }

        }

        return result;
    }
};

void print(vector <int> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
    print(t.in_order());
    print(t.pre_order());
    print(t.post_order());
    return 0;
}

int main(int argc, char** argv)
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }
#endif

    return main_with_large_stack_space();
}

