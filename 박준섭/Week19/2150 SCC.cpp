#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v[10101];
vector<int> s;
vector<vector<int>> scc;
int finished[10101];
int cnt;
int check[10101];
int sccCnt;
int sccNum[10101];

int dfs(int now) {
	// 현재 위치에 대한 cnt를 넣어준다.
	check[now] = ++cnt;

	// 현재 위치 정보를 스택
	s.push_back(now);

	// cnt 정보 저장
	int res = check[now];
	// 다음 간선에 대해서
	for (int next : v[now]) {
		// 다음 노드가 아직 방문하지 않은 곳이라면
		// 현재의 cnt 값과 다음 노드에 대해서 dfs를 돌린 결과에 대해서
		// 최솟값 갱신
		if (check[next] == 0) res = min(res, dfs(next));

		// 확인은 했지만 아직 dfs 탐색중이라면
		else if (!finished[next]) res = min(res, check[next]);
	}

	// 자기 자신으로 돌아온다면
	if (res == check[now]) {
		vector<int> nowScc;

		// dfs를 통해 쌓았던 스택에서 자기 자신이 나올때까지 pop
		while (1) {

			// 가장 나중에 쌓인 것들 부터 차근차근 빼주기
			int t = s.back();
			s.pop_back();
			nowScc.push_back(t);

			// scc에 포함되었기에 1로 변경
			finished[t] = 1;

			sccNum[t] = sccCnt;

			//자기 자신으로 돌아왔다면 while문 종료
			if (t == now) break;
		}

		// 오름차순 정렬
		sort(nowScc.begin(), nowScc.end());
		
		// scc에 정렬된 nowScc 벡터를 삽입
		scc.push_back(nowScc);

		// 전체 scc 개수 +
		sccCnt++;
	}

	return res;
}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int V, E;
	cin >> V >> E;

	// 단방향으로 연결
	for (int i = 0; i < E; i++) {
		int A, B;
		cin >> A >> B;
		v[A].push_back(B);
	}

	// 아직 확인이 안된 친구들만! dfs를 돌려서 scc 찾아줌
	for (int i = 1; i <= V; i++) {
		if (check[i] == 0) dfs(i);
	}

	// 오름차순 정렬
	sort(scc.begin(), scc.end());
	
	// scc 개수 출력
	cout << sccCnt << '\n';

	for (int i = 0; i < scc.size(); i++) {
		for (int j = 0; j < scc[i].size(); j++) {
			cout << scc[i][j] << ' ';
		}
		cout << "-1\n";
	}
	return 0;
}
