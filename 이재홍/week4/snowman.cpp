#include <iostream>
#include <queue>
#include <vector>
#define SNOWMAN 2
#define JEWEL 3
using namespace std;
// assume each board as node
// if node 1 and node 2 intersects in x-axis, make edge with cost height
// use bfs to route

struct Edge {
    int dest;
    int cost;
};

struct Node {
    int h;
    int xmin;
    int xmax;
};

int H, W; // height and width
vector<Node> V; // nodes
vector<vector<Edge>> E; // edges
vector<int> cost_map; // track max limit
int s, e; // start and end node index
queue<int> q;

void read_map() {
    cin >> H >> W;
    for(int i = 0; i < H; ++i) { // read map and find nodes
        int value;
        int prev_value;
        cin >> value;
        if(value) {V.push_back({i, 0, 0});}
        if(value == SNOWMAN) {s = V.size() - 1;} // find snowman node
        else if(value == JEWEL) {e = V.size() - 1;} // find jewel node
        prev_value = value;
        for(int j = 1; j < W; ++j) {
            cin >> value;
            if(value) {
                if(prev_value) {V.back().xmax = j;} // node extend
                else {V.push_back({i, j, j});} // new node
                if(value == SNOWMAN) {s = V.size() - 1;} // find snowman node
                else if(value == JEWEL) {e = V.size() - 1;} // find jewel node
            }
            prev_value = value;
        }
    }
}

void make_edge() {
    int Vsize = V.size();
    E = vector<vector<Edge>>(Vsize, vector<Edge>());
    for(int i = 0; i < Vsize; ++i) {
        for(int j = i + 1; j < Vsize; ++j) {
            Node &n1 = V[i];
            Node &n2 = V[j];
            if(n1.xmax < n2.xmin || n2.xmax < n1.xmin) {continue;}
            int cost = abs(n1.h - n2.h);
            E[i].push_back({j, cost});
            E[j].push_back({i, cost});
        }
    }
}

void bfs() {
    // prepare queue, cost_map, visited
    q.push(s);
    int Vsize = V.size();
    cost_map = vector<int>(Vsize, H);
    cost_map[s] = 0;
    // start bfs
    while(q.size()) {
        // pop front of queue
        int now = q.front();
        q.pop();
        // backtracking
        int Esize = E[now].size();
        for(int i = 0; i < Esize; ++i) {
            Edge &to_next = E[now][i];
            // pruning
            int cost_now = cost_map[now];
            int cost_next = cost_now < to_next.cost ? to_next.cost : cost_now;
            if(cost_map[to_next.dest] <= cost_next) {continue;}
            // process
            cost_map[to_next.dest] = cost_next;
            // push into queue
            q.push(to_next.dest);
        }
    }
}

int main() {
    read_map();
    make_edge();
    bfs();
    cout << cost_map[e];
    return 0;
}