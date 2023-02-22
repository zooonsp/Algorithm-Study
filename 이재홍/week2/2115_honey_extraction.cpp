#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// at (N,N) array, select 2 length M row, find max value(square sum, sum under K)
// 1. select 2 row range (sliding window)
// 2. find max square sum
//     if (a + b + c + ... <= N)
//     max of (a^2 + b^2 + c^2 + ...) => make difference between numbers big
//     1. sort window
//     2. find max value
//     3. repeat 2.1.
//     4. get two window in single row value
// 3. repeat 2.
// 4. get two window in different row value
// 5. get max value

int win[5];
int row_val[10];
int row_max[10];
int row_two_max;

int main() {
    // read 1 int
    int T;
    cin >> T;
    // start testcase loop
    for(int testcase = 1; testcase <= T; testcase++) {
        // read 2 int
        int N, M, C;
        cin >> N >> M >> C;
        // prepare array
        fill(row_max, row_max + N, 0);
        row_two_max = 0;
        // find max in row
        for(int col = 0; col < N; col++) {
            // prepare array
            fill(row_val, row_val + N, 0);
            // first window
            priority_queue<int> pq;
            for(int row = 0; row <= M - 1; row++) {
                cin >> win[row];
                pq.push(win[row]);
            }
            int C_ = C;
            while(!pq.empty()) {
                int cost = pq.top();
                pq.pop();
                if(0 <= C_ - cost) {
                    row_val[0] += cost * cost;
                    C_ -= cost;
                    if(!C_) {break;}
                }
            }
            row_max[col] = row_val[0];

            // rest of window
            for(int row = M; row < N; row++) {
                cin >> win[row % M];
                priority_queue<int> pq;
                for(int i = 0; i < M; i++) {
                    pq.push(win[i]);
                }
                int C_ = C;
                while(!pq.empty()) {
                    int cost = pq.top();
                    pq.pop();
                    if(0 <= C_ - cost) {
                        row_val[row - M + 1] += cost * cost;
                        C_ -= cost;
                        if(!C_) {break;}
                    }
                }
                if(row_max[col] < row_val[row - M + 1]) {
                    row_max[col] = row_val[row - M + 1];
                }
            }

            // calculate double window in single row
            for(int i = 0; i < N - 2 * M + 1; i++) {
                for(int j = i + M; j < N - M + 1; j++) {
                    int row_two = row_val[i] + row_val[j];
                    if(row_two_max < row_two) {row_two_max = row_two;}
                }
            }
        }
        // calculate different row sum
        for(int i = 0; i < N; i++) {
            for(int j = i + 1; j < N; j++) {
                int two_row = row_max[i] + row_max[j];
                if(row_two_max < two_row) {row_two_max = two_row;}
            }
        }
        // print result
        cout << "#" << testcase << " " << row_two_max << "\n";
    }
    return 0;
}