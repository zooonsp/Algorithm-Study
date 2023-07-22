#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

constexpr int MAX_V = 26 * 2;	// MAX_V: 알파벳(소문자 + 대문자)의 개수 = 26 + 26개
constexpr int INF = 10e8;	// INF: 최소 유량을 구하기 위한 초기 값

int N;	// N: 파이프의 개수
std::vector<std::vector<int>> capacity, flow;	// capacity[i][j]: i 에서 j로 연결되어 있는 파이프의 용량, flow[i][j]: i 에서 j로 흐르는 유량
std::vector<std::vector<int>> adj;	// adj[i][j]: i와 연결되어 있는 노드 번호
int ans;	// ans: A(우물)에서 Z(외양간)까지의 최대 유량

void solution(){

	int start = 0, end = 25;	// start: 우물의 인덱스, end: 외양간의 인덱스

	while(true){	// 시작 노드(우물)에서 도착 노드(외양간)까지의 모든 경로를 bfs를 사용하여 탐색

		std::vector<int> prev;	// prev: 현재 노드에 방문하기 위한 이전 방문 노드
		std::queue<int> q;	// q: 다음 방문 노드

		prev.assign(MAX_V, -1);
		q.push(start);

		while(!q.empty()){
			if(prev[end] != -1) break;	// 외양간에 방문한 적 있다면 종료

			int curr = q.front();	// curr: 현재 방문 노드
			q.pop();

			for(const int& next: adj[curr]){	// next: 현재 방문 노드와 파이프로 연결되어 있는 노드 번호
				if(capacity[curr][next] - flow[curr][next] <= 0) continue;	// 파이프의 용량을 초과했다면 (유량을 늘릴 수 없다면) continue
				if(prev[next] != -1) continue;	// 이미 방문한 노드라면 continue

				q.push(next);
				prev[next] = curr;	// next 노드는 curr 노드를 통해 방문함

				if(next == end) break;	// 외양간에 도착했다면 break
			}
		}
		if(prev[end] == -1) break;	// 탐색 후에 외양간에 도착하지 못했다면 break

		int minFlow = INF;	// minFlow: 경로에 있는 파이프의 최소 유량
		for(int i=end; i!=start; i=prev[i]){	// 도착 지점(외양간)에서 시작 지점(우물)로 가면서 탐색
			minFlow = std::min(minFlow, capacity[prev[i]][i] - flow[prev[i]][i]);	// 파이프의 최소 유량 계산
		}

		// 계산한 최소 유량을 사용하여 흐르는 유량 갱신
		for(int i=end; i!=start; i=prev[i]){
			flow[prev[i]][i] += minFlow;
			flow[i][prev[i]] -= minFlow;
		}

		ans += minFlow;	// 총 유량 증가
	}

	return;
}

void input(){

	// 공간 할당
	capacity.assign(MAX_V, std::vector<int>(MAX_V, 0));
	flow.assign(MAX_V, std::vector<int>(MAX_V, 0));
	adj.assign(MAX_V, std::vector<int>(0, 0));

	std::cin >> N;
	for(int i=0; i<N; ++i){
		char charU, charV;	// charU, charV: 파이프가 연결되어 있는 두 노드
		int u, v;	// u, v: 파이프가 연결되어 있는 두 노드의 인덱스
		int w;	// w: 파이프의 용량

		std::cin >> charU >> charV >> w;

		// 인덱스로 변환 -> 대문자는 65~90이고 소문자는 97~122이므로 대문자를 0~25, 소문자를 26~51로 변환
		u = charU <= 'Z'? charU - 'A': charU-'a' + 26;
		v = charV <= 'Z'? charV - 'A': charV-'a' + 26;

		capacity[u][v] = capacity[v][u] += w;	// 파이프는 양방향으로 흐를 수 있음

		// 양방향 연결 정보 입력
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	input();

	solution();

	std::cout << ans;

	return 0;
}