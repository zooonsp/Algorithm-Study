#include <iostream>
#include <vector>

struct Edge{	// Edge: 간선 정보
	int to;	// to: 도착도시
	int time;	// time: 버스를 타고 이동하는데 걸리는 시간
};

int N, M;	// N: 도시의 개수, M: 버스 노선의 개수
std::vector<std::vector<Edge>> v;	// v[i][j]: i 도시에서 출발하는 j 번째 간선 정보
std::vector<long long> nodeTime;	// nodeTime[i]: i 도시로 가는 가장 빠른 시간
bool cycle = false;	// cycle: 사이클이 있으면 true

void solution(){

	nodeTime.assign(N, 1e18);	// 각 도시로 가는 가장 빠른 시간을 저장할 공간 할당

	nodeTime[0] = 0;	// 출발 도시

	for(int j=0; j<N; j++){	// N 번 반복

		for(int i=0; i<N; i++){	// N 개의 도시 i 도시에 대하여
			for(int k=0; k<v[i].size(); k++){	// i 도시에서 갈 수 있는 간선 정보
				Edge next = v[i][k];	// next: i 도시에 연결되어 있는 k 번째 간선 정보

				if(nodeTime[i] == 1e18) continue;	// i 도시에 방문한 적이 없으면 continue

				if(nodeTime[next.to] > nodeTime[i] + next.time){	// 이번에 탐색한 시간이 이전에 기록되어 있는 시간 보다 빠른 경우
					nodeTime[next.to] = nodeTime[i] + next.time;	// 가장 빠른 시간 갱신

					if(j == N -1) cycle = true;	// N 번째 탐색에서 값이 변하는 경우는 사이클이 있는 경우
				}
			}
		}
	}

	return;
}

void input(){

	std::cin >> N >> M;

	v.assign(N, std::vector<Edge>(0, {0, 0}));	// N 개의 도시에 대한 간선 정보 공간 할당

	for(int i=0; i<M; i++){
		int from, to, time;	// from: 시작도시, to: 도착도시, time: 버스를 타고 이동하는데 걸리는 시간 혹은 타임머신으로 시간을 되돌아가는 경우
		std::cin >> from >> to >> time;
		v[from - 1].push_back({to - 1, time});	// 도로와 타임머신은 단방향
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	if(cycle) std::cout << "-1";	// 시간을 무한히 오래 전으로 되돌릴 수 있다면 -1
	else{
		for(int i=1; i<N; i++){
			std::cout << (nodeTime[i] != 1e18 ? nodeTime[i] : -1) << '\n';	// i 번도시로 가는 가장 빠른 시간 출력, 만약 i 도시로 가는 경로가 없다면 -1 출력
		}
	}

	return 0;
}