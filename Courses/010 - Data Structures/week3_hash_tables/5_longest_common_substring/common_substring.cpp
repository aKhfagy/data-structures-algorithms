#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct Answer {
	int i, j, len;
};

struct Query {
    bool flag;
    int i, j;

    Query(bool flag, int i, int j): flag(flag), i(i), j(j) {}
};

const int p1 = 1610612741, p2 = int(1e9) + 7, p3 = 1000012337, p4 = 1000009567, p5 = 1000007147, multiplier = 263;

int p[] = 
{ 
    p1, p1, 
    p2, p2, 
    p3, p3, 
    p4, p4, 
    p5, p5 
};

int mult(int a, int b, int m) {
    return (1ll * (a % m) * (b % m)) % m;
}

int add(int a, int b, int m) {
    return (1ll * (a % m) + (b % m)) % m;
}

int subtract(int a, int b, int m) {
    int ret = (1ll * (a % m) - (b % m)) % m;
    if (ret < 0)
        ret += m;
    return ret % m;
}

size_t hash_func(const string& s, int m) {
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = add(mult(hash, multiplier, m), s[i], m);
    return hash % m;
}

vector <int> precompute_hashes(string T, int len_P, int m) {
    vector <int> H(T.size() - len_P + 1);

    string S = T.substr(T.size() - len_P, len_P);
    H[T.size() - len_P] = hash_func(S, m);

    int temp = 1;

    for (int i = 0; i < len_P; ++i) {
        temp = mult(temp, multiplier, m);
    }

    for (int i = (T.size() - len_P - 1); i >= 0; --i) {
        H[i] = subtract(
            add(
                mult(
                    multiplier,
                    H[i + 1],
                    m
                ),
                int(T[i]),
                m
            ),
            mult(
                temp,
                int(T[i + len_P]),
                m
            ),
            m
        );
    }

    return H;
}

Query rolling_hash(const string& s, const string& t, int len) {
    vector <int> H[10];

    if (s.size() < t.size()) {
        for (int i = 0; i < 6; ++i) {
            H[i] = precompute_hashes((i & 1) ? t : s, len, p[i]);
        }
    }
    else {
        for (int i = 0; i < 6; ++i) {
            H[i] = precompute_hashes((i & 1) ? s : t, len, p[i]);
        }
    }

    unordered_map <int, int> tables[5];
    //unordered_set <int> hashes[5];

    for (int i = 0; i < H[0].size(); ++i) {
        tables[0][H[0][i]] = i;
        //hashes[0].insert(H[0][i]);
    }

    for (int i = 0; i < H[2].size(); ++i) {
        tables[1][H[2][i]] = i;
        //hashes[1].insert(H[2][i]);
    }

    for (int i = 0; i < H[4].size(); ++i) {
        tables[2][H[4][i]] = i;
        //hashes[2].insert(H[4][i]);
    }

    for (int i = 0; i < H[1].size(); ++i) {
        if (
            tables[0].find(H[1][i]) != tables[0].end()
            &&
            tables[1].find(H[3][i]) != tables[1].end()
            &&
            tables[2].find(H[5][i]) != tables[2].end()
            ) {
            
            return Query(true, tables[0][H[1][i]], i);
        }
    }

    return Query(false, -1, -1);
}

Answer solve(const string& s, const string& t) {
    Answer ans = { 0, 0, 0 };

    int l = 0, r = std::min(s.size(), t.size());

    while (l <= r) {
        int mid = (l + r) / 2;
        Query query = rolling_hash(s, t, mid);

        if (query.flag) {
            l = mid + 1;
            ans = { query.i, query.j, mid };
        }
        else {
            r = mid - 1;
        }
    }

    if (s.size() >= t.size()) {
        ans = { ans.j, ans.i, ans.len };
    }

    return ans;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
