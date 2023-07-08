#include <string>
#include <vector>
#include <queue>

using namespace std;

#define INF 123456789

struct Edge {
    int to;
    int cost;
    Edge(int to, int cost): to(to), cost(cost) {}
    bool operator<(const Edge &rhs) const {return cost > rhs.cost;}
    Edge operator+(int add_cost) {return Edge{to, cost + add_cost};}
};

struct Node {
    vector<Edge> edges;
    void add(int to, int cost) {
        edges.push_back(Edge{to, cost});
    }
};

struct Graph {
    vector<Node> nodes;
    Graph(int size): nodes(vector<Node>(size + 1)) {}
    void connect(int node1, int node2, int cost) {
        nodes[node1].add(node2, cost);
        nodes[node2].add(node1, cost);
    }
    void dijkstra(int start_node, vector<int> &costs) {
        priority_queue<Edge> edges;
        vector<int> visited = vector<int>(nodes.size(), 0);
        int remain_nodes = nodes.size();
        edges.push(Edge{start_node, 0});
        while(--remain_nodes) {
            Edge path = Edge{0, 0};
            while(true) {
                if(edges.empty()) {return;}
                path = edges.top();
                edges.pop();
                if(visited[path.to]) {continue;}
                break;
            }
            visited[path.to] = 1;
            costs[path.to] = path.cost;
            for(Edge &edge: nodes[path.to].edges) {
                edges.push(edge + path.cost);
            }
        }
    }
};

int get_min_sum_cost(int n, vector<int> costs1, vector<int> costs2, vector<int> costs3) {
    int sum = INF;
    int index = 0;
    for(int it = 1; it <= n; ++it) {
        if(sum < costs1[it] + costs2[it] + costs3[it]) {continue;}
        sum = costs1[it] + costs2[it] + costs3[it];
        index = it;
    }
    return sum;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    Graph graph{n};
    for(vector<int> &fare: fares) {
        graph.connect(fare[0], fare[1], fare[2]);
    }
    vector<int> to_s_cost = vector<int>(n + 1, INF);
    vector<int> to_a_cost = vector<int>(n + 1, INF);
    vector<int> to_b_cost = vector<int>(n + 1, INF);
    graph.dijkstra(s, to_s_cost);
    graph.dijkstra(a, to_a_cost);
    graph.dijkstra(b, to_b_cost);
    int answer = get_min_sum_cost(n, to_s_cost, to_a_cost, to_b_cost);
    return answer;
}