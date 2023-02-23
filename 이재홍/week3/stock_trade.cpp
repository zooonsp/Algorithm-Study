#include <iostream>
using namespace std;

int seed[16]; // seed of each month
int stock_data[15][16]; // save stock price data
int Ms, Ma; // seed, addition
int stock; // number of stock
int month; // month to track

int dfs(int this_month, int stock_idx, int now, int next) {
    // condition check
    if(stock <= stock_idx) {return now + next;} // pass remain seed to next month
    int max_next = next;
    int now_price = stock_data[stock_idx][this_month];
    int next_price = stock_data[stock_idx][this_month + 1];
    if(next_price < now_price) { // skip price dropping stock
        int new_next = dfs(this_month, stock_idx + 1, now, next);
        max_next = max_next < new_next ? new_next : max_next;
        return max_next;
    }
    // backtracking
    int quantity = now / stock_data[stock_idx][this_month];
    for(int i = 0 ; i <= quantity; ++i) { // buy all available combination
        // process
        // recursive
        int new_next = dfs(this_month, stock_idx + 1, now - i * now_price, next + i * next_price);
        // unprocess
        max_next = max_next < new_next ? new_next : max_next;
    }
    return max_next; // get max next seed
}

int main() {
    // read 1 int
    int T;
    cin >> T;
    // start testcase loop
    for(int testcase = 1; testcase <= T; ++testcase) {
        // read 2 int
        cin >> Ms >> Ma;
        // read 2 int
        cin >> stock >> month;
        // read stock info
        for(int i = 0; i < stock; ++i) {
            for(int j = 0; j <= month; ++j) {
                cin >> stock_data[i][j];
            }
        }
        // set initial seed
        seed[0] = Ms;
        for(int i = 0; i < month; ++i) {
            seed[i + 1] = dfs(i, 0, seed[i], Ma);
        }
        // get max profit
        int max_profit = seed[month] - Ms - Ma * month;
        // print max profit
        cout << '#' << testcase << ' ' << max_profit << '\n';
    }
}