#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>

int N;	// 격자 모양의 땅의 한 변의 길이
char MAP[1'001][1'001];	// MAP[i][j]: i행 J열의 알파벳
int AREA[1'001][1'001];	// AREA[i][j]: i행 J열의 영역 번호
int areaIdx;	// areaIdx: 영역의 개수
int areaSize[1'000'001];	// areaSize[i]: i 영역의 크기
std::unordered_map<int, int> um[1'000'001];	// s[i]: 영역 번호 i와 인접한 영역의 (영역 번호, 영역 넓이)
std::unordered_map<int, bool> startIdx, endIdx;	// startIdx: 시작 가능 영역 번호, endIdx: 도착 가능 영역 번호
int weight[1'000'001];	// weight[i]: i 영역까지 가는데 걸리는 최소 영역 넓이
int ans = 21e8;	// ans: 상원이가 사야하는 최소 칸의 수

struct Edge {
	int to;	// to: 갈 수 있는 영역 번호
	int weight;	// weight: 현재 영역까지 오는데 까지의 영역 넓이의 합

	bool operator < (Edge next) const {
		if (weight != next.weight) return weight > next.weight;	// 오름차순

		return false;
	}
};

std::vector<Edge> v[1000001];	// v[i]: i 영역과 연결되어 있는 영역의 번호

// 방향 벡터 -> 12시 방향부터 시계 방향
int dirY[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dirX[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void Dijkstra() {
	std::priority_queue<Edge> pq;	// pq: 영역의 넓이의 합을 오름차순으로 정렬한 우선 순위 큐

	for (int i = 0; i < areaIdx; i++)
		weight[i] = 21e8;	// 초기화

	for (std::unordered_map<int, bool>::iterator it = startIdx.begin(); it != startIdx.end(); it++) {
		int start = it->first;	// start: 시작 가능한 영역 번호

		weight[start] = areaSize[start];	// 시작 영역은 자신의 영역 넓이
		pq.push({ start, areaSize[start] });	// 우선 순위 큐에 넣음
	}
	
	while (!pq.empty()) {
		Edge cur = pq.top();	// cur: 현재 간선
		pq.pop();

		if (weight[cur.to] < cur.weight) continue;	// 현재 간선의 넓이의 합이 현재 넓이의 합보다 크면 continue
	
		int curToSize = v[cur.to].size();	// curToSize: 현재 간선으로 갈 수 있는 영역의 수
		for (int i = 0; i < curToSize; i++) {
			Edge next = v[cur.to][i];	// next: 다음 간선
			int nextWeight = weight[cur.to] + next.weight;	// nextWeight: 다음 간선을 사용하였을 때 갈 수 있는 영역의 넓이의 합

			if (weight[next.to] <= nextWeight) continue;	// 크거나 같으면 continue

			weight[next.to] = nextWeight;	// 최소 영역의 넓이 갱신

			pq.push({ next.to, nextWeight });
		}
	}	

	for (std::unordered_map<int, bool>::iterator it = endIdx.begin(); it != endIdx.end(); it++) {
		ans = std::min(ans, weight[it->first]);	// 도착 가능 영역에 대하여 최소 넓이의 합 조사
	}

	return;
}

void startEnd() {

	// 시작 지점 상, 우
	for (int i = 1; i < N; i++) {
		int curIdx = AREA[0][i];	// 상
				
		if (startIdx.find(curIdx) != startIdx.end()) continue;
		startIdx.insert({ curIdx, true });
	}
	for (int j = 0; j < N - 1; j++) {
		int curIdx = AREA[j][N - 1];	// 우
				
		if (startIdx.find(curIdx) != startIdx.end()) continue;
		startIdx.insert({ curIdx, true });
	}

	// 도착 지점 하, 좌
	for (int i = 0; i < N - 1; i++) {
		int curIdx = AREA[N - 1][i];	// 하
		
		if (endIdx.find(curIdx) != endIdx.end()) continue;
		endIdx.insert({ curIdx, true });
	}
	for (int j = 1; j < N; j++) {	// 좌
		int curIdx = AREA[j][0];
				
		if (endIdx.find(curIdx) != endIdx.end()) continue;
		endIdx.insert({ curIdx, true });
	}

	return;
}

void makeGraph() {

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (AREA[j][i] == -1) continue;	// 로미오나 줄리엣의 위치 continue
			
			int curIdx = AREA[j][i];	// curIdx: 현재 영역 변호

			for (int dir = 0; dir < 8; dir++) {	// 8 방향 탐색 -> 대각선으로도 길을 막을 수 있음
				int nextY = j + dirY[dir];	// nextY: 다음 y 좌표
				int nextX = i + dirX[dir];	// nextX: 다음 x 좌표

				if (nextY < 0 || nextX < 0 || nextY >= N || nextX >= N) continue;	// 범위 벗어나면 continue
				if (AREA[nextY][nextX] == curIdx) continue;	// 같은 영역이면 continue
				if (AREA[nextY][nextX] == -1) continue;	// 로미오나 줄리엣의 위치 continue

				int nextIdx = AREA[nextY][nextX];	// nextIdx: 인접한 영역 번호

				if (um[curIdx].find(nextIdx) != um[curIdx].end()) continue;

				um[curIdx].insert({ nextIdx, areaSize[nextIdx] });	// 인접한 영역 번호와 넓이 집합에 넣음		
			}			
		}
	}

	for (int i = 1; i < areaIdx; i++) {		
		for (std::unordered_map<int, int>::iterator it = um[i].begin(); it != um[i].end(); it++) {
			v[i].push_back({ it->first, it->second });	// 간선 정보 넣기
		}
	}

	return;
}

void divide() {
	
	AREA[0][0] = -1;	// 로미오의 위치
	AREA[N - 1][N - 1] = -1;	// 줄리엣의 위치
		
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (AREA[j][i] != 0) continue;	// 로미오와 줄리엣의 영역이거나, 이미 영역에 포함되었다면 continue;
			
			areaIdx++;	// 새로운 영역 발견 -> 영역 인덱스 증가 (1부터 사용)

			char curChar = MAP[j][i];	// curChar: 현재 영역의 알파벳
			int curIdx = areaIdx;	// curIdx: 현재 영역의 영역 번호
			std::queue<std::pair<int, int>> q;	// q: 연결되어있는 영역 탐색하기 위한 큐

			AREA[j][i] = curIdx;
			areaSize[curIdx]++;
			q.push({ j, i });

			while (!q.empty()) {
				int curY = q.front().first;	// curY: 현재 y 좌표
				int curX = q.front().second;	// curX: 현재 x좌표
				q.pop();

				for (int dir = 0; dir < 8; dir += 2) {	// 4방향 탐색
					int nextY = curY + dirY[dir];	// nextY: 다음 y 좌표
					int nextX = curX + dirX[dir];	// nextX: 다음 x 좌표

					if (nextY < 0 || nextX < 0 || nextY >= N || nextX >= N)	continue;	// 범위 벗어나면 continue
					if (AREA[nextY][nextX] != 0) continue;	// 이미 영역에 포함되어있다면 continue
					if (MAP[nextY][nextX] != curChar) continue;	// 같은 영역에 포함될 수 없으면 continue

					AREA[nextY][nextX] = curIdx;	// 영역 표시
					areaSize[curIdx]++;
					q.push({ nextY, nextX });
				}
			}
		}
	}
	
	areaIdx++;

	return;
}

void sol() {

	// 영역 분리
	divide();

	// 그래프 생성
	makeGraph();

	// 시작점과 끝점 탐색
	startEnd();

	// 다익스트라
	Dijkstra();

	return;
}

void input() {
	std::cin >> N;
	
	for (int j = 0; j < N; j++) {
		std::string s;	// s: 격자 한 행의 알파벳 정보
		std::cin >> s;
		for (int i = 0; i < N; i++) {
			MAP[j][i] = s[i];
		}
	}

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();
	sol();

	std::cout << ans;

	return 0;
}