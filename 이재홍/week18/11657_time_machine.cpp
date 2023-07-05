#include <iostream>
#include <vector>
using namespace std;

#define INF 900'0000'0000'0000'0000L

struct Edge {
    int start;
    int end;
    long long cost;
};

class BellmanFord {
    int nodes_size_;
    int edges_size_;
    vector<long long> costs_;
    vector<Edge> edges_;

public:
    BellmanFord(int nodes_size, int edges_size): nodes_size_(nodes_size), edges_size_(edges_size), costs_(vector<long long>(nodes_size + 1)), edges_(vector<Edge>(edges_size)) {}
    void Read() {
        for(Edge &edge: edges_) {
            cin >> edge.start >> edge.end >> edge.cost;
        }
    }
    bool Run(int start_node = 1) {
        for(int it = 1; it <= nodes_size_; ++it) {
            costs_[it] = INF;
        }
        costs_[start_node] = 0;
        for(int it = 1; it < nodes_size_; ++it) {
            for(Edge &edge: edges_) {
                if(costs_[edge.start] == INF) {continue;}
                long long new_cost = costs_[edge.start] + edge.cost;
                if(costs_[edge.end] <= new_cost) {continue;}
                costs_[edge.end] = new_cost;
            }
        }
        for(Edge &edge: edges_) {
            if(costs_[edge.start] == INF) {continue;}
            long long new_cost = costs_[edge.start] + edge.cost;
            if(costs_[edge.end] <= new_cost) {continue;}
            return true;
        }
        for(int it = 1; it <= nodes_size_; ++it) {
            if(costs_[it] == INF) {costs_[it] = -1;}
        }
        return false;
    }
    void Print(int start_node = 1) {
        for(int it = 1; it < start_node; ++it) {cout << costs_[it] << '\n';}
        for(int it = start_node + 1; it <= nodes_size_; ++it) {cout << costs_[it] << '\n';}
    }
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int nodes, edges;
    cin >> nodes >> edges;
    BellmanFord bellmanFord{nodes, edges};
    bellmanFord.Read();
    if(bellmanFord.Run()) {
        cout << -1;
        return 0;
    }
    bellmanFord.Print();
    return 0;
}