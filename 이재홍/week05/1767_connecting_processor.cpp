#include <iostream>
#include <algorithm>
#define NMAX 12
#define COREMAX 12
#define DIR 4
#define BIGNUM 87654321
using namespace std;
// get available processor info at edge of field
// integrate available connection info to processor
// sort processor info by available conections
// (get rid of redundant stacking: processors with 1 available connections should be routed first)
// dfs through all available path

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &pos) {return {x + pos.x, y + pos.y};}
    Coordinate &operator+=(const Coordinate &pos) {x += pos.x; y += pos.y; return *this;}
};

struct Processor {
    Coordinate pos;
    int con[DIR]; // available connections
    int con_num; // total number of available connections
    bool operator<(const Processor &prcr) {return con_num < prcr.con_num;}
};

Coordinate d[DIR] = {{ 0,-1}, { 0, 1}, {-1, 0},{ 1, 0}};

int N;
int field[NMAX][NMAX];
Processor p[COREMAX];
int p_index;
int min_conn_len;
int max_connected_core;
int conn[DIR][NMAX]; // top, bottom, left, right
void (*conn_update[4])(const Processor &) = { // check if conn array should be updated
    [](const Processor &prcr) -> void {if(prcr.pos.y < conn[0][prcr.pos.x]) {conn[0][prcr.pos.x] = prcr.pos.y;}},
    [](const Processor &prcr) -> void {if(prcr.pos.y > conn[1][prcr.pos.x]) {conn[1][prcr.pos.x] = prcr.pos.y;}},
    [](const Processor &prcr) -> void {if(prcr.pos.x < conn[2][prcr.pos.y]) {conn[2][prcr.pos.y] = prcr.pos.x;}},
    [](const Processor &prcr) -> void {if(prcr.pos.x > conn[3][prcr.pos.y]) {conn[3][prcr.pos.y] = prcr.pos.x;}}
};
void (*prcr_update[4])(Processor &) = { // update processor info
    [](Processor &prcr) -> void {if(prcr.pos.y == conn[0][prcr.pos.x]) {prcr.con[0] = 1; prcr.con_num += 1;}},
    [](Processor &prcr) -> void {if(prcr.pos.y == conn[1][prcr.pos.x]) {prcr.con[1] = 1; prcr.con_num += 1;}},
    [](Processor &prcr) -> void {if(prcr.pos.x == conn[2][prcr.pos.y]) {prcr.con[2] = 1; prcr.con_num += 1;}},
    [](Processor &prcr) -> void {if(prcr.pos.x == conn[3][prcr.pos.y]) {prcr.con[3] = 1; prcr.con_num += 1;}}
};
bool is_edge(const Processor &prcr) {return prcr.pos.x == 0 || prcr.pos.x == (N - 1) || prcr.pos.y == 0 || prcr.pos.y == (N - 1);}
bool is_out(const Coordinate &pos) {return pos.x < 0 || pos.y < 0 || N <= pos.x || N <= pos.y;}

void read_field() {
    // read field, find processor
    p_index = 0;
    for(int i = 0; i < N; ++i) {
        int flag = 1;
        for(int j = 0; j < N; ++j) {
            cin >> field[i][j];
            if(field[i][j]) {p[p_index] = {{j, i}, {0, 0, 0, 0}, 0}; ++p_index;}
        }
    }
    // init connection info
    int write_val = N - 1;
    int invert_val = N - 1;
    for(int i = 0; i < DIR; ++i) {
        for(int j = 0; j < N; ++j) {conn[i][j] = write_val;}
        write_val ^= invert_val;
    }
    // update connection info to conn array
    for(int i = 0; i < p_index; ++i) {
        for(int j = 0; j < DIR; ++j) {
            conn_update[j](p[i]);
        }
    }
    // update connection info to processor
    for(int i = 0; i < p_index; ++i) {
        if(is_edge(p[i])) {continue;}
        for(int j = 0; j < DIR; ++j) {
            prcr_update[j](p[i]);
        }
    }
    // sort processors
    sort(p, p + p_index);
    return;
}

void dfs(int now, int conn_len, int conn_core) {
    // check condition
    if(p_index <= now) {
        if(max_connected_core < conn_core) {max_connected_core = conn_core; min_conn_len = conn_len;}
        else if(max_connected_core == conn_core) {min_conn_len = min_conn_len < conn_len ? min_conn_len : conn_len;}
        return;
    }
    int total_core_unused = p_index - max_connected_core;
    int now_core_unused = now - conn_core;
    if(total_core_unused < now_core_unused) {return;} // less core than max core number
    if(total_core_unused == now_core_unused && min_conn_len <= conn_len) {return;} // over minimum length with same or less core used
    // backtracking
    for(int i = 0; i < DIR; ++i) {
        // pruning
        if(!(p[now].con[i])) {continue;}
        Coordinate conn_pos = p[now].pos + d[i]; // check if there is line crossing
        while(!field[conn_pos.y][conn_pos.x] && !is_out(conn_pos)) {conn_pos += d[i];}
        if(!is_out(conn_pos)) {continue;}
        // process
        int add_len = 0; // measure contruct length
        conn_pos = p[now].pos + d[i]; // construct connection
        while(!field[conn_pos.y][conn_pos.x] && !is_out(conn_pos)) {field[conn_pos.y][conn_pos.x] = 1; conn_pos += d[i]; ++add_len;}
        // recursive
        dfs(now + 1, conn_len + add_len, conn_core + 1);
        // unprocess
        conn_pos = p[now].pos + d[i]; // destruct connection
        while(!is_out(conn_pos)) {field[conn_pos.y][conn_pos.x] = 0; conn_pos += d[i];}
    }
    // not connected
    dfs(now + 1, conn_len, conn_core);
    return;
}

int main() {
    // read 1 int
    int T;
    cin >> T;
    // run testcase loop
    for(int testcase = 1; testcase <= T; ++testcase) {
        // read 1 int
        cin >> N;
        // read field
        read_field();
        // initialte minimum connection length, maximum connected core
        min_conn_len = BIGNUM;
        max_connected_core = 0;
        // pass cores at edge
        int i = 0;
        while(i < p_index && !(p[i].con_num)) {++i;}
        // run dfs
        dfs(i, 0, i);
        // print minimum connection length
        cout << '#' << testcase << ' ' << min_conn_len << '\n';
    }
    return 0;
}