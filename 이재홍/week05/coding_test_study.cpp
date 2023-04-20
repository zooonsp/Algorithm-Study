#include <string>
#include <vector>
#include <queue>
#define NBOUND 150
#define BIGNUM 87654321
#define PMAX 100
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

// use bfs dijkstra
// start value optimization
// make p_xy array
// do not read problems from start, save problems at available p_xy

// accessing multiple arrays -> big slowdown

// max alp, cop of problems
int max_alp, max_cop;
int min_alp, min_cop;

struct Alco {
    int alp;
    int cop;
    int cost;
    Alco operator+(const Alco &p) const {return {MIN(alp + p.alp, max_alp), MIN(cop + p.cop, max_cop), cost + p.cost};}
    bool operator<(const Alco &p) const {return cost > p.cost || cost == p.cost && (alp + cop) < (p.alp + p.cop);}
};
using vA_it = vector<Alco>::iterator;
Alco d_alp = {1, 0, 1};
Alco d_cop = {0, 1, 1};

// recompose problems to find available problems faster
Alco p_xy[NBOUND + 1][NBOUND + 1][PMAX];
int p_xy_idx[NBOUND + 1][NBOUND + 1];
// bounded cost map, out of range position will be bounded to edge
int cost_map[NBOUND + 1][NBOUND + 1];

int solution(int alp, int cop, vector<vector<int>> problems) {
    int answer = 0;
    // find max alp, cop
    int problemsSize = problems.size();
    for(int i = 0; i < problemsSize; ++i) {
        vector<int> &prob = problems[i];
        max_alp = max_alp < prob[0] ? prob[0] : max_alp;
        max_cop = max_cop < prob[1] ? prob[1] : max_cop;
        min_alp = min_alp > prob[0] ? prob[0] : min_alp;
        min_cop = min_cop > prob[1] ? prob[1] : min_cop;
    }
    // modify alp and cop
    alp = MIN(alp, max_alp);
    cop = MIN(cop, max_cop);
    int init_val = MAX(alp, min_alp) - alp + MAX(cop, min_cop) - cop;
    alp = MAX(alp, min_alp);
    cop = MAX(cop, min_cop);
    // recompose problems to find available problems faster
    for(int i = 0; i < problemsSize; ++i) {
        vector<int> &prob = problems[i];
        if(prob[2] + prob[3] <= prob[4]) {continue;}
        int p_alp = MAX(alp, prob[0]);
        int p_cop = MAX(cop, prob[1]);
        for(int p_y = p_alp; p_y <= max_alp; ++p_y) {
            for(int p_x = p_cop; p_x <= max_cop; ++p_x) {
                p_xy[p_y][p_x][p_xy_idx[p_y][p_x]] = {prob[2], prob[3], prob[4]};
                p_xy_idx[p_y][p_x] += 1;
            }
        }
    }
    // prepare queue
    priority_queue<Alco> pq;
    pq.push({alp, cop, init_val});
    // prepare costmap
    for(int i = alp; i <= max_alp; ++i) {
        for(int j = cop; j <= max_cop; ++j) {
            cost_map[i][j] = BIGNUM;
        }
    }
    cost_map[alp][cop] = 0;
    // run bfs dijkstra
    while(pq.size()) {
        // pop front of queue
        Alco now = pq.top();
        pq.pop();
        // condition check
        if(now.alp == max_alp && now.cop == max_cop) {answer = now.cost; break;}
        // backtracking
        Alco next;
        next = now + d_alp;
        // pruning
        if(next.cost < cost_map[next.alp][next.cop]) {
            //process
            cost_map[next.alp][next.cop] = next.cost;
            // push into queue
            pq.push(next);
        }
        next = now + d_cop;
        // pruning
        if(next.cost < cost_map[next.alp][next.cop]) {
            //process
            cost_map[next.alp][next.cop] = next.cost;
            // push into queue
            pq.push(next);
        }
        int p_xy_len = p_xy_idx[now.alp][now.cop];
        for(int i = 0; i < p_xy_len; ++i) {
            next = now + p_xy[now.alp][now.cop][i];
            // pruning
            if(cost_map[next.alp][next.cop] <= next.cost) {continue;}
            //process
            cost_map[next.alp][next.cop] = next.cost;
            // push into queue
            pq.push(next);
        }
    }
    return answer;
}