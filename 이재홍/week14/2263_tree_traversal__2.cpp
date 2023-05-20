#include <iostream>
#include <vector>
using namespace std;

void read_orders(int size, vector<int> &inorder_reverse, vector<int> &postorder) {
    inorder_reverse = vector<int>(size + 1);
    postorder.reserve(size + 1);
    for(int it = 1; it <= size; ++it) {
        int node;
        cin >> node;
        inorder_reverse[node] = it;
    }
    postorder.push_back(0);
    for(int it = 1; it <= size; ++it) {
        int node;
        cin >> node;
        postorder.push_back(node);
    }
}

void init(int size, vector<int> &next_index) {
    next_index.reserve(size + 1);
    next_index.push_back(0);
    for(int it = 0; it < size; ++it) {
        next_index.push_back(it);
    }
}

void print_preorder(int now, int level, vector<int> &inorder_reverse, vector<int> &postorder, vector<int> &next_index) {
    if(!now) {return;}
    int id = postorder[now];
    cout << id << ' ';
    int at_inorder = inorder_reverse[id] - level;
    int left = next_index[at_inorder];
    print_preorder(left, level, inorder_reverse, postorder, next_index);
    next_index[at_inorder] = next_index[left];
    int right = next_index[now];
    print_preorder(right, level + 1, inorder_reverse, postorder, next_index);
    next_index[now] = next_index[right];
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    size_t size;
    cin >> size;
    vector<int> inorder_reverse;
    vector<int> postorder;
    vector<int> next_index;
    read_orders(size, inorder_reverse, postorder);
    init(size, next_index);
    print_preorder(size, 0, inorder_reverse, postorder, next_index);
    return 0;
}