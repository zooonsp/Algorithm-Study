#include <algorithm>
#include <deque>
#include <iostream>
using namespace std;

int dx[]{1, 1, 0, -1, -1, -1, 0, 1};
int dy[]{0, -1, -1, -1, 0, 1, 1, 1};

int N, M, K;
deque<int> tree[10][10]; // (y, x)에 있는 나무들의 나이
int MAP[10][10];         // 땅의 양분
int A[10][10];           // 겨울에 추가되는 양분

void simulation() {
  // die[y][x]: (y, x)에서 죽은 나무로 인해 추가될 양분
  // cnt[y][x]: (y, x)에 생길 나이가 1인 나무의 개수
  int die[10][10]{}, cnt[10][10]{};

  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      int sz = tree[y][x].size();

      // (y, x)에 있는 나무의 개수만큼 반복
      while (sz--) {
        // 현재 나무의 나이
        int age = tree[y][x].front();
        tree[y][x].pop_front();

        // 나이만큼 양분을 먹을 수 없는 경우 죽어서 양분이 된다.
        if (MAP[y][x] < age) {
          die[y][x] += age / 2;
          continue;
        }

        // 양분을 먹고 나이 1 증가
        MAP[y][x] -= age;
        tree[y][x].push_back(age + 1);

        // 증가한 나이가 5의 배수가 아니면 번식하지 않는다.
        if ((age + 1) % 5 != 0)
          continue;

        // 번식
        for (int i = 0; i < 8; i++) {
          int ny = y + dy[i];
          int nx = x + dx[i];

          if (ny < 0 || ny >= N || nx < 0 || nx >= N)
            continue;

          // (ny, nx)에 생길 나이가 1인 나무 개수 증가
          cnt[ny][nx]++;
        }
      }
    }
  }

  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      // 죽은 나무로 인해 추가될 양분과 겨울에 추가되는 양분을 더해준다.
      MAP[y][x] += A[y][x] + die[y][x];
      // 새로 생길 나이가 1인 나무는 무조건 다른 나무들보다 어리다. => 앞에 추가
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
      MAP[y][x] = 5; // 가장 처음 양분은 5
    }
  }

  for (int i = 0; i < M; i++) {
    int y, x, z;
    cin >> y >> x >> z;
    // 입력으로 주어지는 나무의 위치는 모두 서로 다르므로
    // 초기 나무는 0개 아니면 1개
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
