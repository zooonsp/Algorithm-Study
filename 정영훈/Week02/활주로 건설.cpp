// 가로 또는 세로 방향으로 건설 가능성 확인
// 높이가 동일한 구간에서 건설 가능
// 경사로는 높이 차이가 1 이고 낮은 지형의 높이가 동일하게 경사로의 길이만큼 연속되는 곳에 설치 할 수 있다.
// 동일한 셀에 두 개 이상의 경사로를 겹쳐서 사용할 수 없다.

#include <iostream>
#include <cstdio>
#include <vector>

const int LEFT = 1;

using namespace std;
int N, X, ans{}; // 맵의 크기, 경사로의 길이, 답

bool ChkRow(vector<vector<int>>& Map, int i) {
	int last_height{ Map[i][0] }, length{ 1 }, dir{};
	for (int j = 1; j < N; ++j) {
		if (last_height > Map[i][j]) { // LEFT
			if (Map[i][j] + 1 != last_height) return false; // 높이 차이가 1개보다 더 큰 경우
			if (dir && length < X) return false; // 방향이 있을 때
			// 새로 쌓아야 함.
			dir = LEFT;
			last_height = Map[i][j];
			length = 1;
		}
		else if (last_height < Map[i][j]) { // RIGHT
			if (Map[i][j] != last_height + 1) return false;
			if (length < X) return false; // 방향이 있든 없든
			//if (dir && length < X) return false; // 방향이 있을 때
			// dir = RIGHT; // 필요 없을 듯?
			last_height = Map[i][j];
			length = 1;
		}
		else {
			length++;
			if (dir) { // 방향이 있는 경우 개수 넘어가면 길이 초기화
				if (length == X) {
					dir = 0;
					length = 0;
				}
			}
		}
	}
	if (dir && length < X) return false;
	return true;
}

int main() {
	int T;
	// freopen("input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		cin >> N >> X; // 지도 한 변의 크기, 경사로의 길이
		vector<vector<int>> Map(N, vector<int>(N, 0));
		vector<vector<int>> MapTranspose(N, vector<int>(N, 0));
		ans = 0;

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> Map[i][j];
				MapTranspose[j][i] = Map[i][j];
			}
		}

		for (int i = 0; i < N; ++i) {

			// 행
			if (ChkRow(Map, i)) ++ans;

			// 열
			if (ChkRow(MapTranspose, i)) ++ans;

		}

		cout << "#" << tc << ' ' << ans << endl;
	}

	return 0;
}