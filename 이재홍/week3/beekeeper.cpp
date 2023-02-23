#include <iostream>
#include <vector>
#include <algorithm>
#define DIR 6
#define MAXLV 4
#define LEN 4
#define LEN2 7
#define HMAX 15
#define WMAX 15
using namespace std;

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(Coordinate p)
        {return {x + p.x, y + p.y};}
    Coordinate operator-(Coordinate p)
        {return {x - p.x, y - p.y};}
    bool operator<(const Coordinate& p)
        {return y < p.y || (y == p.y && x < p.x);}
};

int H, W;
vector<vector<Coordinate>> pattern[2];
vector<Coordinate> reachable;
vector<int> reachable_level;
vector<Coordinate> path;
int visited[LEN2][LEN] = {0,};
int hive[HMAX][WMAX];

// declare direct array
Coordinate d[2][DIR] = {
    {{-1,-1},{ 0,-1},{ 1,-1},{ 1, 0},{ 0, 1},{-1, 0}},
    {{-1, 0},{ 0,-1},{ 1, 0},{ 1, 1},{ 0, 1},{-1, 1}}
};

bool dfs_out_of_bound(const Coordinate& p) {
    return p.x < 0 || p.y < 0 || LEN <= p.x || LEN2 <= p.y;
}

void dfs(int level, int now_idx) {
    // condition check
    Coordinate now = reachable[now_idx];
    if(MAXLV <= level) {
        pattern[0].push_back(path);
        sort(pattern[0].back().begin(), pattern[0].back().end());
        return;
    }
    // add reachable nodes
    reachable_level[level] = reachable_level[level - 1];
    for(int i = 0; i < DIR; ++i) {
        Coordinate next = now + d[now.x % 2][i];
        if(dfs_out_of_bound(next)) {continue;}
        if(visited[next.y][next.x]) {continue;}
        int ableFlag = 1;
        for(int j = 0; j < DIR; ++j) {
            if(j == (i + DIR / 2) % DIR) {continue;}
            Coordinate next_next = next + d[next.x % 2][j];
            if(visited[next_next.y][next_next.x] == 2) {
                ableFlag = 0;
                break;}
        }
        if(ableFlag) {
            reachable[reachable_level[level]] = next;
            ++reachable_level[level];
        }
    }
    // backtracking
    for(int i = now_idx + 1; i < reachable_level[level]; ++i) {
        Coordinate next = reachable[i];
        // process
        visited[next.y][next.x] = 2;
        path.push_back(next);
        // recursive
        dfs(level + 1, i);
        // unprocess
        visited[next.y][next.x] = 0;
        path.pop_back();
    }
    return;
}

// make all tile pattern
void make_pattern() {
    for(int i = 0; i < LEN - 1; ++i)
        {visited[i][0] = 1;}
        visited[LEN - 1][0] = 2;
    reachable = vector<Coordinate>(MAXLV * DIR);
    reachable[0] = {0, LEN - 1};
    reachable_level = vector<int>(MAXLV);
    reachable_level[0] = 1;
    path.push_back({0, LEN - 1});
    // make pattern for even column
    dfs(1, 0);
    vector<vector<Coordinate>>::iterator it = pattern[0].begin();
    vector<vector<Coordinate>>::iterator it_end = pattern[0].end();
    for(; it != it_end; ++it) {
        vector<Coordinate>::iterator it_it = it->begin();
        vector<Coordinate>::iterator it_it_end = it->end();
        for(; it_it != it_it_end; ++it_it)
            {*it_it = *it_it - Coordinate({0, LEN - 1});
        }
    }
    // make pattern for odd column
    pattern[1] = vector<vector<Coordinate>>(pattern[0]);
    it = pattern[1].begin();
    it_end = pattern[1].end();
    for(; it != it_end; ++it) {
        vector<Coordinate>::iterator it_it = it->begin();
        vector<Coordinate>::iterator it_it_end = it->end();
        for(; it_it != it_it_end; ++it_it) {
            if(it_it->x % 2)
                {*it_it = *it_it + Coordinate({0, 1});
            }
        }
    }
}

bool out_of_bound(const Coordinate& p) {
    return p.x < 0 || p.y < 0 || W <= p.x || H <= p.y;
}

int get_value(Coordinate p) {
    vector<vector<Coordinate>>::iterator it = pattern[p.x % 2].begin();
    vector<vector<Coordinate>>::iterator it_end = pattern[p.x % 2].end();
    int max_value = 0;
    for(; it != it_end; ++it) {
        int value = 0;
        int valid = 1;
        vector<Coordinate>::iterator it_it = it->begin();
        vector<Coordinate>::iterator it_it_end = it->end();
        for(; it_it != it_it_end; ++it_it) {
            Coordinate now = p + *it_it;
            if(out_of_bound(now)) {valid = 0; break;}
            value += hive[now.y][now.x];
        }
        if(valid) {max_value = max_value < value ? value : max_value;}
    }
    return max_value;
}

int main() {
    // make pattern
    make_pattern();
    // read 2 int
    cin >> H >> W;
    // read H*W array
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            cin >> hive[i][j];
        }
    }
    // sweep pattern for each hive cell
    int max_value = 0;
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            int value = get_value({j, i});
            max_value = max_value < value ? value : max_value;
        }
    }
    // print max value
    cout << max_value;
}