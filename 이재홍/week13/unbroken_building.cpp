#include <string>
#include <vector>

using namespace std;

struct Node {
    int left;
    int right;
    int min_val;
    int max_val;
    int lazy;
};

struct SegmentTree {
    int size;
    int bias;
    vector<Node> tree;
    SegmentTree(int size);
    void down(int node_id);
    void up(int node_id);
    void update(int node_id, int left, int right, int value);
    int get_positive(int node_id, int left, int right);
    void range_build(int node_id);
    void read(vector<int> &board);
    void init();
};

SegmentTree::SegmentTree(int size): size(size), bias(1) {
    while(bias < size) {bias <<= 1;}
    tree = vector<Node>(bias << 1, Node());
}

void SegmentTree::down(int node_id) {
    int left_id = node_id << 1;
    int right_id = left_id | 1;

    tree[left_id].lazy += tree[node_id].lazy;
    tree[right_id].lazy += tree[node_id].lazy;
    tree[node_id].lazy = 0;
}

void SegmentTree::up(int node_id) {
    int left_id = node_id << 1;
    int right_id = left_id | 1;

    int left_max = tree[left_id].max_val + tree[left_id].lazy;
    int right_max = tree[right_id].max_val + tree[right_id].lazy;
    tree[node_id].max_val = left_max > right_max ? left_max : right_max;

    int left_min = tree[left_id].min_val + tree[left_id].lazy;
    int right_min = tree[right_id].min_val + tree[right_id].lazy;
    tree[node_id].min_val = left_min < right_min ? left_min : right_min;
}

void SegmentTree::update(int node_id, int left, int right, int value) {
    if(right < tree[node_id].left || tree[node_id].right < left) {return;}
    if(left <= tree[node_id].left && tree[node_id].right <= right) {tree[node_id].lazy += value; return;}

    int left_id = node_id << 1;
    int right_id = left_id | 1;

    down(node_id);
    update(left_id, left, right, value);
    update(right_id, left, right, value);
    up(node_id);
}

int SegmentTree::get_positive(int node_id, int left, int right) {
    if(right < tree[node_id].left || tree[node_id].right < left) {return 0;}
    if(left <= tree[node_id].left && tree[node_id].right <= right) {
        if(tree[node_id].max_val + tree[node_id].lazy <= 0) {return 0;}
        if(tree[node_id].min_val + tree[node_id].lazy > 0) {return tree[node_id].right - tree[node_id].left + 1;}
    }

    int left_id = node_id << 1;
    int right_id = left_id | 1;
    int positives = 0;

    down(node_id);
    positives += get_positive(left_id, left, right);
    positives += get_positive(right_id, left, right);
    return positives;
}

void SegmentTree::range_build(int node_id) {
    int left_id = node_id << 1;
    int right_id = left_id | 1;

    tree[node_id].left = tree[left_id].left;
    tree[node_id].right = tree[right_id].right;
}

void SegmentTree::read(vector<int> &board) {
    for(int it = 0; it < size; ++it) {
        int id = bias + it;
        tree[id].left = tree[id].right = it;
        tree[id].max_val = tree[id].min_val = board[it];
        tree[id].lazy = 0;
    }
    for(int it = size; it < bias; ++it) {
        int id = bias + it;
        tree[id].left = tree[id].right = it;
        tree[id].max_val = tree[id].min_val = 0;
        tree[id].lazy = 0;
    }
}

void SegmentTree::init() {
    for(int it = bias - 1; 0 < it; --it) {
        range_build(it);
        up(it);
    }
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int row = board.size();
    int column = board[0].size();
    vector<SegmentTree> trees = vector<SegmentTree>(row, SegmentTree(column));
    for(int row_it = 0; row_it < row; ++row_it) {
        trees[row_it].read(board[row_it]);
        trees[row_it].init();
    }

    const int ATTACK = 1;
    const int HEAL = 2;
    const int ROOT = 1;

    for(vector<int> &query : skill) {
        int degree;
        if(query[0] == ATTACK) {degree = - query[5];}
        else if(query[0] == HEAL) {degree = query[5];}
        int r1 = query[1];
        int c1 = query[2];
        int r2 = query[3];
        int c2 = query[4];
        for(int row_it = r1; row_it <= r2; ++row_it) {
            trees[row_it].update(ROOT, c1, c2, degree);
        }
    }

    int answer = 0;
    int start_index = 0;
    int end_index = trees[0].size - 1;
    for(SegmentTree &tree : trees) {
        answer += tree.get_positive(ROOT, 0, end_index);
    }

    return answer;
}