#include <algorithm>
#include <iostream>
#include <unordered_map>
#define sws ios::sync_with_stdio(false), cin.tie(NULL);
using namespace std;

int N;
int volt[200000]; // 전압
// psum[now]: 0번 idx부터 now번 idx까지의 전압 부분합
int psum[200000];
// zeroCnt[now]: 0번 idx부터 now번 idx까지의 전압 부분합 중 0의 개수
int zeroCnt[200000];
int ans = 0;
// 전압 부분합에서 해당 숫자가 몇 번 나왔는지 count할 unordered_map
unordered_map<int, int> um;

int main(void) {
  sws;
  cin >> N;
  for (int i = 0; i < N; i++)
    cin >> volt[i];

  psum[0] = volt[0];

  for (int i = 1; i < N; i++) // 부분합 계산
    psum[i] = psum[i - 1] + volt[i];

  zeroCnt[0] = (psum[0] == 0);

  for (int i = 1; i < N; i++) // 부분합 중 0의 개수 count
    zeroCnt[i] = zeroCnt[i - 1] + (psum[i] == 0);

  // 아무것도 조작하지 않았을 때 전압이 0으로 만들어지는 횟수
  ans = zeroCnt[N - 1];

  // 뒤에서부터 확인
  for (int i = N - 1; i >= 0; i--) {
    um[psum[i]]++; // 현재 부분합 숫자가 한 번 나왔다고 count
    if (volt[i] == 0) // 전압이 0이라면 조작해도 변화가 없으니 continue
      continue;
    // zeroCnt[i]: 0번부터 i번까지의 전압 부분합 중 0의 개수
    // um[volt[i]]: i번 volt를 0으로 만들었을 때 i번 이후의 0의 개수
    // => i번 volt를 0으로 만들면 i번 volt와 같은 부분합이 0이 된다.
    ans = max(ans, zeroCnt[i] + um[volt[i]]);
  }

  cout << ans << '\n';

  return 0;
}
