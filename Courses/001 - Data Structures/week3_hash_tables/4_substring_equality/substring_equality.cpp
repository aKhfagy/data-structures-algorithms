#include <iostream>
#include <vector>

using namespace std;
using ull = unsigned long long;

const int prime = 1e9 + 7, multiplier = 263, p2 = 1e9 + 9;

class Solver {
	string s;
	vector <ull> hashes;
	vector <ull> hashs2;
	vector <ull> powers1;
	vector <ull> powers2;

	ull mult(int a, int b, int m = prime) {
		return ((ull)(a % m) * (b % m)) % m;
	}

	ull add(int a, int b, int m = prime) {
		return ((ull)(a % m) + (b % m)) % m;
	}

	ull subtract(int a, int b, int m = prime) {
		long long x = 1ll * (a % m) - (b % m);
		if (x < 0)
			x += m;
		return (ull)x % m;
	}

	ull fp(int b, int p, int m = prime) {
		if (p == 0)
			return 1;
		ull ans = fp(b, p >> 1) % m;
		ans = mult(ans, ans, m) % m;
		if (p & 1)
			ans = mult(ans, b, m) % m;
		return ans % m;
	}

public:
	Solver(string s) : s(s) {
		hashes.resize(s.size() + 1);

		int n = s.size();

		hashs2.resize(n + 1);

		s = "#" + s;

		hashes[0] = 0;
		hashs2[0] = 0;

		for (int i = 1; i <= n; ++i) {
			hashes[i] = add(mult(hashes[i - 1], multiplier), s[i]);
		}

		for (int i = 1; i <= n; ++i) {
			hashs2[i] = add(mult(hashs2[i - 1], multiplier, p2), s[i], p2);
		}
		powers1.resize(n + 1);
		powers2.resize(n + 1);
		powers1[0] = 1;
		powers2[0] = 1;

		for (int i = 1; i <= n; ++i) {
			powers1[i] = mult(powers1[i - 1], multiplier);
			powers2[i] = mult(powers2[i - 1], multiplier, p2);
		}
	}

	bool ask(int a, int b, int l) {
		//std::cout << s.substr(a, l) << ' ' << s.substr(b, l) << '\n';
		return
			(
				subtract(hashes[a + l], mult(powers1[l], hashes[a]))
				== subtract(hashes[b + l], mult(powers1[l], hashes[b]))
				)
			&&
			(
				subtract(hashs2[a + l], mult(powers2[l], hashs2[a], p2), p2)
				== subtract(hashs2[b + l], mult(powers2[l], hashs2[b], p2), p2)
				)
			;
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
