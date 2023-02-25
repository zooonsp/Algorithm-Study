#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <cmath> // abs
#include <algorithm>
#include <cstdio>

using namespace std;

struct coord {
	int x, y; // 계단 위치
	coord(int x, int y) : x(x), y(y) {}
};

int N{}; // 크기
int peopleCnt{}; // 사람 수
int ans{}; // 답
vector<vector<int>> Map; // 입력받을 map
vector<vector<int>> tmpMap; // Map에 사람 index 저장
vector<coord> stairsPos; // 계단 위치 저장
vector<int> stairs; // 계단 길이
vector<coord> peoples; // 사람 위치 저장
vector<vector<int>> peopleToStair; // [2][사람 수] 사람 ~ 의자까지 거리

inline int ManhattanDist(const coord& stair, const coord& people) {
	return abs(stair.x - people.x) + abs(stair.y - people.y);
}

vector<int> choices;
void dfs(int index) {
	if (index == peopleCnt) {
		// 다 골라졌으니 시간 측정
		priority_queue<int, vector<int>, greater<int>> arriveFirstStair;
		priority_queue<int, vector<int>, greater<int>> arriveSecondStair;
		for (int i = 0; i < peopleCnt; ++i) {
			if (choices[i]) arriveSecondStair.push(peopleToStair[1][i]); // 도착 시간
			else arriveFirstStair.push(peopleToStair[0][i]); // 도착 시간
		}

		int start{};
		if (arriveFirstStair.empty()) start = arriveSecondStair.top();
		else if (arriveSecondStair.empty()) start = arriveFirstStair.top();
		else start = min(arriveFirstStair.top(), arriveSecondStair.top());

		priority_queue<int, vector<int>, greater<int>> moveFirstStair; // 이동중인 사람들
		priority_queue<int, vector<int>, greater<int>> moveSecondStair; // 이동중인 사람들

		// int tmp_ans{ 21e8 };
		for (int times = start + 1;; ++times) {
			if (times >= ans) return; // 더 볼 필요 없음

			while (!moveFirstStair.empty() && moveFirstStair.top() <= times) {
				moveFirstStair.pop();
				// tmp_ans = min(tmp_ans, times);
			}

			while (!moveSecondStair.empty() && moveSecondStair.top() <= times) {
				moveSecondStair.pop();
				// tmp_ans = min(tmp_ans, times);
			}

			while (!arriveFirstStair.empty() && arriveFirstStair.top() < times) {
				if (moveFirstStair.size() < 3) { // 계단은 최대 3명
					moveFirstStair.push(max(times, arriveFirstStair.top()) + stairs[0]);
					arriveFirstStair.pop();
				}
				else {
					break; // 더 이상 넣을 수 없어서 나와야 함.
				}
			}
			while (!arriveSecondStair.empty() && arriveSecondStair.top() < times) {
				if (moveSecondStair.size() < 3) { // 계단은 최대 3명
					moveSecondStair.push(max(times, arriveSecondStair.top()) + stairs[1]);
					arriveSecondStair.pop();
				}
				else {
					break; // 더 이상 넣을 수 없어서 나와야 함.
				}
			}

			if (moveFirstStair.empty() && moveSecondStair.empty() &&
				arriveFirstStair.empty() && arriveSecondStair.empty()) {
				ans = min(ans, times);
				break;
			}
		}

		return;
	}

	choices[index] = 0;
	dfs(index + 1);
	choices[index] = 0;

	choices[index] = 1;
	dfs(index + 1);
	choices[index] = 0;
}

int main() {
	int T{};
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N;
		peopleCnt = 0;
		ans = static_cast<int>(21e8);
		Map.assign(N, vector<int>(N, 0));
		tmpMap.assign(N, vector<int>(N, 0));
		stairsPos.clear();
		stairs.clear();
		peoples.clear(); // 초기화를 잘 하자..
		
		stairsPos.reserve(10);
		peoples.reserve(20);
		

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> Map[i][j];
				if (Map[i][j] > 1) { // 계단
					stairsPos.push_back(coord(i, j));
					stairs.push_back(Map[i][j]); // 길이
				}
				else if (Map[i][j]) { // 사람
					tmpMap[i][j] = peopleCnt++;
					peoples.push_back(coord(i, j));
				}
			}
		}

		// 사람에서 게단까지 거리 구하기
		peopleToStair.assign(2, vector<int>(peopleCnt, 0));
		choices.assign(peopleCnt, -1); // 각 사람마다 고르는 선택
		for (int i = 0; i < peopleCnt; ++i) {
			peopleToStair[0][i] = ManhattanDist(peoples[i], stairsPos[0]);
			peopleToStair[1][i] = ManhattanDist(peoples[i], stairsPos[1]);
		}

		// 모든 경우 계산
		dfs(0);

		cout << "#" << tc << ' ' << ans << endl;
	}
	return 0;
}

