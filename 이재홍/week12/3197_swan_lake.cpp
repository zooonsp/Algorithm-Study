#include <iostream>
#include <queue>
#define DIR 4
#define DIR_HALF 2
using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &rhs) const {return {x + rhs.x, y + rhs.y};}
    bool operator==(const Coordinate &rhs) const {return x == rhs.x && y == rhs.y;}
    bool operator!=(const Coordinate &rhs) const {return x != rhs.x || y != rhs.y;}
};

Coordinate d[DIR] = {{-1, 0}, { 0,-1}, { 1, 0}, { 0, 1}};

struct Lake {
    static const int MAX_R = 1500;
    static const int MAX_C = 1500;
    static const int WATER = '.';
    static const int ICE = 'X';
    static const int SWAN = 'L';

    int R, C;
    int field_map[MAX_R][MAX_C];

    int days_passed;
    int field_queued[MAX_R][MAX_C];
    queue<Coordinate> q;

    Coordinate u_set[MAX_R][MAX_C];
    void u_init();
    Coordinate u_find(Coordinate &pos);
    void u_union(Coordinate &lhs, Coordinate &rhs);

    Coordinate swan[2];
    bool out(Coordinate &pos);
    void read_lake();
    void run_time();
};

void Lake::u_init() {
    for(int R_it = 0; R_it < R; ++R_it) {
        for(int C_it = 0; C_it < C; ++C_it) {
            u_set[R_it][C_it] = {C_it, R_it};
            field_queued[R_it][C_it] = 0;
        }
    }
}

Coordinate Lake::u_find(Coordinate &pos) {
    if(pos != u_set[pos.y][pos.x]) {return u_set[pos.y][pos.x] = u_find(u_set[pos.y][pos.x]);}
    return pos;
}

void Lake::u_union(Coordinate &lhs, Coordinate &rhs) {
    Coordinate s_lhs = u_find(lhs);
    Coordinate s_rhs = u_find(rhs);
    if(s_lhs == s_rhs) {return;}
    u_set[s_rhs.y][s_rhs.x] = s_lhs;
    return;
}

bool Lake::out(Coordinate &pos) {
    return pos.x < 0 || pos.y < 0 || C <= pos.x || R <= pos.y;
}

void Lake::read_lake() {
    cin >> R >> C;
    u_init();
    int swan_count = 0;
    for(int row = 0; row < R; ++row) {
        string row_string;
        cin >> row_string;
        for(int col = 0; col < C; ++col) {
            field_map[row][col] = row_string[col];
            if(field_map[row][col] == WATER) {
                Coordinate now = Coordinate{col, row};
                for(int dir = 0; dir < DIR_HALF; ++dir) {
                    Coordinate next = now + d[dir];
                    if(out(next)) {continue;}
                    if(field_map[next.y][next.x] == WATER || field_map[next.y][next.x] == SWAN) {
                        u_union(next, now);
                    }
                    else if(field_map[next.y][next.x] == ICE) {
                        if(field_queued[next.y][next.x]) {continue;}
                        q.push(next);
                        field_queued[next.y][next.x] = 1;
                    }
                }
            }
            else if(field_map[row][col] == ICE) {
                if(field_queued[row][col]) {continue;}
                Coordinate now = Coordinate{col, row};
                for(int dir = 0; dir < DIR_HALF; ++dir) {
                    Coordinate next = now + d[dir];
                    if(out(next)) {continue;}
                    if(field_map[next.y][next.x] == WATER || field_map[next.y][next.x] == SWAN) {
                        q.push(now);
                        field_queued[now.y][now.x] = 1;
                        break;
                    }
                }
            }
            else if(field_map[row][col] == SWAN) {
                swan[swan_count] = {col, row};
                ++swan_count;
                Coordinate now = Coordinate{col, row};
                for(int dir = 0; dir < DIR_HALF; ++dir) {
                    Coordinate next = now + d[dir];
                    if(out(next)) {continue;}
                    if(field_map[next.y][next.x] == WATER || field_map[next.y][next.x] == SWAN) {
                        u_union(next, now);
                    }
                    else if(field_map[next.y][next.x] == ICE) {
                        if(field_queued[next.y][next.x]) {continue;}
                        q.push(next);
                        field_queued[next.y][next.x] = 1;
                    }
                }
            }
        }
    }
};

void Lake::run_time() {
    days_passed = 0;
    while(u_find(swan[0]) != u_find(swan[1])) {
        for(int q_size = q.size(); q_size; --q_size) {
            Coordinate now = q.front();
            q.pop();
            field_map[now.y][now.x] = WATER;
            for(int dir = 0; dir < DIR; ++dir) {
                Coordinate next = now + d[dir];
                if(out(next)) {continue;}
                if(field_map[next.y][next.x] == ICE) {
                    if(field_queued[next.y][next.x]) {continue;}
                    q.push(next);
                    field_queued[next.y][next.x] = 1;
                }
                else {u_union(next, now);}
            }
        }
        ++days_passed;
    }
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    Lake lake;
    lake.read_lake();
    lake.run_time();
    cout << lake.days_passed;
    return 0;
}