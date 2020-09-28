#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <utility>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    int ctr = 0;
    // store all strings in one vector
    unordered_map <size_t, vector <string>> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (((hash % prime) * (multiplier % prime)) % prime + s[i] % prime) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            int hash = query.ind;

            for (int i = elems[hash].size() - 1; i >= 0; --i)
                cout << elems[hash][i] << ' ';
            std::cout << "\n";
        }
        else {
            int hash = hash_func(query.s);
            if (query.type == "find") {
                bool flag = false;
                for (int i = 0; i < elems[hash].size(); ++i) {
                    if (elems[hash][i] == query.s)
                        flag = true;
                }
                writeSearchResult(
                    elems.find(hash) != elems.end() && flag
                );
            }
            else if (query.type == "add") {
                bool flag = false;
                for (int i = 0; i < elems[hash].size(); ++i) {
                    if (elems[hash][i] == query.s)
                        flag = true;
                }

                if (!flag)
                    elems[hash].emplace_back(query.s);
            }
            else if (query.type == "del") {

                vector <string> temp;

                for (int i = 0; i < elems[hash].size(); ++i) {
                    if (elems[hash][i] != query.s) {
                        temp.emplace_back(elems[hash][i]);
                    }
                }
                elems[hash].resize(temp.size());
                for (int i = 0; i < temp.size(); ++i)
                    elems[hash][i] = temp[i];
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
