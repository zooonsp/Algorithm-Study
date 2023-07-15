/*
지점의 개수 n, 출발지점을 나타내는 s, A의 도착지점을 나타내는 a, B의 도착지점을 나타내는 b, 지점 사이의 예상 택시요금을 나타내는 fares
두 사람이 s에서 출발해서 각각의 도착 지점까지 택시를 타고 간다고 가정할 때, 최저 예상 택시요금을 계산

지점갯수 n은 3 이상 200 이하인 자연수 => 정점 개수가 n * 100 => floyd-warshall 가능
지점 s, a, b는 1 이상 n 이하인 자연수이며, 각기 서로 다른 값입니다.
  즉, 출발지점, A의 도착지점, B의 도착지점은 서로 겹치지 않습니다.
fares는 2차원 정수 배열입니다.
fares 배열의 크기는 2 이상 n x (n-1) / 2 이하입니다.
  fares 배열의 각 행은 [c, d, f] 형태입니다.
  c지점과 d지점 사이의 예상 택시요금이 f원이라는 뜻입니다.
  지점 c, d는 1 이상 n 이하인 자연수이며, 각기 서로 다른 값입니다.
  요금 f는 1 이상 100,000 이하인 자연수입니다.
  fares 배열에 두 지점 간 예상 택시요금은 1개만 주어집니다. 즉, [c, d, f]가 있다면 [d, c, f]는 주어지지 않습니다.
출발지점 s에서 도착지점 a와 b로 가는 경로가 존재하는 경우만 입력으로 주어집니다.
*/

#include<bits/stdc++.h>

using namespace std;
constexpr int INF = 1 << 29;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;
    answer = INF;

    vector<vector<int>> dist(n+1, vector<int>(n+1,INF));
    for(int i=1;i<=n;++i) dist[i][i] = 0;

    for(auto& row : fares) {
      auto [from, to, cost] = make_tuple(row[0], row[1], row[2]); // self loop X, 두 정점 사이 간선은 오직 1개
      dist[from][to] = dist[to][from] = cost; // 무방향 간선
    }

    for(int k=1;k<=n;++k) {
      for(int i=1;i<=n;++i) {
        for(int j=1;j<=n;++j) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }

    for(int v=1;v<=n;++v) { // v까지는 함께 이동
      int cost = dist[s][v] + dist[v][a] + dist[v][b];
      answer = min(answer, cost);
    }

    return answer;
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);

  vector<vector<int>> fares1{{4, 1, 10}, {3, 5, 24}, {5,6,2}, {3,1,41},{5,1,24},{4,6,50},{2,4,66},{2,3,22},{1,6,25}};
  cout << solution(6, 4, 6, 2, fares1) << '\n';

  vector<vector<int>> fares2{{5,7,9},{4,6,4},{3,6,1},{3,2,3},{2,1,6}};
  cout << solution(7,3,4,1,fares2) << '\n';

  vector<vector<int>> fares3{{2,6,6},{6,3,7},{4,6,7},{6,5,11},{2,5,12},{5,3,20},{2,4,8},{4,3,9}};
  cout << solution(6,4,5,6,fares3) << '\n';

  return 0;
}