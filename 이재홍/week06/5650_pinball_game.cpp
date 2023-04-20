#include <iostream>
#define DIR 4
using namespace std;
// use dfs
// use dynamic programming
// fill all course score if possible
// if course score is available, use it

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(Coordinate p) {
        return {x + p.x, y + p.y};
    }
    bool operator==(Coordinate p) {
        return x == p.x && y == p.y;
    }
};

struct Block {
    int dir[DIR];
    int reflect[DIR];
    Coordinate worm[2];
};

struct Score {
    int score;
    int end_type; // 0: unvisited, 1: reflect, 2: back to origin, -1: blackhole
};

Coordinate d[DIR] = {{0,-1},{1,0},{0,1},{-1,0}};

Block block[11] {
    {{ 0, 1, 2, 3}, {0,0,0,0}, {{-1,-1}, {-1,-1}}},
    {{ 2, 3, 1, 0}, {1,1,0,0}, {{-1,-1}, {-1,-1}}},
    {{ 1, 3, 0, 2}, {0,1,1,0}, {{-1,-1}, {-1,-1}}},
    {{ 3, 2, 0, 1}, {0,0,1,1}, {{-1,-1}, {-1,-1}}},
    {{ 2, 0, 3, 1}, {1,0,0,1}, {{-1,-1}, {-1,-1}}},
    {{ 2, 3, 0, 1}, {1,1,1,1}, {{-1,-1}, {-1,-1}}},
    {{-1,-1,-1,-1}, {0,0,0,0}, {{-1,-1}, {-1,-1}}},
    {{-1,-1,-1,-1}, {0,0,0,0}, {{-1,-1}, {-1,-1}}},
    {{-1,-1,-1,-1}, {0,0,0,0}, {{-1,-1}, {-1,-1}}},
    {{-1,-1,-1,-1}, {0,0,0,0}, {{-1,-1}, {-1,-1}}},
    {{-1,-1,-1,-1}, {0,0,0,0}, {{-1,-1}, {-1,-1}}}
};

int N;
int field[102][102];
Score scoreboard[102][102][DIR];

// parameters for dfs
int last_score; // score of initial dfs coordinate
int max_score; // calculate after all dfs recursive, use last_score
int end_type; // 1: reflect, 2: back to origin (loop), 3: back to origin (no loop), -1: blackhole

void dfs(Coordinate &origin, Coordinate now, int &origin_dir, int dir, int score) {
    // condition check
    if(end_type) { // reflect or blackhole
        return;
    }
    // backtracking
    Coordinate next = now + d[dir];
    int next_dir = dir;
    int next_score = score;
    // pruning
    if(origin == next) { // back to origin
        if(origin_dir == dir) { // loop
            last_score = score;
            end_type = 2;
        }
        else { // no loop
            scoreboard[origin.y][origin.x][origin_dir].score = score;
            scoreboard[origin.y][origin.x][origin_dir].end_type = 3;
            end_type = 3;
        }
    }
    // process
    int field_val = field[next.y][next.x];
    if(6 <= field_val && field_val <= 10) { // block encounter: 
        next = (next == block[field_val].worm[0]) ? block[field_val].worm[1] : block[field_val].worm[0]; // teleport through wormhole
    }
    else if(0 < field_val) { // block encounter: bend, reflect
        if(block[field_val].reflect[dir]) { // end travel: reflect and go back to origin
            last_score = (score << 1) ^ 1; // score * 2 + 1
            end_type = 1;
        }
        else { // bend course
            next_dir = block[field_val].dir[dir];
            next_score += 1;
        }
    }
    else if(0 == field_val) { // blank space
        if(scoreboard[next.y][next.x][dir].end_type == 1) { // end travel: meet precalculated score
            last_score = scoreboard[next.y][next.x][dir].score + (score << 1);
            end_type = 1;
        }
        // else if(scoreboard[next.y][next.x][dir].end_type == 2) { // end travel: meet precalculated score
        //     last_score = scoreboard[next.y][next.x][dir].score;
        //     end_type = 2;
        // }
        else if(scoreboard[next.y][next.x][dir].end_type == -1) { // end travel: meet precalculated score
            last_score = scoreboard[next.y][next.x][dir].score + score;
            end_type = -1;
        }
    }
    else { // block encounter: blackhole
        last_score = score;
        end_type = -1;
    }
    // recursive
        dfs(origin, next, origin_dir, next_dir, next_score);
    // unprocess
    // dynamic programing
    if(!field[now.y][now.x]) {
        if(end_type == 1) { // reflect
            scoreboard[now.y][now.x][dir].score = last_score - (score << 1);
            scoreboard[now.y][now.x][dir].end_type = 1;
        }
        else if(end_type == 2) { // back to origin (loop): fill opposite way too
            scoreboard[now.y][now.x][dir].score = last_score;
            scoreboard[now.y][now.x][dir].end_type = 2;
            scoreboard[now.y][now.x][dir ^ 2].score = last_score;
            scoreboard[now.y][now.x][dir ^ 2].end_type = 2;
        }
        else if(end_type == -1) { // blackhole
            scoreboard[now.y][now.x][dir].score = last_score - score;
            scoreboard[now.y][now.x][dir].end_type = -1;
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
        // read 1 int
        cin >> N;
        // prepare field
        for(int i = 1; i <= N; ++i) {
            field[0][i] = 5;
            field[i][0] = 5;
            field[N + 1][i] = 5;
            field[i][N + 1] = 5;
        }
        // read field
        int wormIdx[5] = {0,};
        for(int i = 1; i <= N; ++i) {
            for(int j = 1; j <= N; ++j) {
                cin >> field[i][j];
                if(6 <= field[i][j] && field[i][j] <= 10) {
                    block[field[i][j]].worm[wormIdx[field[i][j] - 6]] = Coordinate({j, i});
                    wormIdx[field[i][j] - 6] += 1;
                }
            }
        }
        // prepare scoreboard array
        for(int i = 1; i <= N; ++i) {
            for(int j = 1; j <= N; ++j) {
                for(int k = 0; k < DIR; ++k) {
                    scoreboard[i][j][k].end_type = 0;
                }
            }
        }
        // run track
        max_score = 0;
        for(int i = 1; i <= N; ++i) {
            for(int j = 1; j <= N; ++j) {
                if(field[i][j]) continue;
                Coordinate start({j, i});
                for(int k = 0; k < DIR; ++k) {
                    if(scoreboard[i][j][k].end_type) continue;
                    end_type = 0;
                    dfs(start, start, k, k, 0);
                    // find max score
                    max_score = max_score < scoreboard[i][j][k].score ? scoreboard[i][j][k].score : max_score;
                }
            }
        }
        // print result
        cout << '#' << testcase << ' ' << max_score << '\n';
    }
    return 0;
}