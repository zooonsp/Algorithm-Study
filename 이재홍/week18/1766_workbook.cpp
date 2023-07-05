#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int income_;
    vector<int> destination_;
};

struct Ranking {
    int size_;
    int edges_;
    vector<Node> nodes_;
    Ranking(int size, int edges): size_(size), edges_(edges), nodes_(vector<Node>(size + 1)) {
        for(int it = 0; it < edges; ++it) {
            int departure;
            int destination;
            cin >> departure >> destination;
            nodes_[departure].destination_.push_back(destination);
            nodes_[destination].income_ += 1;
        }
    }
    void print() {
        priority_queue<int, vector<int>, greater<int>> zero_incomes;
        for(int it = 1; it <= size_; ++it) {
            if(nodes_[it].income_ != 0) {continue;}
            zero_incomes.push(it);
        }
        while(!zero_incomes.empty()) {
            int poped = zero_incomes.top();
            zero_incomes.pop();
            for(int destination: nodes_[poped].destination_) {
                if(--nodes_[destination].income_) {continue;}
                zero_incomes.push(destination);
            }
            cout << poped << ' ';
        }
    }
};

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    int size;
    int edges;
    cin >> size >> edges;
    Ranking ranking{size, edges};
    ranking.print();
    return 0;
}