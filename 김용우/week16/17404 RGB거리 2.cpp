#include <iostream>
#include <vector>
#include <algorithm>

struct Cost{
	int RGB[3];	// RGB[i]: i가 0 이면 빨강, 1 이면 초록, 2 이면 파랑
};

int N;	// N: 집의 수
std::vector<Cost> cost;	// cost[i]: i 번째 집을 빨강, 초록, 파랑으로 칠하는 비용
std::vector<Cost> DP;	// DP[i]: i 번째 집을 칠하는 비용의 최솟값
int ans = 21e8;	// ans: 모든 집을 칠하는 비용의 최솟값

void sol(){

	DP.resize(N);

	for(int i=0; i<3; i++){	// i 색으로 0 번 집을 칠한 경우 -> 0: 빨강, 1: 초록, 2: 파랑
		
		for(int j=0; j<3; j++){
			if(i == j) DP[0].RGB[j] = cost[0].RGB[j];	// i 색 칠함
			else DP[0].RGB[j] = 21e8;	// 다른 색은 최댓값
		}

		// i 번 집의 색은 i - 1번 집의 색과 같지 않아야 함
		for(int j=1; j<N; j++){
			DP[j].RGB[0] = cost[j].RGB[0] + std::min(DP[j-1].RGB[1], DP[j-1].RGB[2]);	// 빨강으로 색칠
			DP[j].RGB[1] = cost[j].RGB[1] + std::min(DP[j-1].RGB[0], DP[j-1].RGB[2]);	// 초록으로 색칠
			DP[j].RGB[2] = cost[j].RGB[2] + std::min(DP[j-1].RGB[0], DP[j-1].RGB[1]);	// 파랑으로 색칠
		}
		for(int j=0; j<3; j++){
			if(i==j) continue;	// N - 1 번 집이 0 번 집과 같은 색인 경우 continue
			else ans = std::min(ans, DP[N-1].RGB[j]);	// 모든 집을 칠하는 비용의 최솟값 갱신
		}
	}

	return;
}

void input(){

	std::cin >> N;

	cost.resize(N);

	for(int i=0; i<N; i++){
		int R, G, B;	// R: 집을 빨강으로 칠하는 비용, G: 집을 초록으로 칠하는 비용, B: 집을 파랑으로 칠하는 비용
		std::cin >> R >> G >> B;
		cost[i] = {R, G, B};
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << ans;

	return 0;
}