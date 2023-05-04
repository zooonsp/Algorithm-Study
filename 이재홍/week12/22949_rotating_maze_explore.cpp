#include <iostream>
#include <vector>
#include <queue>
#include <string>
#define DIR 5
using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &rhs) const;
    Coordinate operator-(const Coordinate &rhs) const;
    Coordinate operator*(const int multiplier) const;
    bool operator==(const Coordinate &rhs) const;
    bool operator!=(const Coordinate &rhs) const;
    Coordinate rotate(int size, int rotation);
};

Coordinate Coordinate::operator+(const Coordinate &rhs) const {
    return {x + rhs.x, y + rhs.y};
}

Coordinate Coordinate::operator-(const Coordinate &rhs) const {
    return {x - rhs.x, y - rhs.y};
}

Coordinate Coordinate::operator*(const int multiplier) const {
    return {x * multiplier, y * multiplier};
}

bool Coordinate::operator==(const Coordinate &rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Coordinate::operator!=(const Coordinate &rhs) const {
    return x != rhs.x || y != rhs.y;
}

Coordinate Coordinate::rotate(int size, int rotation) {
    const int originx[4] = {0, size - 1, size - 1, 0};
    const int originy[4] = {0, 0, size - 1, size - 1};
    const int dx[4] = { x,-y,-x, y};
    const int dy[4] = { y, x,-y,-x};
    return {originx[rotation] + dx[rotation], originy[rotation] + dy[rotation]};
}

Coordinate d[DIR] = {{-1, 0}, { 0,-1}, { 1, 0}, { 0, 1}, { 0, 0}};

struct Section {
    int size;
    vector<vector<vector<int>>> field;
    Section(int size_, int layer);
    static Coordinate out(Coordinate coordinate, int size);
};

Section::Section(int size_, int layer):
    size(size_),
    field(vector<vector<vector<int>>>(layer, vector<vector<int>>(size_, vector<int>(size_))))
{}

Coordinate Section::out(Coordinate coordinate, int size) {
    Coordinate next_section = {0, 0};
    next_section.x = coordinate.x < 0 ? -1 : (size <= coordinate.x ? 1 : 0);
    next_section.y = coordinate.y < 0 ? -1 : (size <= coordinate.y ? 1 : 0);
    return next_section;
}

struct RotatingMaze {
    int maze_size;
    int section_size;
    vector<vector<Section>> field;
    vector<vector<Section>> visited;
    RotatingMaze(int total_size, int section_size);
    static bool out(Coordinate section, int size);
};

RotatingMaze::RotatingMaze(int total_size, int section_size):
    maze_size(total_size),
    section_size(section_size),
    field(vector<vector<Section>>(section_size, vector<Section>(section_size, Section(total_size / section_size, 1)))),
    visited(vector<vector<Section>>(section_size, vector<Section>(section_size, Section(total_size / section_size, 4))))
{}

bool RotatingMaze::out(Coordinate section, int size) {
    return section.x < 0 | size <= section.x | section.y < 0 | size <= section.y;
}

struct Position {
    Coordinate section;
    Coordinate position_on_map;
    int rotation;
    Position();
    Position(int section_x, int section_y, int field_x, int field_y, int rotation_);
    bool operator==(const Position &rhs) const;
};

Position::Position():
    section(Coordinate()),
    position_on_map(Coordinate()),
    rotation(0)
{}

Position::Position(int section_x, int section_y, int field_x, int field_y, int rotation_):
    section({section_x, section_y}),
    position_on_map({field_x, field_y}),
    rotation(rotation_)
{}


bool Position::operator==(const Position &rhs) const {
    return section == rhs.section && position_on_map == rhs.position_on_map;
}

void read_map(RotatingMaze &maze, Position &start, Position &end) {
    const int length = maze.maze_size / maze.section_size;
    const int layer = 0;
    const int WALL = 1;
    const int PATH = 0;
    const int WALL_CHAR = '#';
    const int PATH_CHAR = '.';
    const int START_CHAR = 'S';
    const int END_CHAR = 'E';
    const int NO_ROTATION = 0;
    for(int section_row = 0; section_row < maze.section_size; ++section_row) {
        for(int row_it = 0; row_it < length; ++row_it) {
            string row_string;
            cin >> row_string;
            for(int section_column = 0; section_column < maze.section_size; ++section_column) {
                Section &section = maze.field[section_row][section_column];
                vector<vector<int>> &field = section.field[layer];
                for(int column_it = 0; column_it < length; ++column_it) {
                    int string_it = section_column * length + column_it;
                    if(row_string[string_it] == WALL_CHAR) {field[row_it][column_it] = WALL;}
                    else {
                        field[row_it][column_it] = PATH;
                        if(row_string[string_it] == START_CHAR) {start = Position(section_column, section_row, column_it, row_it, NO_ROTATION);}
                        else if(row_string[string_it] == END_CHAR) {end = Position(section_column, section_row, column_it, row_it, NO_ROTATION);}
                    }
                }
            }
        }
    }
}

int bfs(RotatingMaze &maze, Position &start, Position &end) {
    const int length = maze.maze_size / maze.section_size;
    const int FIELD_LAYER = 0;
    queue<Position> q;
    q.push(start);
    maze.visited[start.section.y][start.section.x].field[start.rotation][start.position_on_map.y][start.position_on_map.x] = 1;
    const Coordinate SECTION_NO_MOVE({0, 0});
    while(!q.empty()) {
        Position now = q.front();
        q.pop();
        for(int dir = 0; dir < DIR; ++dir) {
            Position next = now;
            next.position_on_map = next.position_on_map + d[dir];
            Coordinate rotated = next.position_on_map.rotate(length, next.rotation);
            Coordinate section_diff = Section::out(rotated, length);
            if(section_diff != SECTION_NO_MOVE) {
                next.section = next.section + section_diff;
                if(RotatingMaze::out(next.section, maze.section_size)) {continue;}
                next.position_on_map = rotated - section_diff * length;
                next.rotation = 0;
            }
            next.rotation = (next.rotation + 1) % 4;
            if(maze.field[next.section.y][next.section.x].field[FIELD_LAYER][next.position_on_map.y][next.position_on_map.x]) {continue;}
            if(maze.visited[next.section.y][next.section.x].field[next.rotation][next.position_on_map.y][next.position_on_map.x]) {continue;}
            if(next == end) {return maze.visited[now.section.y][now.section.x].field[now.rotation][now.position_on_map.y][now.position_on_map.x];}
            maze.visited[next.section.y][next.section.x].field[next.rotation][next.position_on_map.y][next.position_on_map.x] = maze.visited[now.section.y][now.section.x].field[now.rotation][now.position_on_map.y][now.position_on_map.x] + 1;
            q.push(next);
        }
    }
    return -1;
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int maze_size;
    cin >> maze_size;
    const int section_size = maze_size;
    maze_size *= 4;
    RotatingMaze maze(maze_size, section_size);
    Position start, end;
    read_map(maze, start, end);
    cout << bfs(maze, start, end);
    return 0;
}