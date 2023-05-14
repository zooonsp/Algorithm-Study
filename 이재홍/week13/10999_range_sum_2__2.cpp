#include <iostream>
#include <vector>
#define INDEX(x) ((x) - 1)
#define ROOT 1
using namespace std;

struct Node {
    int left;
    int right;
    long long sum;
    long long lazy;
};

int N, M, K;
vector<Node> segment_tree;
int tree_size;
int node_start;

enum Command {
    UPDATE = 1,
    GETSUM = 2,
};

void build_tree() {
    cin >> N >> M >> K;
    int shifted = 0;
    while((N - 1) >> shifted) {++shifted;}
    tree_size = 1 << (shifted + 1);
    segment_tree = vector<Node>(tree_size, Node());
    node_start = tree_size >> 1;
    int N_it;
    for(N_it = 1; N_it <= N; ++N_it) {
        Node &node = segment_tree[node_start + INDEX(N_it)];
        cin >> node.sum;
        node.left = N_it;
        node.right = N_it;
    }
    int tree_last_level_nodes = tree_size >> 1;
    for(; N_it <= tree_last_level_nodes; ++N_it) {
        Node &node = segment_tree[node_start + INDEX(N_it)];
        node.left = N_it;
        node.right = N_it;
    }
    int node_it = node_start;
    while(--node_it) {
        Node &node = segment_tree[node_it];
        Node &left_child = segment_tree[node_it << 1];
        Node &right_child = segment_tree[(node_it << 1) + 1];
        node.sum = left_child.sum + right_child.sum;
        node.left = left_child.left;
        node.right = right_child.right;
    }
}

void update_tree(int node_id, int left, int right, long long value) {
    Node &node = segment_tree[node_id];
    if(node.right < left || right < node.left) {return;}
    if(left <= node.left && right >= node.right) {node.lazy += value; return;}
    int left_child_id = node_id << 1;
    int right_child_id = (node_id << 1) + 1;
    Node &left_child = segment_tree[left_child_id];
    Node &right_child = segment_tree[right_child_id];
    left_child.lazy += node.lazy;
    right_child.lazy += node.lazy;
    node.lazy = 0LL;
    update_tree(left_child_id, left, right, value);
    update_tree(right_child_id, left, right, value);
    node.sum = (left_child.right - left_child.left + 1) * left_child.lazy + left_child.sum + (right_child.right - right_child.left + 1) * right_child.lazy + right_child.sum;
}

long long range_sum(int node_id, int left, int right) {
    Node &node = segment_tree[node_id];
    if(node.right < left || right < node.left) {return 0LL;}
    if(left <= node.left && right >= node.right) {return (node.right - node.left + 1) * node.lazy + node.sum;}
    int left_child_id = node_id << 1;
    int right_child_id = (node_id << 1) + 1;
    Node &left_child = segment_tree[left_child_id];
    Node &right_child = segment_tree[right_child_id];
    left_child.lazy += node.lazy;
    right_child.lazy += node.lazy;
    node.lazy = 0LL;
    node.sum = (left_child.right - left_child.left + 1) * left_child.lazy + left_child.sum + (right_child.right - right_child.left + 1) * right_child.lazy + right_child.sum;
    long long sum = 0LL;
    sum += range_sum(left_child_id, left, right);
    sum += range_sum(right_child_id, left, right);
    return sum;
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    build_tree();
    int queries = M + K;
    for(int query = 1; query <= queries; ++query) {
        int command;
        int left, right;
        cin >> command;
        switch(command) {
            case UPDATE:
                long long value;
                cin >> left >> right >> value;
                update_tree(ROOT, left, right, value);
                break;
            case GETSUM:
                cin >> left >> right;
                cout << range_sum(ROOT, left, right) << '\n';
                break;
        }
    }
    return 0;
}