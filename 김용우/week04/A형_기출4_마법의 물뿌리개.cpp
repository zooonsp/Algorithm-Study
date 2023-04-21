#include <iostream>
#include <cstring>
#include <algorithm>

int N;	// N: 나무의 개수
int trees[101];	// trees[i]: i 나무의 높이
int targetTall;	// targetTall: 목표 나무 높이
int days;	// days: 나무가 모두 같은 높이가 되는데 걸리는 날짜

bool cmp(int left, int right) {
	if (left > right) return true;
	if (left < right) return false;
	
	return false;
}

void sol() {
	std::sort(trees, trees + N, cmp);	// trees 내림 차순 정렬
	targetTall = trees[0];	// 가장 큰 나무는 목표 나무

	for (int i = 0; i < N; i++)
		trees[i] = targetTall - trees[i];	// 높이의 차를 구함 -> 짝수 혹은 홀수 날 기준이됨

	while (true) {
		int evenNum = 0, oddNum = 0;	// evenNum: 짝수 나무의 개수, oddNum: 홀수 나무의 개수
		for (int i = 0; i < N; i++) {
			if (trees[i] % 2 == 0 && trees[i] != 0)	// 높이의 차가 0인 경우는 추가하지 않음
				evenNum++;
			if (trees[i] % 2 == 1)
				oddNum++;
		}
		if (evenNum == 0 && oddNum == 0)	// 더 이상 자랄 나무가 없음
			return;
		days++;
		if (days % 2 == 1) {	// 홀수 날
			if (oddNum > 0) {	// 홀수 나무가 한개 이상 있다면
				for (int i = 0; i < N; i++) {
					if (trees[i] % 2 == 1) {	// 가장 차이가 적게 나는 홀수 나무 선택
						trees[i]--;
						break;
					}
				}
			}
			else {	// 홀수 날인데 홀수 나무가 없다면
				for (int i = 0; i < N; i++) {
					if (trees[i] % 2 == 0 && trees[i] > 2) {	// 높이가 2 이상 남으면 짝수 나무 선택
						trees[i]--;
						break;
					}
				}				
			}
		}
		else {	// 짝수 날
			if (evenNum > 0) {
				for (int i = 0; i < N; i++) {
					if (trees[i] % 2 == 0 && trees[i] != 0) {	// 짝수 나무가 있다면 가장 차이가 적게 나는 짝수 나무 선택
						trees[i] -= 2;
						break;
					}
				}
			}
			else {	// 짝수 날인데 짝수 나무가 없다면
				if (oddNum > 0) {
					for (int i = 0; i < N; i++) {
						if (trees[i] % 2 == 1 && trees[i] > 2) {	// 높이가 2 이상 남으면 홀수 나무 선택
							trees[i] -= 2;
							break;
						}
					}
				}
			}
		}
	}

}

void input() {
	std::cin >> N;
	memset(trees, 0, sizeof(trees));	// tree 초기화
	for (int i = 0; i < N; i++)
		std::cin >> trees[i];
	days = 0;	// days 초기화

	return;
}

int main() {
	int T;	// T: 테스트 케이스
	std::cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		
		input();
		sol();

		std::cout << '#' << tc << ' ' << days << std::endl;
	}
	return 0;
}