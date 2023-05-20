#include <iostream>
#include <vector>
#define END_OF_LINE -1
using namespace std;

struct Edge {
    int destination;
    long long cost;
};

struct Node {
    vector<Edge> edges;
    int max_cost[2];
};

int N;
vector<Node> nodes;
vector<int> DAT;
int max_diameter;

void init_nodes() {
    for(int it = 0; it <= N; ++it) {nodes.push_back(Node());}
}

void read_edges() {
    int N_2 = N << 1;
    for(int it = 2; it < N_2;) {
        int departure;
        cin >> departure;
        while(true) {
            int destination;
            cin >> destination;
            if(destination == END_OF_LINE) {break;}
            long long cost;
            cin >> cost;
            nodes[departure].edges.push_back(Edge{destination, cost});
            ++it;
        }
    }
}

int dfs_find_max_cost_diameter(int node_id) {
    DAT[node_id] = 1;
    int max_sub_cost = 0;
    Node &node = nodes[node_id];
    for(Edge &edge : node.edges) {
        if(DAT[edge.destination]) {continue;}
        edge.cost += dfs_find_max_cost_diameter(edge.destination);
        if(node.max_cost[0] < edge.cost) {
            node.max_cost[1] = node.max_cost[0];
            node.max_cost[0] = edge.cost;
        }
        else if(node.max_cost[1] < edge.cost) {
            node.max_cost[1] = edge.cost;
        }
    }
    int sub_max_diameter = node.max_cost[0] + node.max_cost[1];
    max_diameter = sub_max_diameter > max_diameter ? sub_max_diameter : max_diameter;
    return node.max_cost[0];
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N;
    DAT = vector<int>(N + 1, 0);
    init_nodes();
    read_edges();
    int root = 1;
    dfs_find_max_cost_diameter(root);
    cout << max_diameter;
    return 0;
}