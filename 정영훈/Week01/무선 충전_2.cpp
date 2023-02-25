// 접근 2. 매 시간마다 충전 가능한 충전기 구하기 16 * (20 ~ 100)
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

inline int Abs(int x, int y) { return x - y < 0 ? y - x : x - y; }

using namespace std;

struct charger {
	int x, y; // 위치
	int canCover; // 커버 가능 범위
	int capacity; // 충전량
	charger(int x, int y, int can, int cap) : x(x), y(y), canCover(can), capacity(cap) {}
	charger() {}
};

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
};

// 제자리, 상, 우, 하, 좌
int dx[]{ 0,-1,0,1,0 };
int dy[]{ 0,0,1,0,-1 };
int M{}, A{};
int aMove[110]{};
int bMove[110]{};
int ans{};
charger chargers[10]{};
coord Acoord(0, 0), Bcoord(0, 0);

// (1,1) 부터 시작

vector<int> PosA; // A가 충전가능한 충전기 index들
vector<int> PosB; // B가 충전가능한 충전기 index들

void Reset() {
	// PosA, PosB
	PosA.clear();
	PosB.clear();

	// coord
	Acoord.x = Acoord.y = 1;
	Bcoord.x = Bcoord.y = 10;

	// ans
	ans = 0;
}

void getPossiblePos() {
	for (int a = 0; a < A;++a) {
		int aDist = Abs(chargers[a].x, Acoord.x) + Abs(chargers[a].y, Acoord.y);
		if (aDist <= chargers[a].canCover) PosA.push_back(a);
		int bDist = Abs(chargers[a].x, Bcoord.x) + Abs(chargers[a].y, Bcoord.y);
		if (bDist <= chargers[a].canCover) PosB.push_back(a);
	}
}

void getMax() {
	int ret{};
	if (PosA.size() == 0 && PosB.size() == 0) { // 가능한 게 없음
		return;
	}
	else if (PosA.size() == 0) {
		// PosB에서 최대 구하기
		for (int& pb : PosB) {
			ret = max(ret, chargers[pb].capacity);
		}
	}
	else if (PosB.size() == 0) {
		// PosA에서 최대 구하기
		for (int& pa : PosA) {
			ret = max(ret, chargers[pa].capacity);
		}
	}
	else {
		// 둘 다 가능한 애들이 1개 이상
		for (int& pa : PosA) {
			for (int& pb : PosB) {
				if (pa == pb) { // 1개
					ret = max(ret, chargers[pa].capacity);
				}
				else {
					ret = max(ret, chargers[pa].capacity + chargers[pb].capacity);
				}
			}
		}
	}
	ans += ret;
	// 다음 가능한 점들을 위해 clear
	PosA.clear();
	PosB.clear();
}

int main() {
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		Reset();
		cin >> M >> A;
		for (int m = 0; m < M; ++m) cin >> aMove[m];
		for (int m = 0; m < M; ++m) cin >> bMove[m];

		for (int a = 0; a < A; ++a) {
			cin >> chargers[a].y >> chargers[a].x >> chargers[a].canCover >> chargers[a].capacity;
		}

		getPossiblePos();
		getMax(); // 시작점

		for (int t = 0; t < M; ++t) {
			Acoord.x += dx[aMove[t]];
			Acoord.y += dy[aMove[t]];
			Bcoord.x += dx[bMove[t]];
			Bcoord.y += dy[bMove[t]];

			getPossiblePos(); // A, B 좌표에 대해 충전 가능한 충전기들 정리
			getMax();
		}

		cout << "#" << test_case << " " << ans << endl;
	}

	return 0;
}