#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int N, M;
std::vector<std::vector<int>> adj;
std::vector<std::vector<int>> capacity, flow;
int ans;

void solution(){

	int start = 0, end = N + M + 1;	// start: 시작 노드, end: 끝 노드

	while(true){

		std::vector<int> prev;
		std::queue<int> q;

		prev.assign(N + M + 2, -1);
		q.push(start);

		while(!q.empty()){
			
			if(prev[end] != -1) break;

			int curr = q.front();
			q.pop();

			for(const int& next: adj[curr]){

				if(capacity[curr][next] - flow[curr][next] <= 0) continue;
				if(prev[next] != -1) continue;

				q.push(next);
				prev[next] = curr;
				if(next == end) break;
			}
		}
		if(prev[end] == -1) break;

		int minFlow = 10;
		for(int i=end; i!=start; i=prev[i]) 
			minFlow = std::min(minFlow, capacity[prev[i]][i] - flow[prev[i]][i]);

		for(int i=end; i!=start; i=prev[i]){
			flow[prev[i]][i] += minFlow;
			flow[i][prev[i]] -= minFlow;
		}
		ans += minFlow;
	}	

	return;
}

void input(){

	std::cin >> N >> M;

	adj.assign(N + M + 2, std::vector<int>(0, 0));
	capacity.assign(N + M + 2, std::vector<int>(N + M + 2, 0));
	flow.assign(N + M + 2, std::vector<int>(N + M + 2, 0));

	int start = 0;	// 시작 노드는 0의 값을 가짐
	for(int cowIdx=1; cowIdx<=N; ++cowIdx) {	// 시작 노드와 소를 연결 -> 소 인덱스는 1 ~ N의 범위를 가짐

		capacity[start][cowIdx] = 1;	// 유량 1
		capacity[cowIdx][start] = 1;	// 유량 -1
		adj[start].push_back(cowIdx);	// 시작 노드와 소가 연결
	}

	int end = N + M + 1;	// 끝 노드는 N + M + 1의 값을 가짐
	for(int barnIdx=N+1; barnIdx<=N+M; ++barnIdx){	// 축사와 끝 노드를 연결 -> 축사 인덱스는 N + 1 ~ N + M의 범위를 가짐

		capacity[barnIdx][end] = 1;	// 유량 1
		capacity[end][barnIdx] = 1;	// 유량 -1
		adj[barnIdx].push_back(end);	// 축사와 끝 노드가 연결
	}

	for(int cowIdx=1; cowIdx<=N; ++cowIdx){	// 소와 축사를 연결
		int S;	// cowIdx 소가 들어가기 원하는 축사의 수
		std::cin >> S;

		for(int i=0; i<S; ++i){
			int s;	// cowIdx 소가 들어가기 원하는 축사 번호
			std::cin >> s;

			int barnIdx = N + s;	// barnIdx: 축사 인덱스 -> 축사 인덱스는 N + 1 ~ N + M 사이의 범위를 가짐

			capacity[cowIdx][barnIdx] = 1;	// 유량 1
			capacity[barnIdx][cowIdx] = 1;	// 유량 -1
			adj[cowIdx].push_back(barnIdx);	// 소가 축사로 들어감
		}
	}

	return;
}

int main(){

	input();

	solution();

	std::cout << ans;

	return 0;
}