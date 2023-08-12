#include <string>
#include <vector>

using namespace std;

#define DIR 4

enum Direction {
    UP      = 0b0001,
    RIGHT   = 0b0010,
    DOWN    = 0b0100,
    LEFT    = 0b1000
};

struct Point {
    unsigned char installed;
    Point(): installed(0) {}
    template<typename... DirectionArgs>
    void install(DirectionArgs... direction) {
        installed |= (direction | ...);
    }
    template<typename... DirectionArgs>
    void uninstall(DirectionArgs... direction) {
        installed ^= installed & (direction | ...);
    }
    template<typename... DirectionArgs>
    bool is_installed(DirectionArgs... direction) {
        return installed & (direction | ...);
    }
};

struct Frame {
    size_t size;
    vector<vector<Point>> points;
    Frame(int size): size(static_cast<size_t>(size)), points(vector<vector<Point>>(size + 1, vector<Point>(size + 1, Point()))) {
        for(int it = 0; it <= size; ++it) {
            points[0][it].install(DOWN);
        }
    }
    bool check_valid(size_t x, size_t y, Direction direction) {
        if(direction == UP) {return points[y][x].is_installed(RIGHT | DOWN | LEFT);}
        if(direction == RIGHT) {return points[y][x].is_installed(DOWN) || points[y][x + 1].is_installed(DOWN) || (points[y][x].is_installed(LEFT) && points[y][x + 1].is_installed(RIGHT));}
        if(direction == DOWN) {return points[y - 1][x].is_installed(RIGHT | DOWN | LEFT);}
        if(direction == LEFT) {return points[y][x - 1].is_installed(DOWN) || points[y][x].is_installed(DOWN) || (points[y][x - 1].is_installed(LEFT) && points[y][x].is_installed(RIGHT));}
        return false;
    }
    void install(size_t x, size_t y, Direction direction) {
        if(!check_valid(x, y, direction)) {return;}
        points[y][x].install(direction);
        if(direction == UP) {points[y + 1][x].install(DOWN); return;}
        if(direction == RIGHT) {points[y][x + 1].install(LEFT); return;}
        if(direction == DOWN) {points[y - 1][x].install(UP); return;}
        if(direction == LEFT) {points[y][x - 1].install(RIGHT); return;}
    }
    void uninstall(size_t x, size_t y, Direction direction) {
        size_t dx = 0;
        size_t dy = 0;
        if(direction == UP) {dy = 1;}
        else if(direction == RIGHT) {dx = 1;}
        else if(direction == DOWN) {dy = -1;}
        else if(direction == LEFT) {dx = -1;}
        points[y][x].uninstall(direction);
        if(direction == UP) {points[y + dy][x + dx].uninstall(DOWN);}
        else if(direction == RIGHT) {points[y + dy][x + dx].uninstall(LEFT);}
        else if(direction == DOWN) {points[y + dy][x + dx].uninstall(UP);}
        else if(direction == LEFT) {points[y + dy][x + dx].uninstall(RIGHT);}
        bool valid_destruction = true;
        valid_destruction &= !points[y][x].is_installed(UP) || check_valid(x, y, UP);
        valid_destruction &= !points[y][x].is_installed(RIGHT) || (x == size ? true : check_valid(x, y, RIGHT));
        valid_destruction &= !points[y][x].is_installed(DOWN) || (y == 0 ? true : check_valid(x, y, DOWN));
        valid_destruction &= !points[y][x].is_installed(LEFT) || (x == 0 ? true : check_valid(x, y, LEFT));
        valid_destruction &= !points[y + dy][x + dx].is_installed(UP) || check_valid(x + dx, y + dy, UP);
        valid_destruction &= !points[y + dy][x + dx].is_installed(RIGHT) || (x + dx == size ? true : check_valid(x + dx, y + dy, RIGHT));
        valid_destruction &= !points[y + dy][x + dx].is_installed(DOWN) || (y + dy == 0 ? true : check_valid(x + dx, y + dy, DOWN));
        valid_destruction &= !points[y + dy][x + dx].is_installed(LEFT) || (x + dx == 0 ? true : check_valid(x + dx, y + dy, LEFT));
        if(valid_destruction) {return;}
        points[y][x].install(direction);
        if(direction == UP) {points[y + dy][x + dx].install(DOWN); return;}
        else if(direction == RIGHT) {points[y + dy][x + dx].install(LEFT); return;}
        else if(direction == DOWN) {points[y + dy][x + dx].install(UP); return;}
        else if(direction == LEFT) {points[y + dy][x + dx].install(RIGHT); return;}
    }
    void get_installed(vector<vector<int>> &installed) {
        for(int row_it = 0; row_it <= size; ++row_it) {
            for(int col_it = 0; col_it <= size; ++col_it) {
                if(points[col_it][row_it].is_installed(UP)) {
                    vector<int> row{row_it, col_it, 0};
                    installed.push_back(move(row));
                }
                if(points[col_it][row_it].is_installed(RIGHT)) {
                    vector<int> row{row_it, col_it, 1};
                    installed.push_back(move(row));
                }
            }
        }
    }
};

#define X_ENTRY 0
#define Y_ENTRY 1
#define KIND_ENTRY 2
#define INSTALL_ENTRY 3
#define COLUMN 0
#define BEAM 1
#define UNINSTALL 0
#define INSTALL 1

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    Frame frame{n};
    for(vector<int> &command: build_frame) {
        Direction direction;
        if(command[KIND_ENTRY] == COLUMN) {direction = UP;}
        else if(command[KIND_ENTRY] == BEAM) {direction = RIGHT;}
        if(command[INSTALL_ENTRY] == INSTALL) {frame.install(command[X_ENTRY], command[Y_ENTRY], direction);}
        else if(command[INSTALL_ENTRY] == UNINSTALL) {frame.uninstall(command[X_ENTRY], command[Y_ENTRY], direction);}
    }
    frame.get_installed(answer);
    return answer;
}