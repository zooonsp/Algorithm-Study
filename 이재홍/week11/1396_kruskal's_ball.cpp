#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
using namespace std;

struct Edge {
    int departure;
    int destination;
    int temperature;
    bool operator<(const Edge &rhs) const {return temperature <rhs.temperature;}
};

struct Node {
    int left;
    int right;
    int mid;
    int index;
    int departure;
    int destination;
    bool operator<(const Node &rhs) const {return mid > rhs.mid;}
};

int *u_set;
int *u_set_size;

int u_find(int node) {
    if(node != u_set[node]) {
        return u_set[node] = u_find(u_set[node]);
    }
    return node;
}

void u_union(int node_1, int node_2) {
    int s_node_1 = u_find(node_1);
    int s_node_2 = u_find(node_2);
    if(s_node_1 == s_node_2) {return;}
    u_set[s_node_2] = s_node_1;
    u_set_size[s_node_1] += u_set_size[s_node_2];
    return;
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    u_set = new int[N + 1];
    u_set_size = new int[N + 1];
    vector<Edge> v = vector<Edge>(M);
    for(int it = 0; it < M; ++it) {
        Edge e;
        cin >> e.departure >> e.destination >> e.temperature;
        v[it] = e;
    }
    sort(v.begin(), v.end());
    int it = 0;
    int Q;
    cin >> Q;
    int *query_result_minimum_temperature = new int[Q];
    int *query_result_size = new int[Q];
    priority_queue<Node> q[2];
    int q_index = 0;
    for(int it = 1; it <= N; ++it) {u_set[it] = it;}
    for(int it = 1; it <= N; ++it) {u_set_size[it] = 1;}
    for(int it = 0; it < M; ++it) {u_union(v[it].departure, v[it].destination);}
    for(int it = 0; it < Q; ++it) {
        Node node;
        node.left = 0;
        node.right = M - 1;
        node.mid = (node.left + node.right) >> 1;
        node.index = it;
        cin >> node.departure >> node.destination;
        if(u_find(node.departure) == u_find(node.destination)) {q[q_index].push(node);}
        else {query_result_minimum_temperature[it] = 0;}
    }
    while(!q[0].empty() || !q[1].empty()) {
        for(int it = 1; it <= N; ++it) {u_set[it] = it;}
        for(int it = 1; it <= N; ++it) {u_set_size[it] = 1;}
        int q_index_next = q_index ^ 1;
        int it = 0;
        while(!q[q_index].empty()) {
            Node now = q[q_index].top();
            q[q_index].pop();
            while(it <= now.mid) {u_union(v[it].departure, v[it].destination); ++it;}
            if(u_find(now.departure) == u_find(now.destination)) {
                now.right = now.mid;
                now.mid = (now.left + now.right) >> 1;
                if(now.right == now.left) {
                    query_result_minimum_temperature[now.index] = v[now.mid].temperature;
                    query_result_size[now.index] = u_set_size[u_find(now.departure)];
                }
                else {
                    q[q_index_next].push(now);
                }
            }
            else {
                now.left = now.mid + 1;
                now.mid = (now.left + now.right) >> 1;
                if(now.right == now.left) {
                    query_result_minimum_temperature[now.index] = v[now.mid].temperature;
                    query_result_size[now.index] = u_set_size[u_find(now.departure)] + u_set_size[u_find(now.destination)];
                }
                else {
                    q[q_index].push(now);
                }
            }
        }
        q_index = q_index_next;
    }
    for(int query_it = 0; query_it < Q; ++query_it) {
        if(!query_result_minimum_temperature[query_it]) {cout << -1 << '\n';}
        else {cout << query_result_minimum_temperature[query_it] << ' ' << query_result_size[query_it] << '\n';}
    }
    delete[] u_set;
    delete[] u_set_size;
    delete[] query_result_minimum_temperature;
    delete[] query_result_size;
    return 0;
}