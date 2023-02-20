#include <iostream>
#include <algorithm>
#define N_MAX 16
using namespace std;
// fold s diagonal to reduce calculation
// s[i][j] = s[i][j] + s[j][i] (i < j)
// when adding s values, calculate both sum at once

int N;
int s[N_MAX][N_MAX];
int team[N_MAX]; // 0: team 0, 1: team 1
int team_avail[2]; // available team capacity
int diff;
int min_diff;
int min_diff_flag;

void (*fptr[2][2])(int) = {
    {[] (int num) {diff += num; return;},
     [] (int num) {return;}},
    {[] (int num) {return;},
     [] (int num) {diff -= num; return;}}
};

void dfs(int now) {
    // condition check
    if(N <= now) {
        // find min diff
        int temp_diff = abs(diff);
        if(min_diff_flag) {
            if(temp_diff < min_diff) {
                min_diff = temp_diff;
            }
        }
        else {
            min_diff = temp_diff;
            min_diff_flag = 1;
        }
        return;
    }
    // backtracking
    for(int i = 0; i < 2; i++) {
        // pruning
        if(!team_avail[i]) {
            continue;
        }
        // process
        team_avail[i]--;
        team[now] = i;
        for(int j = 0; j < now; j++) {
            fptr[team[j]][team[now]](s[j][now]);
        }
        // recursive
        dfs(now + 1);
        // unprocess
        team_avail[i]++;
        for(int j = 0; j < now; j++) {
            fptr[1^team[j]][1^team[now]](s[j][now]); // invert j, now to undo operation {0,0} <-> {1,1}
        }
    }
}

int main() {
    // read 1 int (T: testcase)
    int T;
    cin >> T;
    // execute each testcase
    for(int testcase = 1; testcase <= T; testcase++) {
        // read 1 int (N: number)
        cin >> N;
        // read N*N synergy values
        for(int i = 0; i < N; i++) {
            int syn;
            for(int j = 0; j < i; j++) { // bottom left half
                cin >> syn;
                s[j][i] += syn;
            }
            for(int j = i; j < N; j++) { // top right half
                cin >> syn;
                s[i][j] = syn;
            }
        }
        // run dfs
        team_avail[0] = N / 2;
        team_avail[1] = N / 2;
        diff = 0;
        min_diff_flag = 0;
        fill(team, team + N_MAX, 0);
        dfs(0);
        // print result
        cout << "#" << testcase << " " << min_diff << "\n";
    }
    return 0;
}