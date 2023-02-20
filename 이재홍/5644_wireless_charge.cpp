#include <iostream>
#include <algorithm>
// 8 bc and 1 default
#define CHARGER_MAX 9
#define COMBINATION_MAX 512
#define TIME_MAX 100
using namespace std;
// charger overlap combination is max 2^8
// combination of 2 person is (2^8,2^8)
// calculate value of typical state when face the state
// not use map: calculating distance between bc and person can be done by coordinate calculation

struct BC {
    int y;
    int x;
    int cover;
    int power;
};

struct User {
    int y;
    int x;
};

BC bc[CHARGER_MAX]; // bc[0] is default state with 0 power
int c[COMBINATION_MAX][COMBINATION_MAX]; // max value at state, default: -1
                                         // index can be accessed by (1<<i)

int walk[2][TIME_MAX];


int M; // total time moved
int A; // number of BC

// declare direct array
int dy[5] = { 0,-1, 0, 1, 0};
int dx[5] = { 0, 0, 1, 0,-1};

int d(int x1, int y1, int x2, int y2) { // calculate distance
    return abs(y1 - y2) + abs(x1 - x2);
}

// calculate max charge value at given state
int findMax(int s1, int s2) {
    int max_val = 0; // min value of max_val is 0
    for(int i = 0; i <= A; i++) {
        if(s1 & (1<<i)) {
            for(int j = 0; j < i; j++) { // when i > j
                if(s2 & (1<<j)) {
                    if(max_val < bc[i].power + bc[j].power) {
                        max_val = bc[i].power + bc[j].power;
                    }
                }
            }
            if(s2 & (1<<i)) { // when i == j
                if(max_val < bc[i].power) {
                    max_val = bc[i].power;
                }
            }
            for(int j = i + 1; j <= A; j++) { // when i < j
                if(s2 & (1<<j)) {
                    if(max_val < bc[i].power + bc[j].power) {
                        max_val = bc[i].power + bc[j].power;
                    }
                }
            }
        }
    }
    return max_val;
}

int getBC(int x, int y) { // get accassable BC bit
    int ret = 0;
    for(int i = 1; i <= A; i++) {
        if(d(x, y, bc[i].x, bc[i].y) <= bc[i].cover) {
            ret ^= (1<<i);
        }
    }
    return ret + 1; // include default state
}

int getBC(User p) {
    return getBC(p.x, p.y);
}

int main() {
    // read 1 int (T: testcase)
    int T;
    cin >> T;
    // execute each testcase
    for(int testcase = 1; testcase <= T; testcase++) {
        // read 2 int (M: total time moved, A: number of BC)
        cin >> M >> A;
        // read walk history
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < M; j++) {
                cin >> walk[i][j];
            }
        }
        // read BC info (read from 1 to A)
        for(int i = 1; i <= A; i++) {
            cin >> bc[i].x;
            cin >> bc[i].y;
            cin >> bc[i].cover;
            cin >> bc[i].power;
        }
        // prepare c space
        int ij_end = 1<<(A + 1);
        for(int i = 0; i < ij_end; i++) {
            for(int j = 0; j < ij_end; j++) {
                c[i][j] = -1;
            }
        }
        // calculate at initial state
        int max_ret = 0;
        User p1 = {1, 1}; // declare person
        User p2 = {10, 10};
        int s1 = getBC(p1); // get state
        int s2 = getBC(p2);
        c[s2][s1] = c[s1][s2] = findMax(s1, s2); // calculate max power
        max_ret += c[s1][s2]; 
        // calculate after initial
        for(int i = 0; i < M; i++) {
            p1.x = p1.x + dx[walk[0][i]]; // move person
            p1.y = p1.y + dy[walk[0][i]];
            p2.x = p2.x + dx[walk[1][i]];
            p2.y = p2.y + dy[walk[1][i]];
            s1 = getBC(p1); // get state
            s2 = getBC(p2);
            if(0 <= c[s1][s2]) { // calculated
                max_ret += c[s1][s2];
            }
            else { // not calculated
                c[s2][s1] = c[s1][s2] = findMax(s1, s2);
                max_ret += c[s1][s2];
            }
        }
        // print result
        cout << "#" << testcase << " " << max_ret << "\n";
    }
    return 0;
}