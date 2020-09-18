#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <bitset>

const double EPS = 1e-3;
const long double INF = 1.0e+9;

using ld = long double;
using namespace std;
typedef vector<ld> Column;
typedef vector<ld> Row;
typedef vector<Row> Matrix;

struct Equation {
	Equation(const Matrix &a, const Column &b) : a(a),
												 b(b) {}

	Matrix a;
	Column b;
};

struct Position {
	Position(int column, int row) : column(column),
									row(row) {}

	int column;
	int row;
};

Position SelectPivotElement(
	const Matrix &a,
	vector<bool> &used_rows,
	vector<bool> &used_columns) {
	// This algorithm selects the first free element.
	Position pivot_element(0, 0);
	while (used_rows[pivot_element.row])
		++pivot_element.row;
	while (used_columns[pivot_element.column])
		++pivot_element.column;

	ld max = 0.0; // looks cute doe ;)
	int sz = a.size();

	for (int i = pivot_element.row; i < sz; ++i) {
		if (fabs(max) - fabs(a[i][pivot_element.column]) < EPS) {
			max = a[i][pivot_element.column];
			pivot_element.row = i;
		}
	}

	return pivot_element;
}

void SwapLines(
	Matrix &a, Column &b,
	vector<bool> &used_rows,
	Position &pivot_element) {
	swap(a[pivot_element.column], a[pivot_element.row]);
	swap(b[pivot_element.column], b[pivot_element.row]);
	swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
	pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element) {
	int sz = a.size();
	ld div = a[pivot_element.row][pivot_element.column];

	for (int i = pivot_element.column; i < sz; ++i)
		a[pivot_element.row][i] /= div;

	b[pivot_element.row] /= div;

	for (int i = pivot_element.row + 1; i < sz; ++i) {
		ld mult = a[i][pivot_element.column];
		for (int j = pivot_element.column; j < sz; ++j) {
			a[i][j] -= (a[pivot_element.row][j] * mult);
		}
		b[i] -= (b[pivot_element.row] * mult);
	}
}

void MarkPivotElementUsed(
	const Position &pivot_element,
	vector<bool> &used_rows,
	vector<bool> &used_columns) {
	used_rows[pivot_element.row] = true;
	used_columns[pivot_element.column] = true;
}

int back_substitution(Matrix &a, Column &b) {
	int size = a.size();
	for (int i = size - 1; i; --i) {
		ld temp = b[i];
		for (int j = 0; j != i; ++j) {
			b[j] -= a[j][i] * temp;
		}
	}

	return 0;
}

pair<int, Column> SolveEquation(Equation equation) {
	Matrix &a = equation.a;
	Column &b = equation.b;
	int size = a.size();

	if (size == 0)
		return {};

	vector<bool> used_columns(size, false);
	vector<bool> used_rows(size, false);
	for (int step = 0; step < size; ++step) {
		Position pivot_element = SelectPivotElement(a, used_rows, used_columns);
		if(a[pivot_element.row][pivot_element.column] == 0)
			break;
		SwapLines(a, b, used_rows, pivot_element);
		ProcessPivotElement(a, b, pivot_element);
		MarkPivotElementUsed(pivot_element, used_rows, used_columns);
	}

	int code = back_substitution(a, b);

	return { code, move(b) };
}

vector<vector<int>> get_subsets(const vector<int>& set, int m) {
    const int n = 1 << set.size();
    vector<vector<int>> subsets;
    bitset<32> bits;

    for (int i = 0; i < n; ++i) {
        bits = bits.to_ulong() + 1l;
        vector<int> subset;

        int ctr = 0;
        for (int j = 0; j < set.size(); ++j) {

            if (bits[set.size() - 1 - j]) {
                subset.push_back(set[j]);
				++ctr;
                if (ctr > m) {
                    break;
                }
            }
        }

        if (ctr == m) {
            subsets.emplace_back(move(subset));
        }
    }

    return subsets;
}

vector<Column> solve_all_equations(
	int m, 
	const Matrix& A, 
	const Column& b) {
    vector<Column> solutions;
    vector<int> nums(A.size());

    int s = 0;
    generate(nums.begin(), nums.end(), [&s] {
		 return s++; 
		 });
    auto subsets = get_subsets(nums, m);

    if (A.size() == 1) {
        subsets.emplace_back(0);
    }

    for (const auto& subset : subsets) {

        Matrix matrix;
        Column column;

        for (auto j : subset) {
            matrix.push_back(A[j]);
            column.push_back(b[j]);
        }

        Equation eq( move(matrix), move(column) );

        pair<int, Column> code_and_sol = SolveEquation(eq);

        if (code_and_sol.first == 0 && !code_and_sol.second.empty()) {
            solutions.emplace_back(move(code_and_sol.second));
        }
    }

    return solutions;
}

inline void prepare(int& n, const int m, Matrix& A, vector<ld>& b) {
    while (n < m) {
        A.emplace_back(m, 0);
        b.emplace_back(0);
        ++n;
    }

    A.emplace_back(vector<ld>(m, 1));
    b.emplace_back(INF);
    ++n;

    for (int k = 0; k < m; ++k) {
        vector<ld> temp(m, 0.0);
        temp[k] = -1;
        A.emplace_back(move(temp));
        b.emplace_back(-0.0);
        ++n;
    }
}

pair<int, vector<ld>> solve_diet_problem(
	int n, 
	int m, 
	Matrix A, 
	Column b, 
	vector<ld> c) {
    prepare(n, m, A, b);
    vector<Column> solutions = solve_all_equations(m, A, b);

    if (solutions.size() == 0) {
        return { -1, {} };
    }

    int idx = -1;
    ld largest_pleasure = -(numeric_limits<ld>::max() / 2);

    for (int i = 0; i < solutions.size(); ++i) {

        auto& sol = solutions[i];
        bool satisfied = true;

        for (int j = 0; j < n; ++j) {

            ld constraint = b[j];
            ld sum = 0.0;

            for (int k = 0; k < m; ++k) {
                sum += A[j][k] * sol[k];
            }

            if (sum - constraint > EPS) {
                satisfied = false;
                break;
            }
        }

        ld pleasure = 0.0;
        for (int k = 0; k < m; ++k) {
            pleasure += sol[k] * c[k];
        }

        if (satisfied && pleasure > largest_pleasure) {
            largest_pleasure = pleasure;
            idx = i;
        }
    }

    if (idx == -1) {
        return { -1, {} };
    }

    auto& sol = solutions[idx];
	ld accumulate = 0.0;
	for(auto x : sol) {
		accumulate += x;
	}
    if (accumulate + EPS >= INF) {
        return { 1, {} };
    }

    return { 0, move(sol) };
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	Matrix A(n, vector<ld>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> A[i][j];
		}
	}
	vector<ld> b(n);
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	vector<ld> c(m);
	for (int i = 0; i < m; i++) {
		cin >> c[i];
	}

	pair<int, vector<ld>> ans = solve_diet_problem(n, m, move(A), move(b), move(c));

	switch (ans.first) {
	case -1:
		printf("No solution\n");
		break;
	case 0:
		printf("Bounded solution\n");
		for (int i = 0; i < m; i++) {
			printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
		}
		break;
	case 1:
		printf("Infinity\n");
		break;
	}
	return 0;
}
