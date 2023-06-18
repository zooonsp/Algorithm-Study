#include <iostream>
using namespace std;

void down(int *from, int *to, int *add) {
    to[0] = (from[2] < from[1] ? from[2] : from[1]) + add[0];
    to[1] = (from[0] < from[2] ? from[0] : from[2]) + add[1];
    to[2] = (from[1] < from[0] ? from[1] : from[0]) + add[2];
}

int find_min_cost() {
    int N;
    cin >> N;
    const int INF = 1000000;
    int costs[2][9];
    costs[0][1] = costs[0][2] = costs[0][3] = costs[0][5] = costs[0][6] = costs[0][7] = INF;
    int toggle = 1;
    cin >> costs[0][0] >> costs[0][4] >> costs[0][8];
    for(int it = 1; it < N; ++it) {
        int RGB_cost[3];
        cin >> RGB_cost[0] >> RGB_cost[1] >> RGB_cost[2];
        down(&costs[toggle ^ 1][0], &costs[toggle][0], &RGB_cost[0]);
        down(&costs[toggle ^ 1][3], &costs[toggle][3], &RGB_cost[0]);
        down(&costs[toggle ^ 1][6], &costs[toggle][6], &RGB_cost[0]);
        toggle ^= 1;
    }
    toggle ^= 1;
    int min_cost = INF;
    costs[toggle][0] = costs[toggle][4] = costs[toggle][8] = INF;
    for(int it = 0; it < 9; ++it) {
        min_cost = min_cost < costs[toggle][it] ? min_cost : costs[toggle][it];
    }
    return min_cost;
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    cout << find_min_cost();
    return 0;
}