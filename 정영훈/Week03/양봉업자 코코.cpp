#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;
int N, M;
int zib[16][16]{};

int dxeven[]{ -1,-1,-1,0,1,0 };
int dyeven[]{ -1,0,1,1,0,-1 };

int dxodd[]{ 0,-1,0,1,1,1 };
int dyodd[]{ -1,0,1,1,0,-1 };

int answer = -1;
int cnt{};
int sum{};

using pii = pair<int, int>;
vector<pii> path; // debugging
int visited[16][16]{}; // 같은 벌집 두 번 방지

vector<pii> possibles; // 현재 정점에서 추가 가능한 점들
int possible_cnts[5]; // index번째 정점에서 추가 가능한 점들의 개수
void dfs(int x, int y) {
	
	if (cnt == 4) {
		// 답 갱신
		answer = max(answer, sum);
		return;
	}

	// 추가 가능한 점들 조사
	if (y % 2) { // odd
		for (int i = 0; i < 6; ++i) {
			int nx = x + dxodd[i];
			int ny = y + dyodd[i];
			if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) continue;
			possibles.push_back(make_pair(nx, ny));
			++possible_cnts[cnt - 1];
		}
	}
	else {
		for (int i = 0; i < 6; ++i) {
			int nx = x + dxeven[i];
			int ny = y + dyeven[i];
			if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) continue;
			possibles.push_back(make_pair(nx, ny));
			++possible_cnts[cnt - 1];
		}
	}

	// 실제 선택
	for (int p = 0; p < possibles.size();++p) {
		if (visited[possibles[p].first][possibles[p].second]) continue;
		sum += zib[possibles[p].first][possibles[p].second];
		++cnt;
		visited[possibles[p].first][possibles[p].second] = 1;
		path.push_back(possibles[p]);

		dfs(possibles[p].first, possibles[p].second);

		sum -= zib[possibles[p].first][possibles[p].second];
		--cnt;
		for (int i = 0; i < possible_cnts[cnt]; ++i) {
			possibles.pop_back(); // 가지 않을 정점에서 들어가버린 possibles 빼기
		}
		possible_cnts[cnt] = 0;
		visited[possibles[p].first][possibles[p].second] = 0;
		path.pop_back();
	}
}

int main() {
	cin >> N >> M;
	
	for (int n = 0; n < N; ++n) {
		for (int m = 0; m < M; ++m) {
			cin >> zib[n][m];
		}
	}

	for (int n = 0; n < N; ++n) {
		for (int m = 0; m < M; ++m) {
			cnt = 1;
			visited[n][m] = 1;
			path.push_back(make_pair(n, m));
			sum = zib[n][m];

			dfs(n,m);

			possibles.clear();
			possible_cnts[0] = 0;
			path.pop_back();
			visited[n][m] = 0;
		}
	}

	cout << answer << '\n';
	
	return 0;
}