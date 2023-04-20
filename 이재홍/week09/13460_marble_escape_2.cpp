#include <iostream>
#include <queue>
#include <string>
#define DIR 4
using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &rhs) const;
    Coordinate operator-(const Coordinate &rhs) const;
    Coordinate operator*(const Coordinate &rhs) const;
    bool operator!=(const Coordinate &rhs) const;
};
Coordinate Coordinate::operator+(const Coordinate &rhs) const {return {x + rhs.x, y + rhs.y};}
Coordinate Coordinate::operator-(const Coordinate &rhs) const {return {x - rhs.x, y - rhs.y};}
Coordinate Coordinate::operator*(const Coordinate &rhs) const {return {x * rhs.x, y * rhs.y};}
bool Coordinate::operator!=(const Coordinate &rhs) const {return x != rhs.x || y != rhs.y;}

Coordinate d[DIR] = {{-1, 0}, { 0,-1}, { 0, 1}, { 1, 0}};

struct Marble {
    Coordinate red;
    Coordinate blue;
    Marble();
    Marble(Coordinate red_, Coordinate blue_);
};

Marble::Marble() {}
Marble::Marble(Coordinate red_, Coordinate blue_) : red(red_), blue(blue_) {}

struct Board {
    static const int MAX_N = 10;
    static const int WALL = '#';
    static const int HOLE = 'O';
    static const int RED = 'R';
    static const int BLUE = 'B';
    int row;
    int column;
    Marble marble_start;
    string field[MAX_N];
    int visited[MAX_N][MAX_N][MAX_N][MAX_N];
    void read_field();
    void intitiate_visited();
    Marble move(Marble &marble, int dir);
    int bfs();
};

void Board::read_field() {
    cin >> row >> column;
    for(int row_it = 0; row_it < row; ++row_it) {
        cin >> field[row_it];
        for(int column_it = 0; column_it < column; ++column_it) {
            if(field[row_it][column_it] == RED) {marble_start.red = {column_it, row_it};}
            else if(field[row_it][column_it] == BLUE) {marble_start.blue = {column_it, row_it};}
        }
    }
}

void Board::intitiate_visited() {
    for(int red_row_it = 0; red_row_it < row; ++red_row_it)
        for(int red_column_it = 0; red_column_it < column; ++red_column_it)
            for(int blue_row_it = 0; blue_row_it < row; ++blue_row_it)
                for(int blue_column_it = 0; blue_column_it < column; ++blue_column_it)
                    visited[red_row_it][red_column_it][blue_row_it][blue_column_it] = 0;
}

Marble Board::move(Marble &marble, int dir) {
    const bool RED_FRONT = true;
    const bool BLUE_FRONT = false;
    Coordinate diff_in_direction = (marble.red - marble.blue) * d[dir];
    Coordinate red;
    Coordinate blue;
    Coordinate red_next;
    Coordinate blue_next;
    int front_in_direction = 0 < (diff_in_direction.x + diff_in_direction.y);
    if(front_in_direction == RED_FRONT) {
        red = marble.red;
        red_next = red + d[dir];
        while(field[red_next.y][red_next.x] != WALL && field[red.y][red.x] != HOLE) {
            red = red_next;
            red_next = red_next + d[dir];
        }
        blue = marble.blue;
        blue_next = blue + d[dir];
        while(field[blue_next.y][blue_next.x] != WALL && field[blue.y][blue.x] != HOLE && (blue_next != red || field[red.y][red.x] == HOLE)) {
            blue = blue_next;
            blue_next = blue_next + d[dir];
        }
    }
    else if(front_in_direction == BLUE_FRONT) {
        blue = marble.blue;
        blue_next = blue + d[dir];
        while(field[blue_next.y][blue_next.x] != WALL && field[blue.y][blue.x] != HOLE) {
            blue = blue_next;
            blue_next = blue_next + d[dir];
        }
        red = marble.red;
        red_next = red + d[dir];
        while(field[red_next.y][red_next.x] != WALL && field[red.y][red.x] != HOLE && (red_next != blue || field[blue.y][blue.x] == HOLE)) {
            red = red_next;
            red_next = red_next + d[dir];
        }
    }
    return Marble(red, blue);
}

int Board::bfs() {
    queue<Marble> marble_queue;
    marble_queue.push(marble_start);
    visited[marble_start.red.y][marble_start.red.x][marble_start.blue.y][marble_start.blue.x] = 1;
    while(!marble_queue.empty()) {
        Marble now = marble_queue.front();
        marble_queue.pop();
        int times_moved = visited[now.red.y][now.red.x][now.blue.y][now.blue.x];
        for(int dir = 0; dir < DIR; ++dir) {
            Marble next = move(now, dir);
            int &times_moved_next = visited[next.red.y][next.red.x][next.blue.y][next.blue.x];
            if(times_moved_next) {continue;}
            if(field[next.blue.y][next.blue.x] == HOLE) {continue;}
            if(field[next.red.y][next.red.x] == HOLE) {return times_moved;}
            times_moved_next = times_moved + 1;
            marble_queue.push(next);
        }
    }
    return -1;
}

int main() {
    Board board;
    board.read_field();
    board.intitiate_visited();
    int times_moved = board.bfs();
    const int max_times_moved = 10;
    cout << (max_times_moved < times_moved ? -1 : times_moved);
    return 0;
}