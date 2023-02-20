#include <iostream>
#include <algorithm>
using namespace std;
// sequence of 1, 1, 3 size block

// a(n): minimum pool fee
// b(n): used day per month
// a(n+3) = min( c1+a(n), c2+a(n+2), c3*b(n+2)+a(n+2) )

int main() {
    // read 1 int (T: testcase)
    int T;
    cin >> T;
    // loop of testcase
    for(int testcase = 1; testcase <= T; testcase++) {
        // read 4 int (fee: {day, 1 month, 3 month, 12 month})
        int fee[4];
        for(int i = 0; i < 4; i++) {
            cin >> fee[i];
        }

        // read 12 int (useage: useage per month)
        int useage[12];
        for(int i = 0; i < 12; i++) {
            cin >> useage[i];
        }

        // calculate cumulative minimum pool fee
        int min_fee[12];
        min_fee[0] = min(useage[0] * fee[0], fee[1]); // compare day, 1 month
        min_fee[1] = min(useage[1] * fee[0], fee[1]) + min_fee[0]; // compare day, 1 month
        min_fee[2] = min(min_fee[1] + useage[2] * fee[0], min(min_fee[1] + fee[1], fee[2])); // compare day, 1 month, 3 month
        for(int i = 3; i < 12; i++) {
            min_fee[i] = min(min_fee[i - 1] + useage[i] * fee[0], min(min_fee[i - 1] + fee[1], min_fee[i - 3] + fee[2]));
        }
        min_fee[11] = min(min_fee[11], fee[3]); // compare minimum fee, 12 month

        // print result
        cout << "#" << testcase << " " << min_fee[11] << "\n";
    }
    return 0;
}