#include <iostream>
using namespace std;

struct Node {
    int left;
    int right;
    long long sum;
    long long left_sum;
    long long right_sum;
    long long mid_sum;
};

struct SegmentTree {
    int size;
    int bias;
    Node *nodes;
    static const long long N_INF = -1000LL;

    SegmentTree(int size): size(size), bias(1), nodes(nullptr) {
        while(bias < size) {bias <<= 1;}
        nodes = new Node[bias << 1];
    }

    void up(int index) {
        Node &node = nodes[index];
        Node &left_child = nodes[index << 1];
        Node &right_child = nodes[(index << 1) | 1];
        node.left = left_child.left;
        node.right = right_child.right;
        node.sum = left_child.sum + right_child.sum;
        node.left_sum = max(left_child.left_sum, left_child.sum + right_child.left_sum);
        node.right_sum = max(right_child.right_sum, left_child.right_sum + right_child.sum);
        node.mid_sum = max(max(left_child.mid_sum, right_child.mid_sum), left_child.right_sum + right_child.left_sum);
    }

    Node up(int index, int left, int right) {
        Node result{0, 0, N_INF, N_INF, N_INF, N_INF};
        if(right < nodes[index].left || nodes[index].right < left) {return result;}
        if(left <= nodes[index].left && nodes[index].right <= right) {return nodes[index];}
        Node left_child = up(index << 1, left, right);
        Node right_child = up((index << 1) | 1, left, right);
        result.sum = left_child.sum + right_child.sum;
        result.left_sum = max(left_child.left_sum, left_child.sum + right_child.left_sum);
        result.right_sum = max(right_child.right_sum, left_child.right_sum + right_child.sum);
        result.mid_sum = max(max(left_child.mid_sum, right_child.mid_sum), left_child.right_sum + right_child.left_sum);
        return result;
    }

    void read_tree() {
        int it_end = bias + size;
        int it;
        for(it = bias; it < it_end; ++it) {
            cin >> nodes[it].sum;
            nodes[it].left_sum = nodes[it].sum;
            nodes[it].right_sum = nodes[it].sum;
            nodes[it].mid_sum = nodes[it].sum;
            nodes[it].left = it - bias + 1;
            nodes[it].right = nodes[it].left;
        }
        it_end = bias << 1;
        for(; it < it_end; ++it) {
            nodes[it].sum = N_INF;
            nodes[it].left_sum = N_INF;
            nodes[it].right_sum = N_INF;
            nodes[it].mid_sum = N_INF;
            nodes[it].left = it - bias + 1;
            nodes[it].right = nodes[it].left;
        }
    }

    void build_tree() {
        for(int it = bias - 1; 0 < it; --it) {up(it);}
    }

    long long max_sum(int start, int end) {
        Node node = up(1, start, end);
        return max(max(node.left_sum, node.right_sum), max(node.sum, node.mid_sum));
    }
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int nodes_size;
    cin >> nodes_size;
    SegmentTree tree(nodes_size);
    tree.read_tree();
    tree.build_tree();
    int queries;
    cin >> queries;
    for(int it = 1; it <= queries; ++it) {
        int start, end;
        cin >> start >> end;
        cout << tree.max_sum(start, end) << '\n';
    }
    return 0;
}

