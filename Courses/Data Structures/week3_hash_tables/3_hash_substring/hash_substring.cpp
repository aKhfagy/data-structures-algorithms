#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

const int prime = 1610612741, multiplier = 263;

int mult(int a, int b) {
    return (1ll * (a % prime) * (b % prime)) % prime;
}

int add(int a, int b) {
    return (1ll * (a % prime) + (b % prime)) % prime;
}

int subtract(int a, int b) {
    int ret = (1ll * (a % prime) - (b % prime)) % prime;
    if (ret < 0)
        ret += prime;
    return ret % prime;
}

size_t hash_func(const string& s) {
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = add(mult(hash, multiplier), s[i]);
    return hash % prime;
}

vector <int> precompute_hashes(string T, int len_P) {
    vector <int> H(T.size() - len_P + 1);

    string S = T.substr(T.size() - len_P, len_P);
    H[T.size() - len_P] = hash_func(S);

    int temp = 1;

    for (int i = 0; i < len_P; ++i) {
        temp = mult(temp, multiplier);
    }

    for (int i = (T.size() - len_P - 1); i >= 0; --i) {
        H[i] = subtract(
            add(
                mult(
                    multiplier, 
                    H[i + 1]
                ), 
                int(T[i])
            ), 
            mult(
                temp, 
                int(T[i + len_P])
            )
        );
    }

    return H;
}

vector <int> rabin_karp(const Data& input) {
    const string& s = input.pattern, t = input.text;
    vector <int> output;

    int sHash = hash_func(s);

    vector <int> H = precompute_hashes(t, s.size());

    for (int i = 0; i <= t.size() - s.size(); ++i) {
        //std::cout << sHash << ' ' << H[i] << '\n';
        if (sHash != H[i])
            continue;
        if (t.substr(i, s.size()) == s)
            output.emplace_back(i);
    }
    return output;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(rabin_karp(read_input()));
    return 0;
}
