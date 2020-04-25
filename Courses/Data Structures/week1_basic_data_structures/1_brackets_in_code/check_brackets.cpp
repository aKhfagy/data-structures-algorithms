#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position) :
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next, position + 1));
        }

        else if (next == ')' || next == ']' || next == '}') {
            if (opening_brackets_stack.size() && opening_brackets_stack.top().Matchc(next)) {
                opening_brackets_stack.pop();
            }
            else {
                opening_brackets_stack.push(Bracket(next, position + 1));
                break;
            }
        }
    }

    if (opening_brackets_stack.empty()) {
        puts("Success");
    }
    else {
        std::cout << opening_brackets_stack.top().position << '\n';
    }

    return 0;
}
