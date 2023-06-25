#include <cstring>
#include <iostream>
using namespace std;

struct Range {
  int st;
  int en;
};

constexpr int MAX_N = 1000;
constexpr int MAX_M = 1000;

int N, M;
Range adj[MAX_M + 1];
int studentMatch[MAX_M + 1];
int bookMatch[MAX_N + 1];
bool visited[MAX_M + 1];

bool dfs(int studentIdx) {
  if (visited[studentIdx])
    return false;

  visited[studentIdx] = true;

  auto [st, en] = adj[studentIdx];

  for (int bookIdx = st; bookIdx <= en; bookIdx++) {
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

    for (int studentIdx = 1; studentIdx <= M; studentIdx++) {
      memset(visited, 0, sizeof(visited));
      if (dfs(studentIdx))
        ans++;
    }

    cout << ans << '\n';
  }

  return 0;
}
