/*
build_frame [x, y, a, b]
	x, y : 가로, 세로
	a : 0(기둥), 1(보)
	b : 0(삭제), 1(설치)
규칙
1. 기둥은 바닥 위에 있거나 보의 한쪽 끝 부분 위에 있거나, 또는 다른 기둥 위에 있어야 합니다.
2. 보는 한쪽 끝 부분이 기둥 위에 있거나, 또는 양쪽 끝 부분이 다른 보와 동시에 연결되어 있어야 합니다.

만약, 작업을 수행한 결과가 조건을 만족하지 않는다면 해당 작업은 무시됩니다.

구조물은 교차점 좌표를 기준으로 보는 오른쪽, 기둥은 위쪽 방향으로 설치 또는 삭제합니다.
구조물이 겹치도록 설치하는 경우와, 없는 구조물을 삭제하는 경우는 입력으로 주어지지 않습니다.

최종 구조물 형태 [x, y, a]
	x, y : 기둥, 보의 교차점 좌표 = 가로, 세로
	a : 0(기둥), 1(보)
	x좌표 기준 오름차순 정렬 후 x가 같으면 y좌표 기준 오름차순 정렬
	x, y가 모두 같은 경우 기둥이 보보다 앞에
*/
// https://wadekang.tistory.com/28 참고..
// 무엇을 잘못 짰는가..
// 기둥이나 보 확인은 잘 했는데 이상하게 정렬해서 넣으려다가 실패함...
#include <bits/stdc++.h>

using namespace std;

// 오류 검증용 함수 2개
bool install_item(int n, vector<vector<vector<int>>>& Map, int x, int y, int a) {
	if (a == 0) { // 기둥 설치
		if (y == 0) return true; // 바닥위에 있거나
		if (x > 0 && Map[x - 1][y][1]) return true; // 보의 오른쪽 끝 위
		if (y < n && Map[x][y][1]) return true; // 보의 왼쪽 끝 위
		if (y > 0 && Map[x][y - 1][0]) return true; // 다른 기둥 위
	}
	else { // 보 설치
		if (y > 0 && Map[x][y - 1][0]) return true; // 왼쪽 끝 아래 기둥
		if (x < n && y > 0 && Map[x + 1][y - 1][0]) return true; // 오른쪽 끝 아래 기둥
		if (x > 0 && x < n && Map[x - 1][y][1] && Map[x + 1][y][1]) return true; // 양쪽 끝 부분 다른 보
	}
	return false;
}

bool remove_item(int n, vector<vector<vector<int>>>& Map, int x, int y, int a) {
	Map[x][y][a] = 0;

	if (a == 0) { // 기둥 삭제
		// 위에 기둥 있을 때, 설치 가능?
		if (y < n && Map[x][y + 1][0] && !install_item(n, Map, x, y + 1, 0)) return false;

		// 위에 보 있을 때, 설치 가능?
		if (y < n && Map[x][y + 1][1] && !install_item(n, Map, x, y + 1, 1)) return false;
		if (x > 0 && y < n && Map[x - 1][y + 1][1] && !install_item(n, Map, x - 1, y + 1, 1)) return false;
	}
	else {
		// 위에 기둥 있을 때, 설치 가능?
		if (Map[x][y][0] && !install_item(n, Map, x, y, 0)) return false;
		if (x < n && Map[x + 1][y][0] && !install_item(n, Map, x + 1, y, 0)) return false;

		// 다른 보와 연결되어 있을 때, 설치 가능?
		if (x > 0 && Map[x - 1][y][1] && !install_item(n, Map, x - 1, y, 1)) return false;
		if (x < n && Map[x + 1][y][1] && !install_item(n, Map, x + 1, y, 1)) return false;
	}

	return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;
	vector <vector<vector<int>>> Map(n + 1, vector<vector<int>>(n + 1, vector<int>(2, 0))); // 기둥은 n에도 놓을 수 있음.
	// [0] : 기둥
	// [1] : 보

	for (vector<int>& frame : build_frame) {
		int x, y, a, b;
		x = frame[0], y = frame[1], a = frame[2], b = frame[3];

		// 규칙 확인
		if (b == 1) { // 설치
			if (a == 0) { // 기둥
				// 바닥 위에 있거나 보의 한쪽 끝 부분 위에 있거나 또는 다른 기둥 위이거나.
				// if(install_item(n, Map, x, y, a)) { // 확인용 코드
				if (y == 0 || (x > 0 && Map[x-1][y][1]) || Map[x][y][1] || Map[x][y - 1][0]) {
					Map[x][y][a] = 1;
				}
			}
			else { // 보
				// 보는 한쪽 끝 부분이 기둥 위에 있거나,양쪽 끝 부분이 다른 보와 동시에 연결되어 있는지
				// if (install_item(n, Map, x, y, a)) { // 확인용 코드
				if ((Map[x][y - 1][0] || Map[x + 1][y - 1][0]) || (x > 0 && Map[x - 1][y][1] && Map[x + 1][y][1])) {
					Map[x][y][a] = 1;
				}
			}
		}
		else { // 삭제
			if (a == 0) { // 기둥
				// if (!remove_item(n, Map, x, y, a)) Map[x][y][a] = 1; // 확인용 코드
				bool chk = true;

				// 기둥 위에 보가 있거나 =>
				if (Map[x][y + 1][1]) { // right
					// 다른 한 쪽 끝이 기둥이거나, 양쪽 끝에 보가 있는지 확인
					if (!(Map[x + 1][y][0] || (x > 0 && Map[x - 1][y + 1][1] && Map[x + 1][y + 1][1]))) {
						chk = false;
					}
				}
				if (x > 0 && Map[x - 1][y + 1][1]) { // left
					// 기둥이 있거나, 양쪽 끝이 보인지 확인
					if (!(Map[x - 1][y][0] || (x > 1 && Map[x - 2][y + 1][1] && Map[x][y + 1][1]))) {
						chk = false;
					}
				}
				// 기둥 위에 기둥이 있거나 => 
				if (Map[x][y + 1][0]) {
					// 다른 보가 있는지 확인
					if (!(Map[x][y + 1][1] || (x > 0 && Map[x - 1][y + 1][1]))) {
						chk = false;
					}
				}

				if (chk) { // 삭제 가능
					Map[x][y][a] = 0;
				}
			}
			else { // 보
				// if (!remove_item(n, Map, x, y, a)) Map[x][y][a] = 1; // 확인용 코드
				bool chk = true;
				// 보 양 옆에 보가 있거나 =>
				if(x > 0 && Map[x - 1][y][1]) { // left
					if (!(Map[x - 1][y - 1][0] || Map[x][y - 1][0])) { // 보 밑에 기둥 확인
						chk = false;
					}
				}
				if (Map[x + 1][y][1]) { // right
					if (!(Map[x + 1][y - 1][0] || (x + 2 <= n && Map[x + 2][y - 1][0]))) { // 보 밑에 기둥 확인
						chk = false;
					}
				}
				// 보 양 옆에 기둥이 있거나 => {
				if (Map[x][y][0]) {
					// 기둥 밑에 기둥 확인 + 다른 보 확인
					if (!(Map[x][y - 1][0] || (x > 0 && Map[x - 1][y][1]))) {
						chk = false;
					}
				}
				if (Map[x + 1][y][0]) {
					// 기둥 밑에 기둥 확인 + 다른 보 확인
					if (!(Map[x + 1][y - 1][0] || Map[x + 1][y][1])) {
						chk = false;
					}
				}

				if (chk) { // 삭제 가능
					Map[x][y][a] = 0;
				}
			}
		}
	}

	/*
	// 이게 왜 안 된 거지..
	// 설치 => 삭제 => 설치하면 2번 들어가네.. ㅋㅋ ㅠㅠㅠㅠㅠㅠㅠ
	for (vector<int>& frame : build_frame) {
		int x, y, a, b;
		x = frame[0], y = frame[1], a = frame[2], b = frame[3];
		if (b == 0) continue; // 삭제는 스킵
		if (Map[x][y][a]) {
			answer.push_back({ x,y,a });
		}
	}

	sort(begin(answer), end(answer), [](vector<int>& first, vector<int>& second) {
		// x좌표 기준으로 오름차순 정렬하며, x좌표가 같을 경우 y좌표 기준으로 오름차순 정렬
		// x, y좌표가 모두 같은 경우 기둥이 보보다 앞에 오면 됩니다.
		if (first[0] == second[0] && first[1] == second[1]) {
			return first[2] < second[2];
		}
		else if (first[0] == second[0]) {
			return first[1] < second[1];
		}
		return first[0] < second[0];
	});
	*/
	for (int x{}; x <= n; ++x) {
		for (int y{}; y <= n; ++y) {
			if (Map[x][y][0]) answer.push_back({ x,y,0 });
			if (Map[x][y][1]) answer.push_back({ x,y,1 });
		}
	}

	return answer;
}

template <typename T>
void Print(vector<vector<T>>& vec) {
	for (auto& row : vec) {
		cout << '[';
		for (auto& v : row) {
			cout << v << ' ';
		}
		cout << "], ";
	}
	cout << '\n';
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	vector<vector<int>> ans1 = solution(5, {{1, 0, 0, 1}, {1, 1, 1, 1}, {2, 1, 0, 1}, {2, 2, 1, 1}, {5, 0, 0, 1}, {5, 1, 0, 1}, {4, 2, 1, 1}, {3, 2, 1, 1}});
	Print(ans1);

	vector<vector<int>> ans2 = solution(5, {{0, 0, 0, 1}, {2, 0, 0, 1}, {4, 0, 0, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}, {2, 1, 1, 1}, {3, 1, 1, 1}, {2, 0, 0, 0}, {1, 1, 1, 0}, {2, 2, 0, 1}});
	Print(ans2);

	return 0;
}