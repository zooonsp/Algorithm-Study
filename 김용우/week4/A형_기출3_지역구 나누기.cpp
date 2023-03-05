#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>

int N;	// N: 마을의 수
int P[9];	// P[i]: i 번째 마을의 유권자 수
std::vector<int> v[9];	// v[i]: i 번째 마을과 연결되어있는 마을
int visited[9];	// visited[i]: i 번째 마을의 분류 0: 아직 없음, 1: 지역구 A, 2: 지역구 B
int flag;	// flag: 1이면 모든 마을이 두 개의 지역구로 잘 나누어짐
int ans = 21e8;	// ans: 정답

void DFSB(int now) {

	int tmpflag = 1;
	for (int i = 0; i < N; i++) {
		if (visited[i] == 0) {	// 지역구가 없는 0이 1개라도 있으면 flag = 0
			tmpflag = 0;
			break;
		}
	}
	if (tmpflag == 1) {	// 모든 지역구가 1
		flag = 1;
	}

	for (int i = 0; i < v[now].size(); i++) {
		int next = v[now][i];

		if (visited[next] == 1 || visited[next] == 2) continue;

		visited[next] = 2;	// B 지역구 체크 -> 복구는 안해 줘도 됨
		DFSB(next);
	}

}

bool validCheck(int num) {
	
	int start = -1;

	for (int i = 0; i < N; i++) {	// B 지역구의 연결 여부 살펴보아야함
		if (visited[i] != 1) {	// B 지역구 DFS 시작점
			start = i;
			break;
		}
	}
	if (start == -1)
		return false;

	flag = 0;
	DFSB(start);	// B 지역구 연결 여부

	if (flag == 1)
		return true;
	else
		return false;
}

void DFSA(int now, int num) {
	
	if (validCheck(num)) {	// 모든 마을이 2개의 지역구로 잘 나누어 졌다면 validCheck = true
		int A=0, B=0;
		for (int i = 0; i < N; i++) {
			if (visited[i] == 1)	// A 지역구 
				A += P[i];
			else
				B += P[i];	// B 지역구
		}
		ans = std::min(ans, std::abs(A - B));	// 두 지역구의 유권자 차이의 초소값 저장
	}

	for (int i = 0; i < N; i++) {
		if (visited[i] != 1)	// A 지역구를 기준으로 삼기 때문에 1이 아닌 것은 모두 0으로 만들기
			visited[i] = 0;
	}

	for (int i = 0; i < v[now].size(); i++) {
		int next = v[now][i];

		if (visited[next] == 1) continue;	// 이미 소속이 정해진 마을 i는 continue

		visited[next] = 1;
		DFSA(next, num+1);
		visited[next] = 0;

	}
}

void sol() {
	for (int i = 0; i < N; i++) {	// i 번째 마을은 지역구 A
		memset(visited, 0, sizeof(visited));
		visited[i] = 1;	
		DFSA(i, 1);	// 지역구 A를 DFS로 탐색
	}
}

void input() {
	std::cin >> N;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			int linked;
			std::cin >> linked;
			if (linked == 0) continue;	// 연결 안되어있음
			v[j].push_back(i);
		}
	}
	for (int i = 0; i < N; i++)
		std::cin >> P[i];
}

void reset() {
	for (int i = 0; i < 9; i++) {
		v[i].clear();
		P[i] = 0;
	}
	ans = 21e8;
}

int main() {
	int T;

	std::cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		reset();
		input();
		sol();
		std::cout << '#' << tc << ' ' << ans << std::endl;
	}
	return 0;
}