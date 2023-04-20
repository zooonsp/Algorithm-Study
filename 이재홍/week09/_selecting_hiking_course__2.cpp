#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    static const int POINT = 0;
    static const int GATE = 0b01;
    static const int SUMMIT = 0b10;
    static const int CONNECTED = 0b11;

    int index;
    int kind;
};

vector<Node> u_set;

Node u_find(Node node) {
    if(u_set[node.index].index != node.index) {
        Node upper_node = u_find(u_set[node.index]);
        u_set[node.index].index = upper_node.index;
        return upper_node;
    }
    return u_set[node.index];
}

int u_union(Node node_1, Node node_2) {
    Node s_node_1 = u_find(node_1);
    Node s_node_2 = u_find(node_2);
    if(s_node_1.index == s_node_2.index) {return 0;}
    if(s_node_1.kind == Node::POINT) {
        u_set[s_node_2.index].kind |= s_node_1.kind;
        u_set[s_node_1.index].index = s_node_2.index;
        return 0;
    }
    else if(s_node_2.kind == Node::POINT) {
        u_set[s_node_1.index].kind |= s_node_2.kind;
        u_set[s_node_2.index].index = s_node_1.index;
        return 0;
    }
    else if(s_node_1.kind == Node::GATE) {
        int new_connected_index = s_node_2.kind == Node::SUMMIT ? s_node_2.index : 0;
        u_set[s_node_2.index].kind |= s_node_1.kind;
        u_set[s_node_1.index].index = s_node_2.index;
        return new_connected_index;
    }
    else if(s_node_2.kind == Node::GATE) {
        int new_connected_index = s_node_1.kind == Node::SUMMIT ? s_node_1.index : 0;
        u_set[s_node_1.index].kind |= s_node_2.kind;
        u_set[s_node_2.index].index = s_node_1.index;
        return new_connected_index;
    }
    else if(s_node_1.index > s_node_2.index) {
        int new_connected_index = (s_node_2.kind == Node::SUMMIT && s_node_1.kind != Node::SUMMIT) ? s_node_2.index : 0;
        u_set[s_node_2.index].kind |= s_node_1.kind;
        u_set[s_node_1.index].index = s_node_2.index;
        return new_connected_index;
    }
    else {
        int new_connected_index = (s_node_1.kind == Node::SUMMIT && s_node_2.kind != Node::SUMMIT) ? s_node_1.index : 0;
        u_set[s_node_1.index].kind |= s_node_2.kind;
        u_set[s_node_2.index].index = s_node_1.index;
        return new_connected_index;
    }
}

bool compare(vector<int> &lhs, vector<int> &rhs) {
    return lhs[2] < rhs[2];
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    u_set.push_back({0, 0});
    for(int it = 1; it <= n; ++it) {u_set.push_back({it, 0});}
    for(int gate : gates) {u_set[gate].kind = Node::GATE;}
    for(int summit : summits) {u_set[summit].kind = Node::SUMMIT;}

    sort(paths.begin(), paths.end(), compare);
    int connected_summits_flag = 0;
    int path_size = paths.size();
    int path_index = 0;
    int previous_intensity{};
    while(path_index < path_size) {
        previous_intensity = paths[path_index][2];
        while(path_index < path_size && previous_intensity == paths[path_index][2]) {
            Node &first_node = u_set[paths[path_index][0]];
            Node &second_node = u_set[paths[path_index][1]];
            connected_summits_flag |= u_union(first_node, second_node);
            ++path_index;
        }
        if(connected_summits_flag) {break;}
    }

    vector<int> answer;
    for(int it = 1; it <= n; ++it) {u_set[it] = {it, 0};}
    for(int gate : gates) {u_set[gate].kind = Node::GATE;}
    for(int summit : summits) {u_set[summit].kind = Node::SUMMIT;}
    for(int path_it = 0; path_it < path_index; ++path_it) {
        Node &first_node = u_set[paths[path_it][0]];
        Node &second_node = u_set[paths[path_it][1]];
        if(first_node.kind == Node::SUMMIT || second_node.kind == Node::SUMMIT) {continue;}
        u_union(first_node, second_node);
    }
    priority_queue<int, vector<int>, greater<int>> connected_summits;
    for(int path_it = 0; path_it < path_index; ++path_it) {
        Node &first_node = u_set[paths[path_it][0]];
        Node &second_node = u_set[paths[path_it][1]];
        if(first_node.kind == Node::SUMMIT && u_find(second_node).kind == Node::GATE) {connected_summits.push(first_node.index);}
        else if(second_node.kind == Node::SUMMIT && u_find(first_node).kind == Node::GATE) {connected_summits.push(second_node.index);}
    }
    while(answer.empty()) {
        answer.push_back(connected_summits.top());
        answer.push_back(previous_intensity);
    }
    return answer;
}