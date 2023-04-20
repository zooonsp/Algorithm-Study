#include <iostream>
#include <string>
#include <iomanip>
#define CHILD 26
#define OFFSET 'a'
using namespace std;

struct Trie { // tree structure
    bool is_end;
    Trie * child[CHILD];
    int child_count; // number f childs

    Trie();
    ~Trie();
    void insert(string &str, int str_idx, int str_len);
};

Trie::Trie(): is_end(false), child_count(0) {for(Trie * &node : child) {node = nullptr;}}
Trie::~Trie() {for(Trie * &node : child) {if(node != nullptr) {delete node;}}} // delete child node recursively
void Trie::insert(string &str, int str_idx, int str_len) { // insert str_idx th character to trie
    if(str_idx == str_len) {is_end = 1;} // mark end of string
    else {
        int node_idx = str[str_idx] - OFFSET; // convert [a-z] to [0-25]
        if(child[node_idx] == nullptr) {child[node_idx] = new Trie(); ++child_count;} // create node if node does not exist
        child[node_idx]->insert(str, str_idx + 1, str_len); // recursively generate trie node
    }
    return;
}

int words;
int words_type;

void dfs(Trie &node, int level = 0) {
    if(node.is_end && level) { // word found, skip root node (level 0)
        words += 1; // count word
        words_type += level; // number of typing to complete word
    }
    int level_add = !node.is_end && (node.child_count == 1) ? 0 : 1; // if node.child_count is 1, there is only 1 character availble, so automatic typing is available
    for(Trie * &sub_node : node.child) { // see all available child nodes
        if(sub_node != nullptr) {dfs(*sub_node, level + level_add);} // recursive function call
    }
    return;
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    int N;
    while(cin >> N) {
        Trie root; // initiate root node
        root.is_end = 1; // automatic typing is disabled at first
        for(int i = 0; i < N; ++i) {
            string str;
            cin >> str;
            root.insert(str, 0, str.size()); // insert to trie
        }
        words = 0;
        words_type = 0;
        dfs(root); // count words and total typings required
        cout << fixed << setprecision(2) << (static_cast<float>(words_type) / static_cast<float>(words)) << '\n'; // get average number of typings
    }
    return 0;
}