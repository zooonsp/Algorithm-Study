#include <algorithm>
#include <deque>
#include <iostream>
using namespace std;

int dx[]{1, 1, 0, -1, -1, -1, 0, 1};
int dy[]{0, -1, -1, -1, 0, 1, 1, 1};

int N, M, K;
deque<int> tree[10][10];
int MAP[10][10];
int A[10][10];

void simulation() {
  int die[10][10]{}, cnt[10][10]{};

  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      int sz = tree[y][x].size();

      while (sz--) {
        int age = tree[y][x].front();
        tree[y][x].pop_front();

        if (MAP[y][x] < age) {
          die[y][x] += age / 2;
          continue;
        }

        MAP[y][x] -= age;
        tree[y][x].push_back(age + 1);

        if ((age + 1) % 5 != 0)
          continue;

        for (int i = 0; i < 8; i++) {
          int ny = y + dy[i];
          int nx = x + dx[i];

          if (ny < 0 || ny >= N || nx < 0 || nx >= N)
            continue;

          cnt[ny][nx]++;
        }
      }
    }
  }

  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      MAP[y][x] += A[y][x] + die[y][x];
      tree[y][x].insert(tree[y][x].begin(), cnt[y][x], 1);
    }
  }
}

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  cin >> N >> M >> K;

  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      cin >> A[y][x];
      MAP[y][x] = 5;
    }
  }

  for (int i = 0; i < M; i++) {
    int y, x, z;
    cin >> y >> x >> z;
    tree[y - 1][x - 1].push_back(z);
  }

  for (int i = 0; i < K; i++)
    simulation();

  int ans = 0;

  for (int y = 0; y < N; y++)
    for (int x = 0; x < N; x++)
      ans += tree[y][x].size();

  cout << ans << '\n';

  return 0;
}
