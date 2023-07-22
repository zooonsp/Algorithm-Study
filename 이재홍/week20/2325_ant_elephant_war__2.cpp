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
    bool operator==(const Edge& rhs) const {return departure == rhs.departure && destination == rhs.destination;}
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
        vector<Edge> back_path;
        get_path(start_node, end_node, back_path);
        int cost = 0;
        for(Edge &edge: back_path) {
            int new_cost = get_cost(start_node, end_node, edge);
            cost = cost > new_cost ? cost : new_cost;
        }
        return cost;
    }
    void get_path(int start_node, int end_node, vector<Edge> &back_path) {
        vector<bool> visited = vector<bool>(nodes.size(), false);
        visited[start_node] = true;
        vector<int> costs = vector<int>(nodes.size(), 0);
        priority_queue<Edge> edge_queue;
        for(Edge edge: nodes[start_node].edges) {
            edge_queue.push(edge);
        }
        vector<Edge> history;
        while(!edge_queue.empty()) {
            Edge edge = edge_queue.top();
            edge_queue.pop();
            if(visited[edge.destination]) {continue;}
            history.push_back(edge);
            costs[edge.destination] = edge.cost;
            visited[edge.destination] = true;
            if(edge.destination == end_node) {break;}
            for(Edge &destination_edge: nodes[edge.destination].edges) {
                edge_queue.push(destination_edge.add_cost(edge.cost));
            }
        }
        int path_end_node = end_node;
        using verit = vector<Edge>::reverse_iterator;
        for(verit rit = history.rbegin(); rit != history.rend(); ++rit) {
            if(rit->destination != path_end_node) {continue;}
            back_path.push_back(*rit);
            path_end_node = rit->departure;
        }
    }
    int get_cost(int start_node, int end_node, Edge &deleted_edge) {
        vector<bool> visited = vector<bool>(nodes.size(), false);
        visited[start_node] = true;
        vector<int> costs = vector<int>(nodes.size(), 0);
        priority_queue<Edge> edge_queue;
        for(Edge edge: nodes[start_node].edges) {
            edge_queue.push(edge);
        }
        vector<Edge> history;
        while(!edge_queue.empty()) {
            Edge edge = edge_queue.top();
            edge_queue.pop();
            if(visited[edge.destination]) {continue;}
            if(edge == deleted_edge) {continue;}
            history.push_back(edge);
            costs[edge.destination] = edge.cost;
            visited[edge.destination] = true;
            if(edge.destination == end_node) {break;}
            for(Edge &destination_edge: nodes[edge.destination].edges) {
                edge_queue.push(destination_edge.add_cost(edge.cost));
            }
        }
        return costs[end_node];
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