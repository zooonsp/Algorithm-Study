#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
    int departure;
    int destination;
    int cost;
    Edge(int departure, int destination, int cost): departure(departure), destination(destination), cost(cost) {}
    bool operator<(const Edge& rhs) const {return cost > rhs.cost;}
    Edge add_cost(int cost_to_add) {
        return Edge{departure, destination, cost + cost_to_add};
    } 
};

struct Node {
    vector<Edge> edges;
    Node(): edges() {}
    void AddEdge(int departure, int destination, int cost) {
        edges.push_back(Edge{departure, destination, cost});
    }
};

struct Graph {
    vector<Node> nodes;
    Graph(int node_size, int edge_size): nodes(vector<Node>(node_size + 1, Node())) {
        Read(edge_size);
    }
    void Read(int edge_size) {
        for(int it = 0; it < edge_size; ++it) {
            int node_1, node_2, cost;
            cin >> node_1 >> node_2 >> cost;
            nodes[node_1].AddEdge(node_1, node_2, cost);
            nodes[node_2].AddEdge(node_2, node_1, cost);
        }
    }
    int get_max_cost_without_one_edge(int start_node, int end_node) {
        vector<bool> visited = vector<bool>(nodes.size(), false);
        visited[start_node] = true;
        vector<int> costs = vector<int>(nodes.size(), 0);
        priority_queue<Edge> edge_queue;
        for(Edge edge: nodes[start_node].edges) {
            edge_queue.push(edge);
        }
        const bool NOT_SKIPPED = false;
        bfs(end_node, visited, costs, edge_queue, NOT_SKIPPED);
        return costs[end_node];
    }
    void bfs(int end_node, vector<bool> &visited, vector<int> &costs, priority_queue<Edge> edge_queue, bool is_skipped) {
        if(edge_queue.empty()) {return;}
        Edge edge = edge_queue.top();
        edge_queue.pop();
        while(visited[edge.destination]) {
            edge = edge_queue.top();
            edge_queue.pop();
        }
        if(!is_skipped) {
            const bool SKIPPED  = true;
            bfs(end_node, visited, costs, edge_queue, SKIPPED);
        }
        if(edge.destination != end_node) {
            costs[edge.destination] = edge.cost;
            for(Edge &node_edge: nodes[edge.destination].edges) {
                edge_queue.push(node_edge.add_cost(costs[node_edge.departure]));
            }
            visited[edge.destination] = true;
            bfs(end_node, visited, costs, edge_queue, is_skipped);
            visited[edge.destination] = false;
            return;
        }
        costs[edge.destination] = costs[edge.destination] > edge.cost ? costs[edge.destination] : edge.cost;
        return;
    }
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    int node_size;
    int edge_size;
    cin >> node_size >> edge_size;

    Graph graph{node_size, edge_size};
    cout << graph.get_max_cost_without_one_edge(1, node_size);
    return 0;
}