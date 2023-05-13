#include <iostream>
#include <vector>
using namespace std;

struct StartPoint {
    int height;
    int index;
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    int max_value = 0;
    vector<StartPoint> stack;
    stack.push_back({0, 0});
    for(int it = 1; it <= N; ++it) {
        int height;
        cin >> height;
        StartPoint back = {0, it};
        while(height < stack.back().height) {
            back = stack.back();
            int square_size = back.height * (it - back.index);
            max_value = max_value > square_size ? max_value : square_size;
            stack.pop_back();
        }
        if(stack.back().height < height) {stack.push_back({height, back.index});}
    }
    while(!stack.empty()) {
        StartPoint &back = stack.back();
        int square_size = back.height * (N + 1 - back.index);
        max_value = max_value > square_size ? max_value : square_size;
        stack.pop_back();
    }
    cout << max_value;
    return 0;
}