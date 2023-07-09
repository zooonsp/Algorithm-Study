#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T;
  cin >> T;

  for (int tc = 1; tc <= T; tc++) {
    int N, M;
    cin >> N;

    vector<int> pastRank(N + 1);
    vector<vector<bool>> change(N + 1, vector<bool>(N + 1));
    vector<vector<int>> adj(N + 1);
    vector<int> indegree(N + 1);

    for (int i = 1; i <= N; i++)
      cin >> pastRank[i];

    cin >> M;

    for (int i = 1; i <= M; i++) {
      int a, b;
      cin >> a >> b;
      change[a][b] = change[b][a] = true;
    }

    for (int i = 1; i <= N; i++) {
      for (int j = i + 1; j <= N; j++) {
        auto [a, b] = make_pair(pastRank[i], pastRank[j]);

        if (!change[a][b]) {
          adj[a].push_back(b);
          indegree[b]++;
        } else {
          adj[b].push_back(a);
          indegree[a]++;
        }
      }
    }

    vector<int> rank;
    queue<int> q;

    for (int i = 1; i <= N; i++)
      if (indegree[i] == 0)
        q.push(i);

    while (!q.empty()) {
      int now = q.front();
      q.pop();
      rank.push_back(now);

      for (const int &next : adj[now]) {
        if (indegree[next] == 0)
          continue;
        if (--indegree[next] == 0)
          q.push(next);
      }
    }

    if (rank.size() != N)
      cout << "IMPOSSIBLE";
    else
      for (int team : rank)
        cout << team << ' ';

    cout << '\n';
  }

  return 0;
}
