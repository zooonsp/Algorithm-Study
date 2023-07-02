#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int node1;
    int node2;
    Edge(int node1, int node2) {
        if(node1 < node2) {
            this->node1 = node1;
            this->node2 = node2;
            return;
        }
        this->node1 = node2;
        this->node2 = node1;
    }
};

struct Node {
    vector<int> to;
};

struct Graph {
    vector<Node> nodes;
    vector<Edge> bridge;
    Graph() {
        int V, E;
        cin >> V >> E;
        nodes = vector<Node>(V + 1);
        while(E) {
            --E;
            int node_1, node_2;
            cin >> node_1 >> node_2;
            nodes[node_1].to.push_back(node_2);
            nodes[node_2].to.push_back(node_1);
        }
    }
    int dfs(int level, int node_id, int parent_id, vector<bool> &visited, vector<int> &levels) {
        visited[node_id] = true;
        levels[node_id] = level;
        int connected_min_level = level;
        for(int next_node_id: nodes[node_id].to) {
            if(next_node_id == parent_id) {continue;}
            if(visited[next_node_id]) {
                connected_min_level = connected_min_level < levels[next_node_id] ? connected_min_level : levels[next_node_id];
                continue;
            }
            int next_node_connected_min_level = dfs(level + 1, next_node_id, node_id, visited, levels);
            if(level < next_node_connected_min_level) {bridge.push_back(Edge{node_id, next_node_id});}
            connected_min_level = connected_min_level < next_node_connected_min_level ? connected_min_level : next_node_connected_min_level;
        }
        return connected_min_level;
    }
    void find_bridge() {
        bridge.clear();
        vector<bool> visited = vector<bool>(nodes.size(), false);
        vector<int> levels = vector<int>(nodes.size(), 0);
        for(int it = 1; it < nodes.size(); ++it) {
            if(visited[it]) {continue;}
            dfs(0, it, 0, visited, levels);
        }
    }
    int number_of_bridge() {
        return bridge.size();
    }
    void print_bridge() {
        sort(bridge.begin(), bridge.end(),
            [](Edge &lhs, Edge &rhs) -> bool {
                if(lhs.node1 < rhs.node1) {return true;}
                if(lhs.node1 > rhs.node1) {return false;}
                return lhs.node2 < rhs.node2;
            });
        if(!bridge.empty()) {cout << bridge[0].node1 << ' ' << bridge[0].node2;}
        for(int it = 1; it < bridge.size(); ++it) {
            cout << '\n' << bridge[it].node1 << ' ' << bridge[it].node2;
        }
    }
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    Graph graph{};
    graph.find_bridge();
    cout << graph.number_of_bridge() << '\n';
    graph.print_bridge();
    return 0;
}