#include <iostream>
#include <queue>
#define DIR 4
#define NMAX 52
#define VMAX 20
#define BIGNUM 987654321
// NAMES
#define WALL 1
#define VIRUS_SLEEP 2
#define VIRUS_AWAKE 3

using namespace std;
// simple bfs (combination way)
// floodfill after all point selected

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &p) const {return {x + p.x, y + p.y};}
    Coordinate & operator()(const int &x_, const int &y_) {x = x_; y = y_; return *this;}
};

using Coor = Coordinate;
Coor d[DIR] = {{-1, 0}, { 0,-1}, { 1, 0}, { 0, 1}};

int fieldLen;
int virusToSelect;
int virusSize;
int field[NMAX][NMAX];
int visited[NMAX][NMAX];
Coor virus[VMAX];
int virusSel[VMAX];
int ableFlag;
int minTurns = BIGNUM;
int zeros;
queue<Coor> q; // queue for virus flood fill

void floodFill() {
    // prepare queue
    for(int i = 0; i < virusSize; ++i) {if(virusSel[i]) {q.push(virus[i]);}}
    // start bfs
    int turns = 0;
    int colony = 0; // area consumed by virus
    while(q.size()) {
        ++turns;
        int qSize = q.size();
        // pruning
        if(minTurns <= turns) {
            while(q.size()) {q.pop();}
            break;
        }
        for(int i = 0; i < qSize; ++i) { // run 1 turn of bfs
            // pop front of queue
            Coor now = q.front();
            q.pop();
            // backtracking
            for(int dir = 0; dir < DIR; ++dir) {
                Coor next = now + d[dir];
                // pruning
                if(field[next.y][next.x] == WALL) {continue;}
                if(visited[next.y][next.x]) {continue;}
                // process
                visited[next.y][next.x] = turns;
                if(field[next.y][next.x] != VIRUS_SLEEP) {++colony;}
                // push into queue
                q.push(next);
            }
        }
        // check if all space is consumed (remaining queue elements are all sleeping virus)
        if(zeros == colony) {
            while(q.size()) {q.pop();}
            break;
        }
    }
    // check all zeros are filled
    if(zeros == colony) {
        ableFlag = 1;
        minTurns = turns < minTurns ? turns : minTurns;
    }
    return;
}

void clearVisited() {
    for(int i = 1; i <= fieldLen; ++i) {for(int j = 1; j <=fieldLen; ++j) {visited[i][j] = 0;}}
    for(int i = 0; i < virusSize; ++i) {if(virusSel[i]) {visited[virus[i].y][virus[i].x] = -1;}}
    return;
}

void dfs(int now, int toSelect) { // select virus
    // condition check
    if(!toSelect) {
        floodFill();
        clearVisited();
        return;
    }
    // backtracking
    for(int i = now; i <= virusSize - toSelect; ++i) {
        // process
        virusSel[i] = 1;
        field[virus[i].y][virus[i].x] = 3; // change selected virus to 3
        visited[virus[i].y][virus[i].x] = -1; // set start point visited value to -1
        // recursive
        dfs(i + 1, toSelect - 1);
        // unprocess
        virusSel[i] = 0;
        field[virus[i].y][virus[i].x] = 2; // recover virus
        visited[virus[i].y][virus[i].x] = 0; // recover visited
    }
    return;
}

int main() {
    // initiate fast io
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // read 2 int
    cin >> fieldLen >> virusToSelect;
    // read field info
    for(int i = 1; i <= fieldLen; ++i) {
        for(int j = 1; j <= fieldLen; ++j) {
            cin >> field[i][j];
            if(!field[i][j]) {++zeros;}
            if(field[i][j] == VIRUS_SLEEP) {
                virus[virusSize](j, i);
                ++virusSize;
            }
        }
    }
    // if there are no space left, print result
    if(!zeros) {cout << 0; return 0;}
    // put fence around field
    for(int i = 1; i <= fieldLen; ++i) {
        field[0][i] = WALL;
        field[i][0] = WALL;
        field[fieldLen + 1][i] = WALL;
        field[i][fieldLen + 1] = WALL;
    }
    // run dfs
    dfs(0, virusToSelect);
    // print result
    if(ableFlag) {cout << minTurns;}
    else {cout << -1;}
    return 0;
}