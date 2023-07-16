#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// 정점의 수 1e3 * 최대 시간 1e3 = 1e6 만에 할 수 있나?
constexpr int INF = 10e7;	// INF: 나올 수 없는 값

struct Edge{	// Edge: 도로 정보
	int to;	// to: 연결되어 있는 정점
	int cost;	// cost: 도로를 지나는데 걸리는 시간

	bool operator < (const Edge& next) const {
		return cost > next.cost;	// cost에 따른 오름차순 정렬
	}
};

int N, M;	// N: 정점의 개수, M: 도로의 수
std::vector<std::vector<Edge>> edge;	// edge[i]: i 정점과 연결되어있는 도로 정보
std::vector<int> parent;	// parent[i]: 최단 거리로 i 정점으로 가기 위한 정점 번호
int ans;	// ans: 적당한 도로 하나를 파괴했을 때 1번 정점에서 N번 정점으로의 최단거리의 최댓값

void dijkstra(int destroyA, int destroyB){	// dstroyA, destroyB: 두 정점을 연결하는 도로를 파괴

	std::priority_queue<Edge> pq;	// pq: cost를 기준으로 오름차순 정렬하는 우선순위 큐
	std::vector<int> cost(N+1, INF);	// cost[i]: i 정점의 최단 시간

	pq.push({1, 0});
	cost[1] = 0;

	while(!pq.empty()){
		Edge curr = pq.top();	// curr: 탐색할 도로 정보
		pq.pop();

		if(cost[curr.to] < curr.cost) continue;	// 이 도로를 사용하지 않고도 더 적은 비용으로 이미 갈 수 있다면 continue

		for(const Edge& next : edge[curr.to]){	// next: 이동한 정점에 연결되어 있는 도로
			if(curr.to == destroyA && next.to == destroyB) continue;	// A -> B 도로 파괴
			if(curr.to == destroyB && next.to == destroyA) continue;	// B -> A 도로 파괴

			int nextCost = cost[curr.to] + next.cost;	// nextCost: next 도로를 사용하였을 때 next.to 정점 까지의 비용

			if(cost[next.to] <= nextCost) continue;	// nextCost 보다 더 적은 비용으로 방문 할 수 있으면 continue

			pq.push({next.to, nextCost});	// 다음 탐색에 사용
			cost[next.to] = nextCost;	// 비용 갱신
		}
	}

	if(cost[N] == INF) return;	// 어떤 하나의 도로를 파괴하더라도 1번 정점에서 N번 정점으로 도달 가능하지만.. 우선 써놓기
	ans = std::max(ans, cost[N]);	// 최단거리의 최댓값 갱신

	return;
}

void solution(){

	std::priority_queue<Edge> pq;	// pq: cost에 따라 오름차순 정렬한 우선순위 큐
	std::vector<int> cost(N+1, INF);	// cost[i]: i 정점까지의 최단 거리 시간

	pq.push({1, 0});	// 1 번 정점에서 시작
	cost[1] = 0;

	while(!pq.empty()){

		Edge curr = pq.top();	// curr: 탐색할 도로 정보
		pq.pop();

		if(cost[curr.to] < curr.cost) continue;	// 이 도로를 사용하지 않고도 더 적은 비용으로 이미 갈 수 있다면 continue

		for(const Edge& next : edge[curr.to]){	// next: 이동한 정점에 연결되어 있는 도로
			int nextCost = cost[curr.to] + next.cost;	// nextCost: next 도로를 사용하였을 때 next.to 정점 까지의 비용

			if(cost[next.to] <= nextCost) continue;	// nextCost 보다 더 적은 비용으로 방문 할 수 있으면 continue

			pq.push({next.to, nextCost});	// 다음 탐색에 사용
			parent[next.to] = curr.to;	// 경로 저장
			cost[next.to] = nextCost;	// 비용 갱신
		}
	}

	int destory = N;	// destory: 파괴될 도로의 시작 노드
	while(true){
		if(parent[destory] == 0) break;	// 시작 지점이라면 break

		dijkstra(destory, parent[destory]);	// 최단 거리에 있는 노드를 하나씩 파괴

		destory = parent[destory];	// 다음 노드로 이동
	}

	return;
}

void input(){

	std::cin >> N >> M;

	// 벡터 공간 할당
	edge.assign(N + 1, std::vector<Edge>(0, {0, 0}));
	parent.assign(N + 1, 0);

	for(int i=0; i<M; ++i){
		int x, y, z;	// x, y: 연결되어 있는 정점, z: 도로를 지나는데 걸리는 시간
		std::cin >> x >> y >> z;
		
		edge[x].push_back({y, z});
		edge[y].push_back({x, z});	// 양방향 도로
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	std::cout << ans;

	return 0;
}