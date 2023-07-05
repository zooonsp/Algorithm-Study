#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    vector<int> to;
};

struct Graph {
    vector<Node> nodes;
    vector<bool> articulation_points;
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
    int dfs(int level, int node_id, vector<bool> &visited, vector<int> &levels) {
        visited[node_id] = true;
        levels[node_id] = level;
        int connected_min_level = level - 1;
        for(int next_node_id: nodes[node_id].to) {
            if(visited[next_node_id]) {
                connected_min_level = connected_min_level < levels[next_node_id] ? connected_min_level : levels[next_node_id];
                continue;
            }
            int next_node_connected_min_level = dfs(level + 1, next_node_id, visited, levels);
            if(level <= next_node_connected_min_level) {articulation_points[node_id] = true;}
            connected_min_level = connected_min_level < next_node_connected_min_level ? connected_min_level : next_node_connected_min_level;
        }
        return connected_min_level;
    }
    int dfs_root(int level, int node_id, vector<bool> &visited, vector<int> &levels) {
        visited[node_id] = true;
        levels[node_id] = level;
        int number_of_child = 0;
        for(int next_node_id: nodes[node_id].to) {
            if(visited[next_node_id]) {continue;}
            ++number_of_child;
            dfs(level + 1, next_node_id, visited, levels);
        }
        if(2 <= number_of_child) {articulation_points[node_id] = true;}
        return 0;
    }
    void find_articulation_points() {
        articulation_points = vector<bool>(nodes.size(), false);
        vector<bool> visited = vector<bool>(nodes.size(), false);
        vector<int> levels = vector<int>(nodes.size(), 0);
        for(int it = 1; it < nodes.size(); ++it) {
            if(visited[it]) {continue;}
            dfs_root(0, it, visited, levels);
        }
    }
    int number_of_articulation_points() {
        int points = 0;
        for(bool point: articulation_points) {points += point;}
        return points;
    }
    void print_articulation_points() {
        int it = 1;
        for(; it < articulation_points.size(); ++it) {
            if(articulation_points[it]) {cout << it; ++it; break;}
        }
        for(; it < articulation_points.size(); ++it) {
            if(articulation_points[it]) {cout << ' ' << it;}
        }
    }
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    Graph graph{};
    graph.find_articulation_points();
    cout << graph.number_of_articulation_points() << '\n';
    graph.print_articulation_points();
    return 0;
}