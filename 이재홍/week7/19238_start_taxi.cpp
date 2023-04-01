#include <iostream>
#include <queue>
#define DIR 4
#define NMAX 22
#define MMAX 401

#define WALL -1
using namespace std;
// find nearest customer, run flood fill from goal of customer, find taxi and next customer
// add dummy 0th goal at taxi
// add dummy M+1th customer at last goal

// workflow
// find: taxi - 0th goal(dummy), 0th goal - next customer (1st flood fill)
// find: taxi - 1st goal, 1st goal - next customer (2nd flood fill)
// ...
// find: taxi - M-1th goal, M-1th goal - next customer (Mth flood fill)
// find: taxi - Mth goal, Mth goal - Mth goal(dummy) (M+1th flood fill)

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &pos) {return {x + pos.x, y + pos.y};}
    bool operator==(const Coordinate & pos) {return x == pos.x && y == pos.y;}
    bool operator<(const Coordinate & pos) {return y < pos.y || y == pos.y && x < pos.x;}
};
using Cor = Coordinate;

Cor d[DIR] = {{-1, 0}, { 0,-1}, { 1, 0}, { 0, 1}};

int N, M, fuel;
int field[NMAX][NMAX];
int visited[NMAX][NMAX];
Cor s[MMAX]; // start: customer
Cor e[MMAX]; // end: goal of customer
Cor taxi;

void clear_visited() {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            visited[i][j] = 0;
        }
    }
}

int floodfill(int customer, Cor taxiNow) {
    // prepare queue
    queue<Cor> q;
    q.push(e[customer]);
    // prepare visited
    clear_visited();
    visited[e[customer].y][e[customer].x] = 1;
    // start floodfill (round by round)
    int next_customer = 0;
    int ttog = -1; // taxi to goal fuel cunsumption
    int gton = -1; // goal to next customer fuel cunsumption
    if(taxiNow == e[customer]) { // taxi at goal
        ttog = 0;
    }
    if(0 < field[e[customer].y][e[customer].x]) { // next customer at goal
        next_customer = field[e[customer].y][e[customer].x];
        gton = 0;
        taxi = e[customer];
    }
    while(q.size() && (ttog < 0 || gton < 0)) {
        int qSize = q.size();
        for(int qi = 0; qi < qSize; ++qi) {
            // pop front of queue
            Cor now = q.front();
            q.pop();
            // backtracking
            for(int dir = 0; dir < DIR; ++dir) {
                Cor next = now + d[dir];
                // pruning
                if(field[next.y][next.x] == WALL) {continue;}
                if(visited[next.y][next.x]) {continue;}
                // process
                visited[next.y][next.x] = visited[now.y][now.x] + 1;
                if(taxiNow == next) { // taxi to goal
                    ttog = visited[now.y][now.x];
                }
                if(0 < field[next.y][next.x] && s[field[next.y][next.x]] < s[next_customer] && (gton < 0 || gton == visited[now.y][now.x])) { // goal to next customer
                    next_customer = field[next.y][next.x];
                    gton = visited[now.y][now.x];
                    taxi = next;
                }
                // push into queue
                q.push(next);
            }
        }
    }
    // calculate fuel
    if(ttog < 0 || gton < 0) {return -1;} // can not reach next customer by wall
    if(fuel < ttog) {return -1;} // can not reach goal
    fuel += ttog;
    if(fuel < gton) {return -1;} // can not reach next customer
    fuel -= gton;
    field[s[next_customer].y][s[next_customer].x] = 0;
    return next_customer;
}

int drive() {
    // start drive
    int now_customer = 0;
    for(int i = 0; i < M; ++i) {
        now_customer = floodfill(now_customer, taxi);
        if(now_customer < 0) {return -1;}
    }
    field[e[now_customer].y][e[now_customer].x] = M; // set dummy customer at last customer's goal
    int result = floodfill(now_customer, taxi);
    if(result < 0) {return -1;}
    return fuel;
}

void readInfo() {
    cin >> N >> M >> fuel;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            cin >> field[i][j];
            field[i][j] = -field[i][j]; // change 1 to -1 (WALL)
        }
    }
    cin >> taxi.y >> taxi.x;
    s[0].y = NMAX; // dummy start point
    s[0].x = NMAX;
    e[0].y = taxi.y; // dummy 0th goal (start point)
    e[0].x = taxi.x;
    for(int i = 1; i <= M; ++i) {
        cin >> s[i].y >> s[i].x >> e[i].y >> e[i].x;
        field[s[i].y][s[i].x] = i;
    }
    return;
}

void createWall() {
    for(int i = 1; i <= N; ++i) {
        field[0][i] = WALL;
        field[i][0] = WALL;
        field[N + 1][i] = WALL;
        field[i][N + 1] = WALL;
    }
    return;
}

int main() {
    readInfo();
    createWall();
    int ans = drive();
    cout << ans;
    return 0;
}