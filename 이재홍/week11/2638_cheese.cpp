#include <iostream>
#include <queue>
#define DIR 4
#define MAX_ROW 100
#define MAX_COLUMN 100
#define CHEESE 1
#define AIR 0
#define CRITERIA 2
using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &rhs) const {return {x + rhs.x, y + rhs.y};}
};

Coordinate d[DIR] = {{ 0,-1}, {-1, 0}, { 1, 0}, { 0, 1}};

int row;
int column;
int field[MAX_ROW][MAX_COLUMN];
int visited[MAX_ROW][MAX_COLUMN];

void read() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> row >> column;
    for(int row_it = 0; row_it < row; ++row_it) {
        for(int column_it = 0; column_it < column; ++column_it) {
            cin >> field[row_it][column_it];
        }
    }
}

bool out(Coordinate &position) {
    return position.x < 0 || position.y < 0 || column <= position.x || row <= position.y;
}

void bfs(int &rounds) {
    rounds = 0;
    queue<Coordinate> air;
    queue<Coordinate> cheese;
    air.push({0, 0});
    visited[0][0] = 1;
    while(!air.empty() || !cheese.empty()) {
        while(!air.empty()) {
            Coordinate now = air.front();
            air.pop();
            for(int dir = 0; dir < DIR; ++dir) {
                Coordinate next = now + d[dir];
                if(out(next)) {continue;}
                if(visited[next.y][next.x]) {continue;}
                visited[next.y][next.x] = 1;
                if(field[next.y][next.x] == CHEESE) {cheese.push(next);}
                else if(field[next.y][next.x] == AIR) {air.push(next);}
            }
        }
        if(cheese.empty()) {break;}
        int cheese_size = cheese.size();
        queue<Coordinate> melt;
        while(cheese_size) {
            Coordinate now = cheese.front();
            cheese.pop();
            int air_around = 0;
            for(int dir = 0; dir < DIR; ++dir) {
                Coordinate next = now + d[dir];
                if(out(next)) {continue;}
                if(field[next.y][next.x] == AIR && visited[next.y][next.x]) {++air_around;}
            }
            if(CRITERIA <= air_around) {melt.push(now);}
            else {cheese.push(now);}
            --cheese_size;
        }
        while(!melt.empty()) {
            Coordinate now = melt.front();
            melt.pop();
            field[now.y][now.x] = AIR;
            air.push(now);
        }
        ++rounds;
    }
    return;
}

int main() {
    read();
    int rounds;
    bfs(rounds);
    cout << rounds;
    return 0;
}