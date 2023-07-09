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

    // 작년 순위
    vector<int> pastRank(N + 1);
    // change[a][b]: a팀과 b팀의 순위가 바뀌었는가?
    vector<vector<bool>> change(N + 1, vector<bool>(N + 1));
    // 상대적 순위 인접 그래프
    vector<vector<int>> adj(N + 1);
    // 해당 정점에 들어오는 간선의 개수
    vector<int> indegree(N + 1);

    for (int i = 1; i <= N; i++)
      cin >> pastRank[i];

    cin >> M;

    // 상대적 순위 변경 정보에 따라 change 갱신
    for (int i = 1; i <= M; i++) {
      int a, b;
      cin >> a >> b;
      change[a][b] = change[b][a] = true;
    }

    // 2개의 팀을 선택하는 모든 경우에 대해
    for (int i = 1; i <= N; i++) {
      for (int j = i + 1; j <= N; j++) {
        auto [a, b] = make_pair(pastRank[i], pastRank[j]);

        // a팀과 b팀의 상대적 순위가
        // 변경되지 않았으면 그대로, 변경되었으면 반대로
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

    // 위상정렬
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

    // N개의 정점이 발견되지 않았다면 순위를 정할 수 없는 경우
    if (rank.size() != N)
      cout << "IMPOSSIBLE";
    else
      for (int team : rank)
        cout << team << ' ';

    cout << '\n';
  }

  return 0;
}
