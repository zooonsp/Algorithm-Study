#include <iostream>
using namespace std;
// use dfs to search all candidates

int N;
int op[4]; // operators
int n[12]; // numbers

// lambda function pointer array
int (*op_f[4])(int, int) = {
    [] (int a, int b) {return a + b;},
    [] (int a, int b) {return a - b;},
    [] (int a, int b) {return a * b;},
    [] (int a, int b) {return a / b;}
};

// declare min max
int res_max;
int res_min;
int res_max_flag;
int res_min_flag;

void dfs(int now, int result) {
    // condition check
    if(N <= now) {
        if(res_max_flag) { // calculate max
            if(res_max < result) {
                res_max = result;
            }
        }
        else {
            res_max = result;
            res_max_flag = 1;
        }
        if(res_min_flag) { // calculate min
            if(result < res_min) {
                res_min = result;
            }
        }
        else {
            res_min = result;
            res_min_flag = 1;
        }
        return;
    }
    // backtracking
    for(int i = 0; i < 4; i++) {
        // pruning
        if(!op[i]) { // no operator left
            continue;
        }
        // process
        op[i]--;
        // recursuve
        dfs(now + 1, op_f[i](result, n[now]));
        // unprocess
        op[i]++;
    }
}

int main() {
    // read 1 int (T: testcase)
    int T;
    cin >> T;
    // execute each testcase
    for(int testcase = 1; testcase <= T; testcase++) {
        // read 1 int (N: numbers)
        cin >> N;
        // read 4 int (op: number of operations)
        cin >> op[0]; // plus
        cin >> op[1]; // minus
        cin >> op[2]; // multiply
        cin >> op[3]; // divide
        // read N int
        for(int i = 0; i < N; i++) {
            cin >> n[i];
        }
        // run dfs
        res_max_flag = 0;
        res_min_flag = 0;
        dfs(1, n[0]);
        // print result
        cout << "#" << testcase << " " << (res_max - res_min) << "\n";
    }
    return 0;
}