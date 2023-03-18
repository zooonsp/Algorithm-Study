// 점수를 기준으로 팀을 짠다는 생각을 하긴 했는데
// 팀을 어떻게 잘라야 할지에 대한 기준이 서지 않았음.

// 처음에는 재귀로 T개의 팀으로 자르기 위한 모든 기준을 다 잘라서 하려고 했으나 말도 안 되는것 같아서 기각
// 아래는 교수님의 아이디어.

/*
8 3
150 130 90 110 140 200 120 90
예를 들어 점수 기준이 400점 인 경우
1. 150을 시작점으로
150 130 90 // 여기에 다음 값인 110을 더하면 400이 넘어가니까 최대값이 400을 넘음
110 140 //
200 120 90
// 3팀
2. 130을 시작점으로
130 90 110 // 여기에 다음 값인 140을 더하면 최대값인 400을 넘음
140 200 //
120 90 150

이런 식으로 반복하다 보면
해당 점수에 대해서 가능한 팀수를 구할 수 있다.
기준 점수가 낮을 수록 팀수가 많이 나오니까
원하는 팀수보다 팀수가 큰 경우에는 점수 기준을 올려서 구하고
원하는 팀수보다 팀수가 작거나 같은 경우에는 점수 기준을 낮춰서 구할 수 있다..
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> vec;
int N, T; // 사람 수, 팀의 수

bool makeTeam(int score) {
	bool ret{};
	for (int s = 0; s < N; ++s) { // start = s
		int nowMax{ -1 }; // s를 시작으로 만들 수 있는 max (필요한 줄 알아서 넣었는데 필요 없넹)
		int tmp_sum{vec[s]}, nowTeamCnt{ 1 }; // team별 합, 만들어지는 team 개수
		for (int t = 1; t < N; ++t) { // s에서 시작해서 N개
			if (score < vec[(s + t) % N]) {
				// 아예 팀을 구성할 수 없음
				return false;
			}
			if (tmp_sum + vec[(s + t) % N] > score) {
				nowMax = max(nowMax, tmp_sum);
				tmp_sum = 0;
				nowTeamCnt++; // 다음 팀~
			}
			tmp_sum += vec[(s + t) % N];
		}
		if (!ret && nowTeamCnt < T) ret = true; // 기준보다 팀 수가 작다
		if (nowTeamCnt == T) ret = true; // 원하는 팀 수를 만들 수 있다.
	}
	return ret;
}

int main() {
	cin >> N >> T;
	vec = vector<int>(N); // 오..
	for (int& v : vec) cin >> v;

	int left = 1, right = 500 * 100000;
	while (left < right) {
		int mid = left + (right - left) / 2; // overflow
		if (makeTeam(mid) == 1) { // 팀수 T보다 작거나 같은 경우에는 점수 기준을 낮추기
			right = mid;
		}
		else { // 팀수가 T보다 큰 경우 점수 기준을 올려야 함.
			left = mid + 1;
		}
	}

	cout << right << endl;
	return 0;
}