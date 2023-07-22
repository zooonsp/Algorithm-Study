#include <iostream>
#include <vector>
#include <queue>

constexpr long long INF = 1e18;	// INF: 도시값 초기화

struct Edge{	// 교통수단
	int to;	// to: 도착 도시
	long long cost;	// cost: 교통수단 비용
};

int N, A, B, M;	// N: 도시의 수, A: 시작 도시, B: 도착 도시, M: 교통수단의 개수
std::vector<std::vector<Edge>> adj;	// adj[i]: i 도시에서 탈 수 있는 교통수단 정보
std::vector<int> plusMoney;	// plusMoney[i]: i 도시에서 벌 수 있는 돈
std::vector<long long> money;	// money[i]: i 도시에 도착할 때, 가지고 있는 돈의 액수
std::queue<int> cycleNode;	// cycleNode: 사이클을 구성하는 노드 번호
std::vector<bool> visited;	// visited[i]: i 도시 방문 정보

bool bfs(){

	while(!cycleNode.empty()){	// 사이클을 모두 확인 할 때 까지
		int curr = cycleNode.front();	// curr: 현재 도시 번호
		cycleNode.pop();

		for(Edge& next : adj[curr]){	// next: curr 도시에서 탈 수 있는 교통수단 정보
			if(visited[next.to]) continue;	// 이미 방문한 도시면 continue
			visited[next.to] = true;	// 방문 체크
			cycleNode.push(next.to);	// 계속 이어서 방문
		}
	}
	if(visited[B]) return true;	// 도착 도시에도 사이클이 생긴다면 도착 도시에 도착이 가능하면서, 무한한 돈을 벌 수 있음

	return false;
}

void solution(){

	money.assign(N, INF);
	visited.assign(N, false);

	money[A] = plusMoney[A];	// 시작 도시

	for(int i=0; i<N; ++i){	// N 번 반복
		for(int j=0; j<N; ++j){	// j 번 도시 선택
			for(Edge& next : adj[j]){	// next: j 도시에서 탈 수 있는 교통수단 정보
				if(money[j] == INF) continue;	// 아직 j 도시에 도착한 적이 없다면 continue

				if(money[next.to] <= money[j] + next.cost + plusMoney[next.to]) continue;	// 더 큰 (교통수단 비용과 벌 수 있는 돈을 반대로 설정하였으므로 더 작은 비용) 값을 갖고 있다면 continue

				money[next.to] = money[j] + next.cost + plusMoney[next.to];	// 값 갱신

				if(i == N-1){	// N 번째 반복에서 바뀌는 값이 있다면 싸이클이 있음
					// 사이클 정보 기록
					visited[j] = true;
					cycleNode.push(j);
				}
			}
		}
	}

	return;
}

void input(){

	std::cin >> N >> A >> B >> M;

	adj.assign(N, std::vector<Edge>(0, {0, 0}));
	plusMoney.assign(N, 0);

	for(int i=0; i<M; ++i){
		int from, to, cost;	// from: 시작도시, to: 도착도시, cost: 교통수단 비용
		std::cin >> from >> to >> cost;
		adj[from].push_back({to, cost});	// 교통수단 비용을 + 로 설정
	}

	for(int i=0; i<N; ++i) {
		int n;	// n: i 도시에서 벌 수 있는 돈
		std::cin >> n;
		plusMoney[i] = -n;	// i 도시에서 벌 수 있는 돈을 - 로 설정
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	if(money[B] == INF) std::cout << "gg";	// 오만식이 도착 도시에 도착하는 것이 불가능할 때
	else{
		if(bfs()) std::cout << "Gee";	// 오만식이 도착 도시에 도착했을 때 돈을 무한히 많이 가지고 있을 수 있을 때
		else std::cout << -money[B];	// 도착 도시에 도착할 때, 가지고 있는 돈의 액수의 최댓값
	}

	return 0;
}