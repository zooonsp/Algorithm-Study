#include <iostream>
#include <queue>
#define NMMAX 50
#define MARGIN 150
#define DIR 4
using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(Coordinate p) {return {x + p.x, y + p.y};}
};

struct Cell {
    Coordinate p;
    int life;
    int start;
};

Coordinate d[DIR] = {
    {-1, 0},
    { 0,-1},
    { 1, 0},
    { 0, 1}
};

int N, M, K;
int field[MARGIN + NMMAX + MARGIN][MARGIN + NMMAX + MARGIN]; // 0: not writen, negative: dead and alive, positive: next loop alive
queue<Cell> liveCell;
queue<Coordinate> nextCell;

void init_field() {
    int h, w;
    h = w = MARGIN + NMMAX + MARGIN;
    for(int i = 0; i < h; ++i) {for(int j = 0; j < w; ++j) {field[i][j] = 0;}}
}

void read_field() {
    // init queue
    liveCell = queue<Cell>();
    nextCell = queue<Coordinate>();
    // read 3 int
    cin >> N >> M >> K;
    // read N*M int
    N += MARGIN;
    M += MARGIN;
    for(int i = MARGIN; i < N; ++i) {
        for(int j = MARGIN; j < M; ++j) {
            cin >> field[i][j];
            if(field[i][j]) {liveCell.push({{j, i}, field[i][j], 0});}
            field[i][j] = -field[i][j];
        }
    }
}

void run_loop(int n) {
    // run loop for n times
    for(int loop = 1; loop < n; ++loop) {
        // get size of live cell
        int live_cells = liveCell.size();

        // iterate through live cells
        for(int it = 0; it < live_cells; ++it) {
            // pop front of queue
            Cell now = liveCell.front();
            liveCell.pop();
            int awake_time = now.start + now.life;
            int terminate_time = now.start + (now.life << 1) - 1;

            // process adjacent cells
            if(awake_time == loop) { // awake cell
                // backtracking
                for(int dir = 0; dir < DIR; ++dir) {
                    Coordinate next_p = now.p + d[dir];
                    // pruning
                    int field_val = field[next_p.y][next_p.x];
                    if(field_val < 0) {continue;} // division completed cell
                    else if(!field_val) { // not visited cell
                        field[next_p.y][next_p.x] = now.life;
                        nextCell.push(next_p);
                    }
                    else if(field_val < now.life) { // conflict cell
                        field[next_p.y][next_p.x] = now.life;
                    }
                }
            }

            // process this cell
            if(terminate_time == loop) {continue;} // kill cell
            else {liveCell.push(now); continue;} // maintain cell
        }

        // process next cells, add to live cell queue
        while(nextCell.size()) {
            // pop front of queue
            Coordinate now = nextCell.front();
            nextCell.pop();
            // push into live cell queue
            liveCell.push({now, field[now.y][now.x], loop + 1});
            // update field
            field[now.y][now.x] = -field[now.y][now.x];
        }
    }
    return;
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    // read 1 int
    int T;
    cin >> T;
    // run testcase loop
    for(int testcase = 1; testcase <= T; ++testcase) {
        init_field();
        read_field();
        run_loop(K);
        cout << '#' << testcase << ' ' << liveCell.size() << '\n';
    }
    return 0;
}