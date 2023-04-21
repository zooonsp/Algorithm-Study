#include <iostream>
#include <cstring>
#include <algorithm>

// Cell
// vitality와 hp가 모두 0이면 빈 상태
// vitality가 0보다 크고, hp가 0보다 크면 비활성 상태 -> hp를 1씩 감소 시킴
// vitality가 0보다 크고, hp가 0이면 번식 상태 -> 번식 후 hp에 vitality값을 넣고 vitality를 0으로 바꿈
// vitality가 0이고, hp가 0보다 크면 살이있는 상태 -> 죽으면 vitality를 -1로 변경 -> (0, 0) 상태에 주의
// vitality가 -1이면 죽은 상태

struct Cell {
	int vitality;	// vitality: 생명력 수치
	int hp;	// hp: 세포의 상태 지속 시간
};


int N, M, K;	// N: 세로 크기, M: 가로 크기, K: 배양 시간
Cell MAP[700][700];	// MAP[i][j]: i행 j열의 정보
int tmpMAP[700][700] = { 0, };	// tmpMAP[i][j]: 배양 시간에 i행 j열에 번식하는 줄기 세포의 생명력 수치
constexpr int standard = 310;	// standard: 기준점 (310, 310) -> (0, 0)
int ans;	// ans: K시간 후 배양 용기에 있는 살아있는 줄기 세포의 개수

int left, right, top, buttom;	// left, right, top, buttom: 세포가 존재하는 범위

// 방향 벡터
constexpr int dirY[] = { 0, 1, 0, -1 };
constexpr int dirX[] = { -1, 0, 1, 0 };

void update(int y, int x) {	// y, x: 줄기 세포의 위치
	left = std::min(left, x);	// 가장 왼쪽에 있는 줄기 세포의 위치
	right = std::max(right, x);	// 가장 오른쪽에 있는 줄기 세포의 위치
	top = std::min(top, y);	// 가장 위쪽에 있는 줄기 세포의 위치
	buttom = std::max(buttom, y);	// 가장 아래쪽에 있는 줄기 세포의 위치

	return;
}


void sol() {

	while (K > 0) {	// 배양 시간이 0보다 클 경우
		
		memset(tmpMAP, 0, sizeof(tmpMAP));	// 초기화 할 필요는 없음

		for (int j = top; j <= buttom; j++) {
			for (int i = left; i <= right; i++) {
				if (MAP[j][i].vitality == 0 && MAP[j][i].hp == 0) continue;	// 빈 상태
				if (MAP[j][i].vitality > 0 && MAP[j][i].hp > 0) {	// 비활성화 상태
					MAP[j][i].hp--;	// 상태 지속시간 감소
				}
				else if (MAP[j][i].vitality > 0 && MAP[j][i].hp == 0) {	// 번식 및 활성화
					int curCellVitality = MAP[j][i].vitality;	// curCellVitality: 현재 세포의 생명력 수치

					for (int dir = 0; dir < 4; dir++) {
						// newY, newX: 번식하는 줄기 세포의 위치
						int newY = j + dirY[dir];
						int newX = i + dirX[dir];

						if (MAP[newY][newX].vitality != 0 || MAP[newY][newX].hp != 0) continue;	// 번식 위치에 다른 세포가 있다면 continue

						update(newY, newX);	// 줄기 세포 범위 갱신

						if (tmpMAP[newY][newX] != 0) {	// 다른 줄기 세포가 이번 배양시간에 번식이 있었다면
							if (curCellVitality > tmpMAP[newY][newX]) {	// 생명력 수치가 높은 줄기 세포로 갱신
								tmpMAP[newY][newX] = curCellVitality;
							}
						}
						else {
							tmpMAP[newY][newX] = curCellVitality;
						}
					}
					MAP[j][i] = { 0, curCellVitality };	// 새포 상태 갱신, 비활성 상태 -> 활성 상태
				}
				if (MAP[j][i].vitality == 0 && MAP[j][i].hp > 0) {	// 활성 상태, vitality와 hp가 모두 0이면 빈 상태와 동일하기 때문에 주의
					if (MAP[j][i].hp == 1) {
						MAP[j][i].vitality = -1;	// 죽은 줄기 세포
						MAP[j][i].hp = 0;
					}
					else {
						MAP[j][i].hp--;	// 상태 지속 시간 감소
					}
				}
			}
		}

		// 번식한 세포 적용
		for (int j = top; j <= buttom; j++) {
			for (int i = left; i <= right; i++) {
				if (tmpMAP[j][i] == 0) continue;	// 번식한 줄기 세포가 없다면 continue
				int a = tmpMAP[j][i];
				MAP[j][i] = { a, a };	// 줄기 세포 번식 적용
				tmpMAP[j][i] = 0;	// 다음 배양 시간에 번식하는 줄기 세포를 위하여 초기화
			}
		}
		K--;
	}

	for (int j = top; j <= buttom; j++) {
		for (int i = left; i <= right; i++) {
			if (MAP[j][i].vitality == -1) continue;	// 죽은 줄기 세포는 continue
			if (MAP[j][i].vitality == 0 && MAP[j][i].hp == 0) continue;	// 줄기 세포 없면 continue
			ans++;
		}
	}

	return;
}

void input() {
	std::cin >> N >> M >> K;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			int a;	// a: 세포 정보
			std::cin >> a;
			if (a == 0) continue;	// 줄기 세포가 없는 위치면 초기화 값과 같으므로 continue
			else if (a > 0) {	// 줄기 세포가 있으면
				update(j + standard, i + standard);	// 줄기 세포 범위 갱신
				MAP[j + standard][i + standard].vitality = a;	// 줄기 세포 생명력 갱신
				MAP[j + standard][i + standard].hp = a;	// 줄기 세포 상태 갱신
			}		
		}
	}

	return;
}

void reset() {
	// 초기 상태 (0, 0)
	for (int j = 0; j < 700; j++) {
		for (int i = 0; i < 700; i++) {
			MAP[j][i].vitality = 0;
			MAP[j][i].hp = 0;
		}
	}

	// 초기 줄기 세포 범위 최대로 초기화
	left = 21e8;
	right = -21e8;
	top = 21e8;
	buttom = -21e8;

	// 살아있는 줄기 세포 수 0으로 초기화
	ans = 0;
	return;
}

int main() {
	int T;	// T: 테스트 케이스 수
	std::cin >> T;
	for (int tc = 1; tc <= T; tc++) {	// tc: 테스트 케이스 번호
		reset();
		input();
		sol();

		std::cout << '#' << tc << ' ' << ans << std::endl;

	}
	return 0;
}