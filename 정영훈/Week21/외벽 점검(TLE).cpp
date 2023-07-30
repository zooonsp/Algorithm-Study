/*
최소한의 친구들을 투입해 취약 지점을 점검하고 나머지 친구들은 내부 공사를 돕도록
편의 상 레스토랑의 정북 방향 지점을 0으로 나타내며,
취약 지점의 위치는 정북 방향 지점으로부터 시계 방향으로 떨어진 거리로 나타냅니다.
또, 친구들은 출발 지점부터 시계, 혹은 반시계 방향으로 외벽을 따라서만 이동합니다.
TLE : 40점
*/

#include <bits/stdc++.h>

using namespace std;

/*
외벽의 길이 n : n은 1 이상 200 이하인 자연수
취약 지점의 위치가 담긴 배열 weak : weak의 길이는 1 이상 15 이하입니다.
	서로 다른 두 취약점의 위치가 같은 경우는 주어지지 않습니다.
	취약 지점의 위치는 오름차순으로 정렬되어 주어집니다.
	weak의 원소는 0 이상 n - 1 이하인 정수입니다.
각 친구가 1시간 동안 이동할 수 있는 거리가 담긴 배열 dist : dist의 길이는 1 이상 8 이하입니다.
	dist의 원소는 1 이상 100 이하인 자연수입니다.
취약 지점을 점검하기 위해 보내야 하는 친구 수의 최소값을 return(모두 투입해도 안 되면 -1 리턴)
*/

constexpr int INF = 1 << 30;
constexpr int NEEDFORCHECK = 1;
constexpr int FINISHCHECK = 2;
int ans = INF, weakNum, friendNum;

vector<int> weakVisited, friendVisited;

void DFS(vector<int>&weak, vector<int>&dist, int n, int friendCnt, int fixedCnt, int index) { // index = weak의 인덱스
	if (fixedCnt == weakNum) {
		ans = min(ans, friendCnt);
		return;
	}

	if (index == weakNum) {
		return;
	}

	if (friendCnt > ans) return;

	vector<int> weakVisitedCopy(weakVisited);
	if (weakVisited[weak[index]] == FINISHCHECK) {
		DFS(weak, dist, n, friendCnt, fixedCnt, index + 1);
	}
	for (int f = 0; f < friendNum; ++f) {
		if (friendVisited[f]) continue; // 이미 점검 감
		friendVisited[f] = 1;

		// + 시계
		int start = weak[index];
		int step = dist[f];
		int cnt = 0;
		for (int s = 0; s <= step; ++s) {
			if (weakVisited[(start + s) % n] == NEEDFORCHECK) {
				weakVisited[(start + s) % n] = FINISHCHECK;
				++cnt;
			}
		}
		DFS(weak, dist, n, friendCnt + 1, fixedCnt + cnt, index + 1);
		weakVisited = weakVisitedCopy;

		// - 반시계
		cnt = 0;
		for (int s = 0; s <= step; ++s) {
			if (weakVisited[(start - s + n) % n] == NEEDFORCHECK) {
				weakVisited[(start - s + n) % n] = FINISHCHECK;
				++cnt;
			}
		}
		DFS(weak, dist, n, friendCnt + 1, fixedCnt + cnt, index + 1);
		weakVisited = weakVisitedCopy;
		friendVisited[f] = 0;
	}
	DFS(weak, dist, n, friendCnt, fixedCnt, index + 1);
}

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = 0;
	weakNum = (int)weak.size();
	friendNum = (int)dist.size();
	ans = INF;

	// set visited
	weakVisited = vector<int>(n, 0);
	friendVisited = vector<int>(n, 0);

	for (int& w : weak) weakVisited[w] = NEEDFORCHECK;

	DFS(weak, dist, n, 0, 0, 0);

	answer = ans;
	if (answer == INF) answer = -1;
	return answer;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	
	cout << solution(12, { 1,5,6,10 }, { 1,2,3,4 }) << '\n';
	cout << solution(12, { 1,3,4,9,10 }, { 3,5,7 }) << '\n';

	return 0;
}