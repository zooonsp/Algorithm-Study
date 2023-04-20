#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

struct Pos {
  int y;
  int x;
};

struct Edge {
  int to;
  int cost;
  bool operator<(const Edge &next) const { return cost > next.cost; }
};

const int INF = 987654321;
const int MAX_N = 1000;

int dx[]{1, 0, -1, 0, 1, 1, -1, -1};
int dy[]{0, -1, 0, 1, 1, -1, -1, 1};

int N;
char MAP[MAX_N + 2][MAX_N + 2];
int visited[MAX_N + 2][MAX_N + 2];
int area[MAX_N * MAX_N];
int dist[MAX_N * MAX_N];
int nodeCnt;
vector<set<int>> adj;

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);
  cin >> N;

  for (int y = 1; y <= N; y++)
    for (int x = 1; x <= N; x++)
      cin >> MAP[y][x];

  memset(visited, -1, sizeof(visited));

  for (int i = 0; i <= N + 1; i++) {
    visited[0][i] = visited[i][N + 1] = 0;
    visited[N + 1][i] = visited[i][0] = 1;
  }

  visited[0][0] = visited[N + 1][N + 1] = -1;
  nodeCnt = 2;
  adj = vector<set<int>>(2);

  for (int y = 1; y <= N; y++) {
    for (int x = 1; x <= N; x++) {
      if (MAP[y][x] == '.')
        continue;
      if (visited[y][x] != -1)
        continue;

      queue<Pos> q;
      q.push({y, x});
      visited[y][x] = nodeCnt;
      area[nodeCnt]++;
      adj.push_back({});
      char ch = MAP[y][x];

      while (!q.empty()) {
        Pos now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
          int ny = now.y + dy[i];
          int nx = now.x + dx[i];

          if (MAP[ny][nx] != ch)
            continue;
          if (visited[ny][nx] != -1)
            continue;

          q.push({ny, nx});
          visited[ny][nx] = nodeCnt;
          area[nodeCnt]++;
        }
      }

      nodeCnt++;
    }
  }

  for (int y = 1; y <= N; y++) {
    for (int x = 1; x <= N; x++) {
      if (visited[y][x] == -1)
        continue;

      for (int i = 0; i < 8; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if (visited[ny][nx] == -1)
          continue;
        if (visited[y][x] == visited[ny][nx])
          continue;

        adj[visited[y][x]].insert(visited[ny][nx]);
        adj[visited[ny][nx]].insert(visited[y][x]);
      }
    }
  }

  for (int i = 0; i < nodeCnt; i++)
    dist[i] = INF;

  priority_queue<Edge> pq;
  pq.push({0, 0});
  dist[0] = 0;

  while (!pq.empty()) {
    Edge now = pq.top();
    pq.pop();

    if (dist[now.to] < now.cost)
      continue;

    for (int next : adj[now.to]) {
      int ncost = dist[now.to] + area[next];

      if (dist[next] <= ncost)
        continue;

      pq.push({next, ncost});
      dist[next] = ncost;
    }
  }

  cout << dist[1] << '\n';

  return 0;
}
