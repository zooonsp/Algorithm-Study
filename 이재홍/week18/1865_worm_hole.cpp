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
    int undirected_edges_size_;
    int directed_edges_size_;
    vector<long long> costs_;
    vector<Edge> edges_;

public:
    BellmanFord(int nodes_size, int undirected_edges_size, int directed_edges_size):
        nodes_size_(nodes_size),
        undirected_edges_size_(undirected_edges_size),
        directed_edges_size_(directed_edges_size),
        costs_(vector<long long>(nodes_size + 1)),
        edges_(vector<Edge>((undirected_edges_size << 1) + directed_edges_size))
    {}
    void Read() {
        for(int it = 0; it < undirected_edges_size_; ++it) {
            cin >> edges_[it << 1].start >> edges_[it << 1].end >> edges_[it << 1].cost;
            edges_[(it << 1) + 1].start = edges_[it << 1].end;
            edges_[(it << 1) + 1].end = edges_[it << 1].start;
            edges_[(it << 1) + 1].cost = edges_[it << 1].cost;
        }
        for(int it = undirected_edges_size_ << 1; it < (undirected_edges_size_ << 1) + directed_edges_size_; ++it) {
            cin >> edges_[it].start >> edges_[it].end >> edges_[it].cost;
            edges_[it].cost = -edges_[it].cost;
        }
    }
    bool Run(int start_node = 1) {
        for(int it = 1; it <= nodes_size_; ++it) {
            costs_[it] = INF;
        }
        for(int it = 1; it < nodes_size_; ++it) {
            for(Edge &edge: edges_) {
                long long new_cost = costs_[edge.start] + edge.cost;
                if(costs_[edge.end] <= new_cost) {continue;}
                costs_[edge.end] = new_cost;
            }
        }
        for(Edge &edge: edges_) {
            long long new_cost = costs_[edge.start] + edge.cost;
            if(costs_[edge.end] <= new_cost) {continue;}
            return true;
        }
        return false;
    }
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int testcases;
    cin >> testcases;
    for(int testcase = 1; testcase <= testcases; ++testcase) {
        int nodes, undirected_edges, directed_edges;
        cin >> nodes >> undirected_edges >> directed_edges;
        BellmanFord bellmanFord{nodes, undirected_edges, directed_edges};
        bellmanFord.Read();
        if(bellmanFord.Run()) {
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
    return 0;
}