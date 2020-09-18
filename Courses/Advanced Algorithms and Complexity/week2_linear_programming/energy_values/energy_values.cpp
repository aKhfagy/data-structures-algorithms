#include <cmath>
#include <iostream>
#include <vector>

const double EPS = 1e-6;
const int PRECISION = 20;

using ld = long double;

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

struct Equation {
    Equation(const Matrix &a, const Column &b):
        a(a),
        b(b)
    {}

    Matrix a;
    Column b;
};

struct Position {
    Position(int column, int row):
        column(column),
        row(row)
    {}

    int column;
    int row;
};

Equation ReadEquation() {
    int size;
    std::cin >> size;
    Matrix a(size, std::vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column)
            std::cin >> a[row][column];
        std::cin >> b[row];
    }
    return Equation(std::move(a), std::move(b));
}

Position SelectPivotElement(
  const Matrix &a, 
  std::vector <bool> &used_rows, 
  std::vector <bool> &used_columns) {
    // This algorithm selects the first free element.
    Position pivot_element(0, 0);
    while (used_rows[pivot_element.row])
        ++pivot_element.row;
    while (used_columns[pivot_element.column])
        ++pivot_element.column;

    ld max = 0.0; // looks cute doe ;)
    int sz = a.size();
    
    for(int i = pivot_element.row; i < sz; ++i) {
        if(std::fabs(a[i][pivot_element.column]) > std::fabs(max)) {
            max = a[i][pivot_element.column];
            pivot_element.row = i;
        }
    }
    
    return pivot_element;
}

void SwapLines(
    Matrix &a, Column &b, 
    std::vector <bool> &used_rows, 
    Position &pivot_element) {
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
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
    std::vector <bool> &used_rows, 
    std::vector <bool> &used_columns) {
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

Column SolveEquation(Equation equation) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int size = a.size();

    std::vector <bool> used_columns(size, false);
    std::vector <bool> used_rows(size, false);
    for (int step = 0; step < size; ++step) {
        Position pivot_element = SelectPivotElement(a, used_rows, used_columns);
        SwapLines(a, b, used_rows, pivot_element);
        ProcessPivotElement(a, b, pivot_element);
        MarkPivotElementUsed(pivot_element, used_rows, used_columns);
    }

    for (int i = size - 1; i; --i) {
        for (int j = 0; j != i; ++j) {
            b[j] -= a[j][i] * b[i];
            a[j][i] = 0;
        }
    }

    return b;
}

void PrintColumn(const Column &column) {
    int size = column.size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < size; ++row)
        std::cout << column[row] << " \n"[row == (size - 1)];
}

int main() {
    Equation equation = ReadEquation();
    if(equation.a.size()) {
        Column solution = SolveEquation(equation);
        PrintColumn(solution);
    }
    return 0;
}
