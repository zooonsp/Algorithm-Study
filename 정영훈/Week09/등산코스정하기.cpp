#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

constexpr int INF = 1'000'000'000;
// 등산코스에서 출입구는 처음과 끝에 한 번씩, 산봉우리는 한 번만 포함되어야 합니다

struct Edge {
	int to;
	int weight;
	Edge(int t, int w) : to(t), weight(w) {}
	bool operator< (const Edge& other) const { // PQ
		return this->weight > other.weight;
	}
};

using Graph = vector<vector<Edge>>;
Graph graph;

int gateDAT[50001]{}; // index : number, value : gate이면 1
int summitDAT[50001]{}; // index : number, value : summit이면 1

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
	vector<int> answer{-1, INF};
	graph = vector<vector<Edge>>(n + 1);

	for (auto& row : paths) { // 20만
		// 양방향
		graph[row[0]].push_back(Edge(row[1], row[2]));
		graph[row[1]].push_back(Edge(row[0], row[2]));
	}
	for (int& gate : gates) { // 5만
		gateDAT[gate] = 1;
	}
	for (int& summit : summits) { // 5만
		summitDAT[summit] = 1;
	}

	// summits -> 
	for (int & summit : summits) {
		vector<int> intensities(n + 1, INF);
		intensities[summit] = 0;
		priority_queue<Edge> pq;
		pq.push(Edge(summit, 0));
		
		while (!pq.empty()) {
			Edge now = pq.top(); pq.pop();

			if (now.weight != intensities[now.to]) continue;

			for (auto& e : graph[now.to]) {
				if (summitDAT[e.to]) continue; // 정상 또 가지 X
				int nextIntensity = max(intensities[now.to], e.weight);
				if (intensities[e.to] <= nextIntensity) continue;

				if (gateDAT[e.to]) { // gate
					intensities[e.to] = nextIntensity; // 갱신만
					if (answer[1] > intensities[e.to]) {
						answer[1] = intensities[e.to];
						answer[0] = summit;
					}
					if (answer[1] == intensities[e.to]) {
						if (answer[0] > summit) {
							answer[1] = intensities[e.to];
							answer[0] = summit;
						}
					}
				}
				else { // 쉼터
					intensities[e.to] = nextIntensity;
					if(answer[1] >= nextIntensity) pq.push(Edge(e.to, nextIntensity)); // 추가 방문
				}
			}
		}
	}
	return answer;
}