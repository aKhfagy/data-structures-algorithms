#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const string black = "black";

class Puzzle {
private:
    class Square {
    public:
        string up, down, left, right;
        int id;

        Square() : up(""), down(""), left(""), right(""), id(-1) {}

        Square(string u, string d, string l, string r, int i) : up(u), down(d), left(l), right(r), id(i) {}

        bool operator<(const Square &obj) const {
            return id < obj.id;
        }

        friend ostream& operator<<(ostream& os, const Square& square) {
            os << 
            '(' << square.up << ',' 
            << square.left << ',' 
            << square.down << ','
            << square.right << ");";
            return os;
        }
    };

    Square upLeft, upRight, downLeft, downRight;
    vector <Square> up, down, left, right, mid;

    bool check(string s) {
        return (s == black);
    }

    bool borders() {
        for(int i = 0; i < up.size(); ++i) {
            if(up[i].down != mid[i].up)
                return true;
        }

        for(int i = 0; i < left.size(); ++i) {
            if(left[i].right != mid[i * left.size()].left)
                return true;
        }

        for(int i = 1; i <= down.size(); ++i) {
            if(down[down.size() - i].up != mid[mid.size() - i].down)
                return true;
        }

        for(int i = 0; i < right.size(); ++i) {
            if(
                right[i].left 
                != mid[i * right.size() + (right.size() - 1)].right
            ) return true;
        }

        return false;
    }

    void permute() {
        while(
            upLeft.right != up.front().left ||
            up.front().right != up[1].left ||
            up.back().right != upRight.left
        ) {
            next_permutation(up.begin(), up.end());
        }

        while(
            downLeft.right != down.front().left ||
            down.front().right != down[1].left ||
            down.back().right != downRight.left
        ) {
            next_permutation(down.begin(), down.end());
        }

        while(
            upLeft.down != left.front().up ||
            left.front().down != left[1].up ||
            left.back().down != downLeft.up
        ) {
            next_permutation(left.begin(), left.end());
        }

        while(
            upRight.down != right.front().up ||
            right.front().down != right[1].up ||
            right.back().down != downRight.up
        ) {
            next_permutation(right.begin(), right.end());
        }

        while(
            borders()
        ) {
            next_permutation(mid.begin(), mid.end());
        }
    }

    void insert(Square square) {
        if(check(square.up)) {
            if(check(square.left))
                upLeft = move(square);
            else if(check(square.right)) 
                upRight = move(square);
            else 
                up.emplace_back(move(square));
            return;
        }
        else if(check(square.down)) {
            if(check(square.left))
                downLeft = move(square);
            else if(check(square.right)) 
                downRight = move(square);
            else 
                down.emplace_back(move(square));
            return;
        }
        else if(check(square.left)) {
            left.emplace_back(move(square));
            return;
        }
        else if(check(square.right)) {
            right.emplace_back(move(square));
            return;
        }
        
        mid.emplace_back(move(square));
    }

    void displayFirst() {
        cout << upLeft;

        for(Square& square : up) {
            cout << square;
        }

        cout << upRight << '\n';
    }

    void displayLast() {
        cout << downLeft;

        for(Square& square : down) {
            cout << square;
        }

        cout << downRight << '\n';
    }

    void displayMid() {
        for(int i = 0, j = 0; i < left.size(); ++i) {
            cout << left[i];
            for(int k = 0; k < up.size(); ++k, ++j) {
                cout << mid[j];
            } 

            cout << right[i] << '\n';
        }
    }

public:

    void add(string u, string d, string l, string r, int id) {
        insert(Square(move(u), move(d), move(l), move(r), id));
    }

    void solve() {
        permute();
    }

    void display() {
        displayFirst();
        displayMid();
        displayLast();
    }
};

Puzzle read() {
    Puzzle puzzle;
    int id = 0;
    string up, down, left, right, temp;
    while(getline(cin, up, ',')) {
        up = up.substr(1);

        getline(std::cin, left, ',');
        getline(std::cin, down, ',');
        getline(std::cin, right, ')');
        right = right.substr(0, right.size());
        getline(std::cin, temp, '\n');

        puzzle.add(
            std::move(up), std::move(left), 
            std::move(down), std::move(right), id++
            );
    }
    return puzzle;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Puzzle puzzle = read();
    puzzle.solve();
    puzzle.display();
}
