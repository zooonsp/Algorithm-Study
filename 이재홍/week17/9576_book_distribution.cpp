#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define all(x) x.begin(), x.end()

struct Range {
    int start;
    int end;
    Range(int start, int end): start{start}, end{end} {}
};

void distribute_queue(priority_queue<int, vector<int>, greater<int>> &pq, int &distributed, int &now, int end) {
    while(pq.size() && now <= end) {
        if(now <= pq.top()) {
            ++now;
            ++distributed;
            pq.pop();
        }
        else if(pq.top() < now) {
            pq.pop();
        }
    }
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    int testcases;
    cin >> testcases;
    for(int testcase = 1; testcase <= testcases; ++testcase) {
        int books, students;
        cin >> books >> students;
        int distributed = 0;
        vector<Range> ranges{static_cast<size_t>(students), Range(0, 0)};
        for(Range &range: ranges) {
            cin >> range.start >> range.end;
        }
        sort(all(ranges), [](Range &lhs, Range &rhs) -> bool {return lhs.start < rhs.start;});
        int now = 1;
        priority_queue<int, vector<int>, greater<int>> pq;
        for(Range &range: ranges) {
            if(range.start == now) {
                pq.push(range.end);
                continue;
            }
            distribute_queue(pq, distributed, now, range.start - 1);
            now = range.start;
            pq.push(range.end);
        }
        distribute_queue(pq, distributed, now, books);
        cout << distributed << '\n';
    }
    return 0;
}