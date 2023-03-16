#include <iostream>
using namespace std;

int N, T;        // N: 사람 수, T: 팀 수
int speed[1010]; // 두뇌 회전 속도

// HeadSum: 팀원들의 두뇌 회전 속도 합
// tar: 정답이라고 가정한 HeadSum의 MAX값
// tar을 기준으로 T개 이하의 팀을 구성할 수 있는가?
bool isValid(int tar) {
  // 원탁에 앉아 있으니 0부터 N-1까지의 사람을 시작으로
  // 팀을 구성할 수 있는 모든 경우의 수 확인
  for (int i = 0; i < N; i++) {
    int cnt = 0; // 구성할 수 있는 팀의 수
    int sum = 0; // 현재 팀의 HeadSum

    // N명의 사람을 tar을 기준으로 팀 구성
    for (int j = 0; j < N; j++) {
      // 팀을 구성했을 때 tar을 넘지 않으면 팀원에 포함
      if (sum + speed[i + j] <= tar) {
        sum += speed[i + j];
      } else { // tar을 넘으면 새로운 팀 구성
        cnt++;
        sum = speed[i + j];
      }
    }

    // 마지막 남은 그룹 확인
    if (sum > 0)
      cnt++;

    // tar을 기준으로 T개 이하의 팀을 구성할 수 있으면 true 반환
    if (cnt <= T)
      return true;
  }

  // tar을 기준으로 T개 이하의 팀을 구성할 수 없으면 false 반환
  return false;
}

// HeadSum의 MAX값이 가장 작게 나오도록 T개의 팀을 구성
// => HeadSum의 MAX값 반환
int psearch(int l, int r) {
  int left = l;
  int right = r;
  int ans = 0;

  while (left <= right) {
    // mid: 정답이라고 가정한 HeadSum의 MAX값
    int mid = (left + right) / 2;

    // 정답이라고 가정한 HeadSum의 MAX값을 기준으로
    // T개 이하의 팀을 구성할 수 있다면
    if (isValid(mid)) {
      // 정답을 갱신하고 더 작은 HeadSum의 MAX값 찾기
      ans = mid;
      right = mid - 1;
    } else {
      // 더 큰 HeadSum의 MAX값 찾기
      left = mid + 1;
    }
  }

  return ans;
}

int main(void) {
  cin >> N >> T;
  // sum: 모든 사람의 두뇌 회전 속도 합
  // max_speed: 한 사람의 두뇌 회전 속도 최대값
  int sum = 0, max_speed = 0;

  for (int i = 0; i < N; i++) {
    cin >> speed[i];
    // 원탁 => 두뇌 회전 속도 배열 뒤에 똑같은 배열 복사
    speed[N + i] = speed[i];
    sum += speed[i];
    max_speed = max_speed > speed[i] ? max_speed : speed[i];
  }

  // 팀 구성 시 가정할 수 있는
  // 가장 작은 HeadSum의 MAX값: 한 사람의 두뇌 회전 속도 최대값(개인 팀)
  // 가장 큰 HeadSum의 MAX값: 모든 사람의 두뇌 회전 속도 합(모든 사람이 한 팀)
  cout << psearch(max_speed, sum) << '\n';

  return 0;
}
