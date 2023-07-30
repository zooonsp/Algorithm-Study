// https://blog.yjyoon.dev/kakao/2021/01/04/kakao-wallcheck/

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

#include <bits/stdc++.h>

using namespace std;

constexpr int INF = 1 << 30;

int solution(int n, vector<int> weak, vector<int> dist) {
	int answer = INF;
	int weakLen = (int)weak.size();

	// 원형에 대한 weak 배열 가공
	for (int i = 0; i < weakLen; ++i) {
		weak.push_back(weak[i] + n);
	}

	sort(dist.begin(), dist.end()); // 순열 계산을 위한 정렬

	do {
		for (int i = 0; i < weakLen; ++i) {
			int start = weak[i]; // 검사 시작 지점
			int finish = weak[i + weakLen - 1]; // 검사 종료 예상 지점
			for (int j = 0; j < dist.size(); ++j) {
				start += dist[j];
				if (start >= finish) { // 모든 지점 방문 완료 시 탈출
					answer = min(answer, j + 1);
					break;
				}

				// 다음 검사 시작 지점 구하기
				// => 마지막에 방문한 지점보다 큰 weak 지점 중 가장 작은 지점
				auto next = upper_bound(begin(weak), end(weak), start);
				start = *next;
			}
		}
	} while (next_permutation(begin(dist), end(dist))); // 모든 순열에 대한 탐색

	if (answer == INF) return -1;

	return answer;
}


int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	cout << solution(12, { 1,5,6,10 }, { 1,2,3,4 }) << '\n';
	cout << solution(12, { 1,3,4,9,10 }, { 3,5,7 }) << '\n';

	return 0;
}
