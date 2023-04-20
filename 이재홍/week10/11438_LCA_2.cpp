#include <iostream>
#include <vector>
#include <queue>
#define MAX_N 100001
#define MAX_LOG2_N 17
using namespace std;

int N;
vector<int> parents[MAX_N];
int level[MAX_N];
int waiting_queue[MAX_N];
int DAT[MAX_N];

void read_node_information() {
    cin >> N;
    for(int it = 1; it < N; ++it) {
        int node, parent;
        cin >> parent >> node;
        parents[parent].push_back(node);
        parents[node].push_back(parent);
    }
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        DAT[now] = 1;
        vector<int> real_parents;
        for(int it : parents[now]) {
            if(DAT[it]) {real_parents.push_back(it);}
            else {DAT[it] = 1; q.push(it);}
        }
        parents[now].clear();
        if(!real_parents.empty()) {
            parents[now].push_back(real_parents[0]);
        }
    }
}

void make_parents_table() {
    int level_difference = 0;
    int queued_nodes = N - 1;
    int it_end = N - 1;
    for(int it = 0; it < it_end; ++it) {
        waiting_queue[it] = it + 2;
    }
    while(queued_nodes) {
        int next_queued_nodes = 0;
        for(int it = 0; it < queued_nodes; ++it) {
            int &node = waiting_queue[it];
            int last_parent = parents[node][level_difference];
            if(parents[last_parent].size() < level_difference + 1) {continue;}
            parents[node].push_back(parents[last_parent][level_difference]);
            waiting_queue[next_queued_nodes] = node;
            ++next_queued_nodes;
        }
        ++level_difference;
        queued_nodes = next_queued_nodes;
    }
    level[1] = 1;
    for(int it = 2; it <= N; ++it) {
        vector<int> stack;
        vector<int> stack_level_diffence;
        int top = 0;
        stack.push_back(it);
        while(!level[stack[top]]) {
            level_difference = parents[stack[top]].size() - 1;
            int last_parent = parents[stack[top]][level_difference];
            stack.push_back(last_parent);
            stack_level_diffence.push_back(level_difference);
            ++top;
        }
        int level_now = level[stack[top]];
        while(top) {
            level_now += 1 << stack_level_diffence[top - 1];
            level[stack[top - 1]] = level_now;
            --top;
        }
    }
}

void process_query() {
    int M;
    cin >> M;
    for(int it = 0; it < M; ++it) {
        int node_1, node_2;
        cin >> node_1 >> node_2;
        if(level[node_1] < level[node_2]) {
            int node_temp = node_1;
            node_1 = node_2;
            node_2 = node_temp;
        }
        int level_difference = level[node_1] - level[node_2];
        int bitfinder = 0;
        while((1 << bitfinder) <= level_difference) {
            if((1 << bitfinder) & level_difference) {
                node_1 = parents[node_1][bitfinder];
            }
            ++bitfinder;
        }
        level_difference = parents[node_1].size() - 1;
        while(node_1 != node_2) {
            if(parents[node_1][level_difference] != parents[node_2][level_difference]) {
                node_1 = parents[node_1][level_difference];
                node_2 = parents[node_2][level_difference];
                level_difference = parents[node_1].size() - 1;
            }
            else if(0 < level_difference) {
                --level_difference;
            }
            else {
                node_1 = parents[node_1][level_difference];
                node_2 = parents[node_2][level_difference];
            }
        }
        cout << node_1 << '\n';
    }
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    read_node_information();
    make_parents_table();
    process_query();
    return 0;
}