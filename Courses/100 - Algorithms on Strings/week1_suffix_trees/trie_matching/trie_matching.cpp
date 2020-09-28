#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int const Letters = 4;
int const NA = -1;

struct Node
{
	Node* next[Letters];
	bool isLeaf;

	Node()
	{
		for (int i = 0; i < Letters; ++i)
			next[i] = nullptr;
		isLeaf = false;
	}

	~Node() {
		for (int i = 0; i < Letters; ++i)
			delete next[i];
	}
};

int letterToIndex(char letter)
{
	switch (letter)
	{
	case 'A': return 0; break;
	case 'C': return 1; break;
	case 'G': return 2; break;
	case 'T': return 3; break;
	default: assert(false); return -1;
	}
}

vector <int> solve(const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
	set<int> temp;

	Node* root = new Node();

	for (string pattern : patterns) {
		Node* curr = root;

		int sz = pattern.size();

		for (int i = 0; i < sz; ++i) {
			char c = pattern[i];

			if (curr->next[letterToIndex(c)] == nullptr) {
				curr->next[letterToIndex(c)] = new Node();
			}

			curr->next[letterToIndex(c)]->isLeaf = (i == (sz - 1));

			if (i != sz - 1) {
				curr = curr->next[letterToIndex(c)];
			}
		}
	}

	int sz = text.size();

	for (int i = 0; i < sz; ++i) {
		int idx = i;

		Node* curr = root;

		while (idx < sz) {
			char c = text[idx];

			if (curr->next[letterToIndex(c)] == nullptr)
				break;

			curr = curr->next[letterToIndex(c)];

			if (curr->isLeaf) {
				temp.insert(i);
			}

			++idx;
		}
	}

	result = vector<int>(temp.size());

	int i = 0;

	for (auto x : temp) {
		result[i++] = x;
	}

	return result;
}

int main()
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns(n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve(t, n, patterns);

	for (int i = 0; i < (int)ans.size(); i++)
	{
		cout << ans[i];
		if (i + 1 < (int)ans.size())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
