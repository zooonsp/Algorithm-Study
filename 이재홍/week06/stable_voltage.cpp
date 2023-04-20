#include <iostream>
#include <bitset>
#define NMAX 200000
using namespace std;
// zero_count[a + N]: number of N's after first N volt, updated by zero_count_before (a: offset) (refer as zero_count[N])
// zero_count_before[a + N]: maximum number of 0 and N's before volt (refer as zero_count_before[N])
// Ex) assume N: volt
// 0:  4 of 0's | 3 of 0's | 3 of 0's | ...
// N:           | 2 of N's | 5 of N's | ...
// zcb[N]:     0|4        4|7        7|7         (zero_count_before[N])
// zc[N]:      0|0        2|0        5|5         (zero_count[N])
// zc[0]:      4|4        7|7       10|10        (zero_count[0])
// mzc of N:   0|4        4|7        7|12        (min_zero_count at N)

int sum;
int max_zero_count;
int max_zero_count_sum;

int zero_count[NMAX + 1 + NMAX];
int zero_count_before[NMAX + 1 + NMAX];
bitset<NMAX + 1 + NMAX> visited;

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    // read 1 int
    int N;
    cin >> N;
    // read N int
    for(int i = 0; i < N; ++i) {
        // read volt
        int volt;
        cin >> volt;
        // check stability
        sum += volt;
        if(volt && zero_count_before[NMAX + volt] + zero_count[NMAX + volt] < zero_count[NMAX + 0]) {
            zero_count[NMAX + volt] = 0;
            zero_count_before[NMAX + volt] = zero_count[NMAX + 0];
        }
        visited[NMAX + volt] = true;
        if(-NMAX <= sum && sum <= NMAX) {
            if(visited[NMAX + sum]) {
                zero_count[NMAX + sum] += 1;
                if(max_zero_count < zero_count_before[NMAX + sum] + zero_count[NMAX + sum]) {
                    max_zero_count = zero_count_before[NMAX + sum] + zero_count[NMAX + sum];
                    max_zero_count_sum = sum;
                }
            }
        }
    }
    cout << max_zero_count;
    return 0;
}