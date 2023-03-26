#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
  int y;
  int x;
  bool operator<(Node next) const {
    if (y < next.y)
      return true;
    if (y > next.y)
      return false;
    if (x < next.x)
      return true;
    if (x > next.x)
      return false;
    return false;
  }
};

int dx[]{1, 0, -1, 0};
int dy[]{0, -1, 0, 1};

int N, M, fuel;
int MAP[22][22];
vector<Node> clientDest;
Node taxi;

bool simulation() {
  vector<Node> client;
  int visited[22][22]{};
  queue<Node> q;

  visited[taxi.y][taxi.x] = 1;
  q.push(taxi);

  while (!q.empty()) {
    int sz = q.size();

    while (sz--) {
      Node now = q.front();
      q.pop();

      if (MAP[now.y][now.x] > 0)
        client.push_back(now);

      for (int i = 0; i < 4; i++) {
        int ny = now.y + dy[i];
        int nx = now.x + dx[i];

        if (MAP[ny][nx] == -1)
          continue;
        if (visited[ny][nx] != 0)
          continue;

        visited[ny][nx] = visited[now.y][now.x] + 1;
        q.push({ny, nx});
      }
    }

    if (!client.empty())
      break;
  }

  if (client.empty())
    return false;

  sort(client.begin(), client.end());

  taxi = client[0];
  int custId = MAP[taxi.y][taxi.x];
  int dist = visited[taxi.y][taxi.x] - 1;
  Node ndest = clientDest[custId];

  if (fuel < dist)
    return false;

  fuel -= dist;
  MAP[taxi.y][taxi.x] = 0;

  memset(visited, 0, sizeof(visited));
  q = queue<Node>();

  visited[taxi.y][taxi.x] = 1;
  q.push(taxi);

  while (!q.empty()) {
    Node now = q.front();
    q.pop();

    if (now.y == ndest.y && now.x == ndest.x)
      break;

    for (int i = 0; i < 4; i++) {
      int ny = now.y + dy[i];
      int nx = now.x + dx[i];

      if (MAP[ny][nx] == -1)
        continue;
      if (visited[ny][nx] != 0)
        continue;

      visited[ny][nx] = visited[now.y][now.x] + 1;
      q.push({ny, nx});
    }
  }

  dist = visited[ndest.y][ndest.x] - 1;

  if (fuel < dist || dist == -1)
    return false;

  taxi = ndest;
  fuel += dist;

  return true;
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  cin >> N >> M >> fuel;

  clientDest = vector<Node>(M + 1);

  for (int i = 0; i <= N + 1; i++)
    MAP[i][0] = MAP[i][N + 1] = MAP[0][i] = MAP[N + 1][i] = -1;

  for (int y = 1; y <= N; y++) {
    for (int x = 1; x <= N; x++) {
      cin >> MAP[y][x];
      if (MAP[y][x])
        MAP[y][x] = -1;
    }
  }

  cin >> taxi.y >> taxi.x;

  for (int i = 1; i <= M; i++) {
    Node st;
    cin >> st.y >> st.x >> clientDest[i].y >> clientDest[i].x;
    MAP[st.y][st.x] = i;
  }

  for (int i = 0; i < M; i++) {
    if (!simulation()) {
      fuel = -1;
      break;
    }
  }

  cout << fuel << '\n';

  return 0;
}
