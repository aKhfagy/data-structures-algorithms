#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;

struct Node {
    pair<int, int> range;
    vector<Node> next;
};

void build_trie(const string& text, Node* trie) {
    for (int i = text.size(); i--; ) {
        Node* curr_node = trie;
        int sz = text.size();
        for (int k = i; k < sz; k++) {
            bool match = false;
            int szz = curr_node->next.size();
            for (int i = 0; i < szz; i++)
                if (text[k] == text[curr_node->next[i].range.first]) {
                    curr_node = &(curr_node->next[i]);
                    match = true;
                    break;
                }


            if (!match) {
                Node new_node;
                new_node.range.first = k;
                new_node.range.second = k;
                curr_node->next.emplace_back(new_node);
                curr_node = &(curr_node->next.back());
            }
        }
    }
}

void compress_trie(const string& text, Node* trie) {
    int sz = trie->next.size();
    for (int i = 0; i < sz; i++) {
        compress_trie(text, &(trie->next[i]));
    }
    if (sz == 1) {
        Node desc = trie->next[0];
        trie->range.second = desc.range.second;
        trie->next.clear();
        int szz = desc.next.size();
        for (int i = 0; i < szz; i++) {
            trie->next.emplace_back(desc.next[i]);
        }
    }
}

void traverse_trie(const string& text, Node* trie) {
    int sz = trie->next.size();
    for (int i = 0; i < sz; i++) {
        traverse_trie(text, &(trie->next[i]));
    }
    int l = trie->range.first;
    int r = trie->range.second;
    if (l != -1) {
        cout << text.substr(l, r - l + 1) << '\n';
    }
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
void ComputeSuffixTreeEdges(const string& text) {
    Node trie;
    trie.range = make_pair(-1, -1);
    build_trie(text, &trie);
    compress_trie(text, &trie);
    traverse_trie(text, &trie);
}

int main() {
    std::ios_base::sync_with_stdio(); cin.tie(0); cout.tie(0);
    string text;
    cin >> text;
    ComputeSuffixTreeEdges(text);
    return 0;
}
