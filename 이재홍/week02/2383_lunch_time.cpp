#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define DIR 4
#define N_MAX 10
#define MAXPOP 3
using namespace std;

struct Coordinate {
    int x;
    int y;
};

struct Stair {
    int len; // length of stair
    queue<int> q; // people on stair
    int wait; // people waiting to use stair
    int pop; // number of total person on stair
    vector<int> dist; // distance of people who want to use this stair
};

vector<Coordinate> pp; // person position vector
Coordinate sp[2]; // stair position array
vector<int> dist[2]; // distance between person and stair
Stair stair[2]; // stair object to process people on stair
int min_time;

int MAP[N_MAX][N_MAX];

int get_dist(const Coordinate& p1, const Coordinate& p2) {
    int y_diff = (p1.y < p2.y) ? (p2.y - p1.y) : (p1.y - p2.y);
    int x_diff = (p1.x < p2.x) ? (p2.x - p1.x) : (p1.x - p2.x);
    return y_diff + x_diff;
}

int lunch_time(int idx) {
    vector<int> w = vector<int>(stair[idx].dist);
    sort(w.begin(), w.end());
    int w_idx = 0;
    int w_len = w.size();
    int time = 0;
    int s_len = stair[idx].len;
    stair[idx].q = queue<int>();
    for(int i = 0; i < s_len; i++) { // initialize stair queue
        stair[idx].q.push(0);
    }
    while(stair[idx].pop || w_idx != w_len) { // update waiting line
        ++time;
        while(w_idx != w_len && time == w[w_idx]) {
            ++w_idx;
            stair[idx].wait += 1;
        }
        int exit_pop = stair[idx].q.front(); // update stair exiting people
        stair[idx].q.pop();
        stair[idx].pop -= exit_pop;
        int enter_pop = min(MAXPOP - stair[idx].pop, stair[idx].wait); // update stair entering people
        stair[idx].wait -= enter_pop;
        stair[idx].pop += enter_pop;
        stair[idx].q.push(enter_pop);
    }
    return time;
}

void dfs(int now = 0) {
    // conditnion check
    if(pp.size() <= now) {
        if(!min_time) 
            {min_time = max(lunch_time(0), lunch_time(1));}
        else
            {min_time = min(min_time, max(lunch_time(0), lunch_time(1)));}
        return;
    }
    // backtracking
    // process
    stair[0].dist.push_back(dist[0][now]);
    // recusive
    dfs(now + 1);
    // unprocess
    stair[0].dist.pop_back();
    // process
    stair[1].dist.push_back(dist[1][now]);
    // recusive
    dfs(now + 1);
    // unprocess
    stair[1].dist.pop_back();
    // return minimum
}

int main() {
    // read 1 int
    int T;
    cin >> T;
    // run testcase loop
    for(int testcase = 1; testcase <= T; ++testcase) {
        // prepare global variable
        pp = vector<Coordinate>();
        dist[0] = vector<int>();
        dist[1] = vector<int>();
        stair[0] = Stair();
        stair[1] = Stair();
        min_time = 0;
        // read 1 int
        int N;
        cin >> N;
        // read map
        int stair_idx = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                cin >> MAP[i][j];
                if(MAP[i][j] == 1) // person found
                    {pp.push_back({j, i});}
                else if(MAP[i][j]) { // stair found
                    sp[stair_idx] = {j, i};
                    stair[stair_idx].len = MAP[i][j];
                    stair_idx++;
                }
            }
        }
        // get person-stair distance vector
        int p_len = pp.size();
        for(int i = 0; i < p_len; i++) {
            dist[0].push_back(get_dist(pp[i], sp[0]));
            dist[1].push_back(get_dist(pp[i], sp[1]));
        }
        // run stair usage combination
        dfs();
        // print result
        cout << "#" << testcase << " " << (min_time + 1) << "\n";
    }
    return 0;
}