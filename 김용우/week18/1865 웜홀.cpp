#include <iostream>
#include <vector>

const int INF = 21e8;	// INF: 나올 수 없는 값

struct Edge{	// Edge: 도로, 웜홀 정보
	int to, time;	// to: 연결되어 있는 지점 번호, time: 시간
};

int N, M, W;	// N: 지점의 수, M: 도로의 개수, W: 웜홀의 개수
std::vector<std::vector<Edge>> v;	// v[i][j]: i 지점과 연결되어 있는 j 번째 도로 정보
std::vector<int> nodeTime;	// nodeTime[i]: i 지점에 도착할 수 있는 최소 시간
bool cycle;	// cycle: 사이클 여부 -> 사이클이 있으면 true

void solution(){

	nodeTime.assign(N, INF);	// 지점 정보 초기화
	cycle = false;

	for(int j=0; j<N; j++){	// N 번 반복
		for(int cur=0; cur<N; cur++){	// cur: 현재 지점
			for(int k=0; k<v[cur].size(); k++){	// k: 현재 지점에 연결되어 있는 도로에 대하여 반복
				Edge edge = v[cur][k];	// edge: 도로 정보

				if(nodeTime[edge.to] > nodeTime[cur] + edge.time){	// 이전 시간보다 더 적은 시간이 걸리는 경우
					nodeTime[edge.to] = nodeTime[cur] + edge.time;	// 갱신

					if(j == N - 1) cycle = true;	// N 번째 반복에도 갱신된다면 사이클이 있음
				}
			}
		}
	}	

	return;
}

void input(){

	std::cin >> N >> M >> W;

	v.assign(N, std::vector<Edge>(0, {0, 0}));	// 도로 정보 공간 할당

	for(int i=0; i<M; i++){
		int from, to, time;	// from: 시작 지점, to: 도착 지점, time: 소요 시간
		std::cin >> from >> to >> time;
		v[from - 1].push_back({to - 1, time});
		v[to - 1].push_back({from - 1, time});	// 도로는 양방향 연결
	}

	for(int i=0; i<W; i++){
		int from, to, time;	// from: 시작 지점, to: 도착 지점, time: 소요 시간
		std::cin >> from >> to >> time;
		v[from - 1].push_back({to - 1, -time});	// 웜홀은 단방향 연결
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;	// T: 테스트 케이스 수
	std::cin >> T;

	for(int tc=0; tc<T; tc++){
		input();

		solution();

		std::cout << (cycle ? "YES" : "NO") << '\n';	// 사이클이 있으면 YES, 없으면 NO
	}
	

	return 0;
}