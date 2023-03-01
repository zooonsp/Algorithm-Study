#include <iostream>
#include <queue>
#define NMAX 32
#define MMAX 60
#define DIR 4
using namespace std;
// use floodfill, dijkstra and tunnel checking to find minimum cost


struct Coordinate {
    int x;
    int y;
    Coordinate operator+(Coordinate p) {
        return {x + p.x, y + p.y};
    }
    bool operator==(Coordinate p) {
        return x == p.x && y == p.y;
    }
    bool operator!=(Coordinate p) {
        return x != p.x || y != p.y;
    }
};

int N; // height, width of map
int field[NMAX][NMAX]; // height of mountain
int field_info[NMAX][NMAX]; // 0: no tunnel, 1: more than 1 tunnel, 2: wall
int cost_map[NMAX][NMAX]; // cost map
int M;
Coordinate tunnel[MMAX]; // use bitwise operation to switch position
int tunnel_cost[MMAX]; // use bitwise operation to switch position
queue<Coordinate> q; // bfs queue

Coordinate d[DIR] = {
    {-1, 0},
    { 0,-1},
    { 1, 0},
    { 0, 1}
};

int cost(int &from, int &to) {
    if(from < to) return (to - from) << 1;
    if(from > to) return 0;
    return 1;
}

void read_field() {
    cin >> N; // height, width
    cin >> M; // tunnels
    for(int i = 0; i <= N + 1; ++i) { // top wall
        field_info[0][i] = 2;
    }
    for(int i = 1; i <= N; ++i) { // left right wall
        field_info[i][0] = 2;
        field_info[i][N + 1] = 2;
    }
    for(int i = 0; i <= N + 1; ++i) { // bottom wall
        field_info[N + 1][i] = 2;
    }
    for(int i = 1; i <= N; ++i) { // read field info
        for(int j = 1; j <= N; ++j) {
            cin >> field[i][j];
            field_info[i][j] = 0;
            cost_map[i][j] = 0;
        }
    }
    for(int i = 0; i < M; ++i) { // tunnel info
        int y1, x1, y2, x2, cost;
        cin >> y1 >> x1 >> y2 >> x2 >> cost;
        field_info[y1][x1] = 1;
        field_info[y2][x2] = 1;
        int idx = i << 1;
        tunnel[idx].x = x1;
        tunnel[idx].y = y1;
        tunnel_cost[idx] = cost;
        ++idx;
        tunnel[idx].x = x2;
        tunnel[idx].y = y2;
        tunnel_cost[idx] = cost;
    }
}

void bfs() {
    // prepare queue
    q.push({1, 1});
    cost_map[1][1] = 1;
    // start bfs
    while(q.size()) {
        // pop front of queue
        Coordinate now = q.front();
        q.pop();
        // backtracking
        for(int i = 0; i < DIR; ++i) { // adjacent 4 points
            Coordinate next = now + d[i];
            int cost_next = cost(field[now.y][now.x], field[next.y][next.x]);
            // pruning
            if(field_info[next.y][next.x] == 2) {continue;} // wall
            if(cost_map[next.y][next.x] && cost_map[next.y][next.x] <= cost_map[now.y][now.x] + cost_next) {continue;} // slower route
            // process
            cost_map[next.y][next.x] = cost_map[now.y][now.x] + cost_next;
            // push into queue
            q.push(next);
        }
        if(field_info[now.y][now.x] != 1) {continue;} // tunnels
        int M2 = M << 1;
        for(int i = 0; i < M2; ++i) {
            if(now != tunnel[i]) {continue;} // not this point
            Coordinate next = tunnel[i ^ 1];
            int cost_next = tunnel_cost[i];
            // pruning
            if(cost_map[next.y][next.x] && cost_map[next.y][next.x] <= cost_map[now.y][now.x] + cost_next) {continue;} // slower route
            // process
            cost_map[next.y][next.x] = cost_map[now.y][now.x] + cost_next;
            // push into queue
            q.push(next);
        }
    }
}

int main() {
    int T;
    cin >> T;
    for(int testcase = 1; testcase <= T; ++testcase) {
        read_field();
        bfs();
        cout << '#' << testcase << ' ' << (cost_map[N][N] - 1) << '\n';
    }
    return 0;
}