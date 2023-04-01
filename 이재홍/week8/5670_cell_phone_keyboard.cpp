#include <iostream>
#include <string>
#include <iomanip>
#define CHILD 26
#define OFFSET 'a'
using namespace std;

struct Trie {
    bool is_end;
    Trie * child[CHILD];
    int child_count;

    Trie();
    ~Trie();
    void insert(string &str, int str_idx, int str_len);
};

Trie::Trie(): is_end(false), child_count(0) {for(Trie * &node : child) {node = nullptr;}}
Trie::~Trie() {for(Trie * &node : child) {if(node != nullptr) {delete node;}}}
void Trie::insert(string &str, int str_idx, int str_len) {
    if(str_idx == str_len) {is_end = 1;}
    else {
        int node_idx = str[str_idx] - OFFSET;
        if(child[node_idx] == nullptr) {child[node_idx] = new Trie(); ++child_count;}
        child[node_idx]->insert(str, str_idx + 1, str_len);
    }
    return;
}

int words;
int words_type;

void dfs(Trie &node, int level = 0) {
    if(node.is_end && level) {
        words += 1;
        words_type += level;
    }
    int level_add = !node.is_end && (node.child_count == 1) ? 0 : 1;
    for(Trie * &sub_node : node.child) {
        if(sub_node != nullptr) {dfs(*sub_node, level + level_add);}
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
        Trie root;
        root.is_end = 1;
        for(int i = 0; i < N; ++i) {
            string str;
            cin >> str;
            root.insert(str, 0, str.size());
        }
        words = 0;
        words_type = 0;
        dfs(root);
        cout << fixed << setprecision(2) << (static_cast<float>(words_type) / static_cast<float>(words)) << '\n';
    }
    return 0;
}