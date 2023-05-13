#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int left;
    int right;
};

void read_orders(int size, vector<int> &inorder, vector<int> &postorder) {
    inorder.reserve(size);
    postorder.reserve(size);
    for(int it = 0; it < size; ++it) {
        int node;
        cin >> node;
        inorder.push_back(node);
    }
    for(int it = 0; it < size; ++it) {
        int node;
        cin >> node;
        postorder.push_back(node);
    }
}

int reconstruct_tree(vector<Node> &nodes, int inorder_start, int postorder_start, int length, vector<int> &inorder, vector<int> &postorder) {
    int left, root;
    int idx = 0;
    int next_length;
    if(!length) {return 0;}
    root = NULL;
    int next_inorder_start = inorder_start;
    int next_postorder_start = postorder_start;
    while(idx < length) {
        left = root;
        root = inorder[inorder_start + idx];
        next_length = 0;
        while(postorder[postorder_start + idx] != root) {
            ++idx;
            ++next_length;
        }
        ++idx;
        nodes[root].left = left;
        nodes[root].right = reconstruct_tree(nodes, next_inorder_start + 1, next_postorder_start, next_length, inorder, postorder);
        next_inorder_start = inorder_start + idx;
        next_postorder_start = postorder_start + idx;
    }
    return root;
}

void print_preorder(vector<Node> &nodes, int root) {
    if(!root) {return;}
    cout << root << ' ';
    print_preorder(nodes, nodes[root].left);
    print_preorder(nodes, nodes[root].right);
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    size_t size;
    cin >> size;
    vector<Node> nodes{size + 1, Node()};
    vector<int> inorder;
    vector<int> postorder;
    read_orders(size, inorder, postorder);
    int root = reconstruct_tree(nodes, 0, 0, size, inorder, postorder);
    print_preorder(nodes, root);
    return 0;
}