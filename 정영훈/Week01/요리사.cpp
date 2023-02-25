#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

// 시너지 차이 최소화하기
// N = 16 -> 16C8 = 12870
// 12870 / 2 = 6435

/*
6
123 456
124 356
125 346
126 345
134 256
135 246
136 245
145 236
146 235
156 234
-- 0원소 고정 후 실행
-- 볼 필요 없음
234 156
235 146
236 145
245 136
246 135
256 134
345 126
346 125
356 124
456 123
*/

// Adjacency Matrix로도 충분
int AM[16][16]{};
int ans{};
int N;
int visited[16]{};

// vector<int> path; // 선택된 애들 저장
int path_index{};
int path[10]{};
int other_path[10]{};

void dfs(int start) {
	if (path_index == (N >> 1)) {
		// 답 갱신
		// 다른 path 만들기
		int index{};
		for (int i = 0; i < N; ++i) {
			if (!visited[i]) other_path[index++] = i;
		}

		int halfN = N >> 1;
		int first{}, second{};
		for (int i = 0; i < halfN; ++i) {
			for (int j = i + 1; j < halfN; ++j) {
				first += AM[path[i]][path[j]];
				first += AM[path[j]][path[i]];
				second += AM[other_path[i]][other_path[j]];
				second += AM[other_path[j]][other_path[i]];
			}
		}
		int diff = first - second;
		if (diff < 0) diff *= -1;
		ans = min(ans, diff);
		return;
	}
	for (int i = start; i < N; ++i) {
		path[path_index++] = i;
		visited[i] = 1;
		dfs(i + 1);
		path_index--;
		visited[i] = 0;
	}

}

int main()
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		ans = 2e18;
		cin >> N;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> AM[i][j];
			}
		}
		visited[0] = 1;
		path_index = 1;
		dfs(1);
		visited[0] = 0;

		cout << "#" << test_case << ' ' << ans << '\n';

	}
	return 0;
}