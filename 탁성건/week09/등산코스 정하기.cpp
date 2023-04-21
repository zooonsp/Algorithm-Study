#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int MAX = 987654321;

struct Edge {
  int to;
  int cost;
  bool operator<(Edge next) const {
    if (cost < next.cost)
      return false;
    if (cost > next.cost)
      return true;
    return false;
  }
};

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates,
                     vector<int> summits) {
  int minIntensity = MAX;
  int minSummit = MAX;

  vector<vector<Edge>> adj(n + 1);
  vector<bool> isSummit(n + 1, false);

  for (vector<int> path : paths) {
    adj[path[0]].push_back({path[1], path[2]});
    adj[path[1]].push_back({path[0], path[2]});
  }

  for (int summit : summits)
    isSummit[summit] = true;

  priority_queue<Edge> pq;
  vector<int> intensity(n + 1, MAX);

  for (int gate : gates) {
    pq.push({gate, 0});
    intensity[gate] = 0;
  }

  while (!pq.empty()) {
    Edge now = pq.top();
    pq.pop();

    if (intensity[now.to] < now.cost)
      continue;

    for (int i = 0; i < adj[now.to].size(); i++) {
      Edge next = adj[now.to][i];

      int ncost = max(now.cost, next.cost);

      if (intensity[next.to] <= ncost)
        continue;

      intensity[next.to] = ncost;

      if (isSummit[next.to])
        continue;

      pq.push({next.to, ncost});
    }
  }

  for (int summit : summits) {
    if (intensity[summit] < minIntensity) {
      minIntensity = intensity[summit];
      minSummit = summit;
    } else if (intensity[summit] == minIntensity) {
      minSummit = min(minSummit, summit);
    }
  }

  return {minSummit, minIntensity};
}
