#include <iostream>
#include <vector>
#define MAXN 101
using namespace std;
// modification:
// 2: {:19}: nested vector to vector array
//    {:34,:39} prereserve vector space
//    {:56,:62} reset method modified

struct Micro {
    int pop; // population
    int y;
    int x;
    int dir; // direction
    int merged;
};

// microbe field: for merge calculation
vector<Micro*> field[MAXN][MAXN];

// microbe list
vector<Micro> microbe;

vector<Micro*> merge;

// direct array
int dy[5] = { 0,-1, 1, 0, 0};
int dx[5] = { 0, 0, 0,-1, 1};

int main() {
    // read 1 int (T: testcase)
    int T;
    cin >> T;
    // prepare field
    for(int i = 0; i < MAXN; i++) {
        for(int j = 0; j < MAXN; j++) {
            field[i][j].reserve(4);
        }
    }
    // loop for test case
    for(int testcase = 1; testcase <= T; testcase++) {
        // read 3 int (N: field W/H, M: iteration, K: groups)
        int N, M, K;
        cin >> N >> M >> K;
        // prepare microbe list
        microbe = vector<Micro>(K);
        // read K microbe group info
        for(int i = 0; i < K; i++) {
            cin >> microbe[i].y;
            cin >> microbe[i].x;
            cin >> microbe[i].pop;
            cin >> microbe[i].dir;
        }
        // iterate M times
        for(int i = 0; i < M; i++) {
            // prepare field, merge
            for(int i = 0; i < MAXN; i++) {
                for(int j = 0; j < MAXN; j++) {
                    field[i][j].clear();
                }
            }
            merge.clear();
            // loop over microbe groups
            for(int j = 0; j < K; j++) {
                // condition check
                if(microbe[j].merged) {
                    continue;
                }
                // process
                microbe[j].y += dy[microbe[j].dir];
                microbe[j].x += dx[microbe[j].dir];
                // merge check
                if(field[microbe[j].y][microbe[j].x].size() == 1) { // check if field is occupied, only save second group
                    merge.push_back(&microbe[j]);
                }
                field[microbe[j].y][microbe[j].x].push_back(&microbe[j]); // add to field
                // edge check
                if(microbe[j].y == 0 || microbe[j].y == N - 1 || microbe[j].x == 0 || microbe[j].x == N - 1) {
                    microbe[j].dir = ((microbe[j].dir - 1) ^ 1) + 1; // flip direction
                    microbe[j].pop /= 2; // halve the population
                }
            }
            // merge groups
            vector<Micro*>::iterator it = merge.begin();
            vector<Micro*>::iterator it_end = merge.end();
            for(; it != it_end; it++) {
                int y_ = (*it)->y;
                int x_ = (*it)->x;
                // calculate merged pop and find max pop group
                int merged_pop = 0;
                Micro* pb = field[y_][x_].back(); // get last group
                field[y_][x_].pop_back();
                Micro* pmax = pb; // set pb as max pop group
                merged_pop += pb->pop; // add pop to merged group
                while(field[y_][x_].size()) {
                    pb = field[y_][x_].back();
                    field[y_][x_].pop_back();
                    if(pmax->pop < pb->pop) { // set merged flag
                        pmax->merged = 1;
                        pmax = pb;
                    }
                    else {
                        pb->merged = 1;
                    }
                    merged_pop += pb->pop;
                }
                // copy merged to max pop group
                pmax->pop = merged_pop;
            }
        }
        // calculate total pop
        int total_pop = 0;
        for(int i = 0; i < K; i++) {
            if(!microbe[i].merged) {
                total_pop += microbe[i].pop;
            }
        }
        // print result
        cout << "#" << testcase << " " << total_pop << "\n";
    }
    return 0;
}