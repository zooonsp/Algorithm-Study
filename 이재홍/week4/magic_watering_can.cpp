#include <iostream>
#define MAXNUM 100
using namespace std;
// get max height
// divide difference to 1 and 2
// distribute 1 and 2, make number of 2 is less then number of 1

int height[MAXNUM];

int main() {
    // read 1 int
    int T;
    cin >> T;
    // run testcase loop
    for(int testcase = 1; testcase <= T; ++testcase) {
        // read 1 int
        int N;
        cin >> N;
        // read N tree height
        int max_h = 0;
        for(int i = 0; i < N; ++i) {
            cin >> height[i];
            max_h = max_h < height[i] ? height[i] : max_h;
        }
        // find min day
        int one = 0;
        int two = 0;
        for(int i = 0; i < N; ++i) {
            one += (max_h - height[i]) & 1;
            two += (max_h - height[i]) >> 1;
        }
        // print result
        int two_to_one = (two - one + 1) / 3;
        two_to_one = two_to_one < 0 ? 0 : two_to_one;
        two -= two_to_one;
        one += two_to_one << 1;
        if(two < one) {
            cout << '#' << testcase << ' ' << (one * 2 - 1) << '\n';
        }
        else {
            cout << '#' << testcase << ' ' << (two * 2) << '\n';
        }
    }
    return 0;
}