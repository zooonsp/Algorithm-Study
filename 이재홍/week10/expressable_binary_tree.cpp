#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Segment {
    int level;
    int position;
    long long get_root();
    long long get_mask();
    void split(queue<Segment> &q);
};

void Segment::split(queue<Segment> &q) {
    if(level == 1) {return;}
    Segment upper = {level - 1, position + (1 << upper.level)};
    Segment lower = {level - 1, position};
    q.push(upper);
    q.push(lower);
}

long long Segment::get_root() {
    return 1LL << (position + (1 << (level - 1)) - 1);
}

long long Segment::get_mask() {
    long long mask = 1LL << ((1 << level) - 1);
    mask -= 1LL;
    return mask << position;
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    int numbers_size = numbers.size();
    for(long long &number : numbers) {
        queue<Segment> q;
        Segment root = {1, 0};
        while(~root.get_mask() & number) {root.level += 1;}
        q.push(root);
        bool representable = true;
        while(!q.empty()) {
            Segment now = q.front();
            q.pop();
            if(number & now.get_root()) {now.split(q);}
            else if(number & now.get_mask()) {representable = false; break;}
        }
        answer.push_back(representable);
    }
    return answer;
}