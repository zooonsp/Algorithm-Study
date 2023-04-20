#include <iostream>
#include <stack>
#include <queue>
#define MAXSET 2
#define MAXVIL 8
#define BIGNUM 987654321
using namespace std;
// assign all node to 2 sets
// see all possible combination and check if split is valid

int N;
int node_pop[MAXVIL];
int node_set[MAXVIL];
int node_set_ideal[MAXVIL];
int min_diff;

int adj[MAXVIL][MAXVIL];

int u_find(int n) {
    if(node_set[n] != n) {return node_set[n] = u_find(node_set[n]);}
    return n;
}

void u_union(int n1, int n2) {
    int sn1 = u_find(n1);
    int sn2 = u_find(n2);
    if(sn1 == sn2) {return;}
    node_set[sn2] = sn1;
    return;
}

void read_data() {
    cin >> N;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {cin >> adj[i][j];}
    }
    for(int i = 0; i < N; ++i) {cin >> node_pop[i];}
}

void grouping() { // make union of nodes
    for(int i = 0; i < N; ++i) {node_set[i] = i;}
    for(int i = 0; i < N; ++i) {
        for(int j = i + 1; j < N; ++j) {
            if(adj[i][j] && node_set_ideal[i] == node_set_ideal[j]) {u_union(i, j);}
        }
    }
}

bool validate_split(int n = MAXSET) { // validate if graph has 2 set
    int groups = 0;
    for(int i = 0; i < N; ++i) {
        if(node_set[i] == i) {++groups;}
    }
    return groups <= n;
}

int get_diff() { // get absolute value of population difference
    int diff = 0;
    for(int i = 0; i < N; ++i) {diff += ((node_set_ideal[i] << 1) - 1) * node_pop[i];}
    return diff < 0 ? -diff : diff;
}

void dfs(int now) { // generate ideal node set and validate it
    // condition check
    if(N <= now) {
        grouping();
        if(validate_split()) {
            int diff = get_diff();
            min_diff = diff < min_diff ? diff : min_diff;
        }
        return;
    }
    // backtracking
    for(int i = 0; i < MAXSET; ++i) {
        // process
        node_set_ideal[now] = i;
        // recursive
        dfs(now + 1);
        // unprocess
    }
}

int main() {
    // read 1 int
    int T;
    cin >> T;
    // run testcase loop
    for(int testcase = 1; testcase <= T; ++testcase) {
        read_data();
        min_diff = BIGNUM;
        dfs(1); // fix first node
        cout << '#' << testcase << ' ' << min_diff << '\n';
    }
    return 0;
}