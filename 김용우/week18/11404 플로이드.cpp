#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 10e8;	// INF: 무한대

int N, M;	// N: 도시의 수, M: 버스의 수
std::vector<std::vector<int>> arr;	// arr[i][j]: i 도시에서 j 도시로 가는데 필요한 최소 버스 비용

void sol() {
	for (int t = 1; t <= N; t++) {	// t: 경유지
		for (int a = 1; a <= N; a++) {	// a: 출발지
			for (int b = 1; b <= N; b++) {	// b: 도착지
				arr[a][b] = std::min(arr[a][b], arr[a][t] + arr[t][b]);	// 플로이드 -> 경유지를 지정해가며 최단 거리를 구함
			}
		}
	}

	return;
}

void input() {

	std::cin >> N >> M;

	arr.assign(N + 1, std::vector<int>(N + 1, 0));

	for (int j = 1; j <= N; ++j) {
		for (int i = 1; i <= N; ++i) {
			if (j == i) arr[j][i] = 0;	// 시작 도시와 도착 도시가 같은 경우 0
			else arr[j][i] = INF;	// j 도시에서 i 도시로 가는 비용 초기화
		}
	}

	for (int i = 0; i < M; i++) {
		int A, B, C;	// A: 출발 도시, B: 도착 도시, C: 비용
		std::cin >> A >> B >> C;
		arr[A][B] = std::min(arr[A][B], C);	// 시작 도시와 도착 도시를 연결하는 노선은 하나가 아닐 수 있으므로 최소값으로 갱신
	}
	
	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= N; i++) {
			if (arr[j][i] == INF) std::cout << "0 ";	// j 도시에서 i 도시로 갈수 없는 경우 0
			else std::cout << arr[j][i] << ' ';	// j 도시에서 i 도시로 갈 수 있는 최소 비용
		}
		std::cout << '\n';
	}

	return 0;
}