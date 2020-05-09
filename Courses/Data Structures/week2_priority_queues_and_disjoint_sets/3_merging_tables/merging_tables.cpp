#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;

	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) :
		size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size) : size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i] = DisjointSetsElement(1,i,0);
	}

	int getParent(int table) {
		return sets[table].parent = sets[table].parent == table ? table : getParent(sets[table].parent);
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			if (sets[realDestination].rank < sets[realSource].rank) {
				sets[realDestination].parent = realSource;
				sets[realSource].size += sets[realDestination].size;
				max_table_size = max(max_table_size, sets[realSource].size);
			}
			else if (sets[realDestination].rank > sets[realSource].rank) {
				sets[realSource].parent = realDestination;
				sets[realDestination].size += sets[realSource].size;
				max_table_size = max(max_table_size, sets[realDestination].size);
			}
			else {
				sets[realSource].parent = realDestination;
				++sets[realDestination].rank;
				sets[realDestination].size += sets[realSource].size;
				max_table_size = max(max_table_size, sets[realDestination].size);
			}
		}
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto& table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
		--destination;
		--source;

		tables.merge(destination, source);
		cout << tables.max_table_size << endl;
	}

	return 0;
}
