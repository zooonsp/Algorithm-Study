#include <iostream>
using namespace std;

int *bp; // brain power

int head_sum(int n, int t, int left_init, int right_init) {
    int left = left_init;
    int right = right_init;
    while(left <= right) {
        int mid = (left + right) / 2;
        int front_end = 0; // front and end part sum
        int team_idx = 0; // count team
        int sum = 0; // sum each team
        int start_i = 0; // start team split from start_i
        int ableFlag = 0; // 0: able to compose team, 1: cannot compose team
        while(front_end <= mid) {
            ableFlag = 1;
            if(mid < front_end + bp[start_i]) {ableFlag = 0; break;} // sum front part to front_end
            front_end += bp[start_i];
            ++start_i;
            team_idx = 1;
            int i;
            sum = 0;
            for(i = start_i; i < n; ++i) { // split team from start_i, use gready
                if(mid < sum + bp[i]) {
                    sum = bp[i];
                    ++team_idx;
                    if(t <= team_idx) {break;}
                }
                else {
                    sum += bp[i];
                }
            }
            sum = front_end; // sum end part to front_end
            for(; i < n; ++i) {
                if(mid < sum + bp[i]) {
                    ableFlag = 0;
                    break;
                }
                else {
                    sum += bp[i];
                }
            }
            if(ableFlag) {break;}
        }
        if(ableFlag) {right = mid - 1;}
        else {left = mid + 1;}
    }
    return left;
}

int main() {
    // read 2 int
    int N, T; // number of people, number of team
    cin >> N >> T;
    // read N int
    bp = new int[N];
    int sum, max_val; // get sum of all values and max value
    cin >> bp[0];
    sum = max_val = bp[0];
    for(int i = 1; i < N; i++) {
        cin >> bp[i];
        sum += bp[i];
        if(max_val < bp[i]) {max_val = bp[i];}
    }
    // run binary search
    cout << head_sum(N, T, max_val, sum); // binary search with initial left: max_val, right: sum of all
    // delete array
    delete[] bp;
}