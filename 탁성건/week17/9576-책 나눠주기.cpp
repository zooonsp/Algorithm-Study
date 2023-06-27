#include <cstring>
#include <iostream>
using namespace std;

struct Range {
  int st;
  int en;
};

constexpr int MAX_N = 1000;
constexpr int MAX_M = 1000;

int N, M;                    // N: 책 개수, M: 학생 수
Range adj[MAX_M + 1];        // 학생이 원하는 책 번호 범위
int studentMatch[MAX_M + 1]; // 학생에 매칭된 책 번호
int bookMatch[MAX_N + 1];    // 책에 매칭된 학생 번호
bool visited[MAX_M + 1];     // 학생 정점 방문 여부

// studentIdx에서 매칭되지 않은 bookIdx로 가는 경로 찾기
bool dfs(int studentIdx) {
  if (visited[studentIdx])
    return false;

  visited[studentIdx] = true;

  auto [st, en] = adj[studentIdx];

  // 학생이 원하는 책 번호 범위만큼 확인
  for (int bookIdx = st; bookIdx <= en; bookIdx++) {
    // 책이 매칭되지 않았다면 매칭
    // 원래 매칭되어 있던 학생을 다른 책과 매칭시킬 수 있으면 매칭
    if (bookMatch[bookIdx] == -1 || dfs(bookMatch[bookIdx])) {
      studentMatch[studentIdx] = bookIdx;
      bookMatch[bookIdx] = studentIdx;
      return true;
    }
  }

  return false;
}

int main(void) {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T;
  cin >> T;

  while (T--) {
    cin >> N >> M;

    for (int i = 1; i <= M; i++)
      cin >> adj[i].st >> adj[i].en;

    memset(studentMatch, -1, sizeof(studentMatch));
    memset(bookMatch, -1, sizeof(bookMatch));

    int ans = 0;

    // 모든 학생에 대해 매칭 시도
    for (int studentIdx = 1; studentIdx <= M; studentIdx++) {
      memset(visited, 0, sizeof(visited));
      // 매칭 성공 시 ans 증가
      if (dfs(studentIdx))
        ans++;
    }

    cout << ans << '\n';
  }

  return 0;
}
