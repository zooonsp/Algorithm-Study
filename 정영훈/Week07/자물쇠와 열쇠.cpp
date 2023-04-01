#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N{}, M{}, homCnt{}; // lock 크기, key의 크기, 메꿔야하는 홈 개수

/*
(0, 0) -> (0, 2) / (1, 0) -> (0, 1) / (2, 0) -> (0, 0)
(0, 1) -> (1, 2) / (1, 1) -> (1, 1) / (2, 1) -> (1, 0)
(0, 2) -> (2, 2) / (1, 2) -> (2, 1) / (2, 2) -> (2, 0)

(x, y) -> (y, N - 1 - x)
*/
// key를 오른쪽 90도로 rotate
void Rotate(vector<vector<int>>& key) {
	vector<vector<int>> tempKey(begin(key), end(key));

	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < M; ++j) {
			key[j][M - 1 - i] = tempKey[i][j];
		}
	}
}

// fi, fj위치에서 유효한 열쇠인지 확인하기
// 자물쇠의 홈 부분(0)을 다 채워야 하고
// 열쇠의 돌기(1)와 자물쇠(1)의 돌기가 만나서는 안 됨.
bool CheckNow(vector<vector<int>>& key, vector<vector<int>>& fullLock, int fi, int fj) {
	int cnt{};
	for (int i{}; i < M; ++i) {
		for (int j{}; j < M; ++j) {
			if (!fullLock[fi + i][fj + j]) { // 현재 위치가 홈이라면
				++cnt;
				if (!key[i][j]) return false; // 근데 key도 홈이야
			}
			else if (fullLock[fi + i][fj + j] == 1) { // 현재 위치가 돌기라면
				if (key[i][j] == 1) return false; // 근데 key도 돌기야
			}
		}
	}
	if (cnt == homCnt) return true; // 진짜 다 채움
	else return false;

}

// fullLock : lock을 3배 확장
// 유효한 열쇠가 하나라도 있는지 확인
bool IsValidKey(vector<vector<int>>& key, vector<vector<int>>& fullLock) {
	bool ret{ false };
	for (int fi{}; fi <= 3 * N - M; ++fi) {
		for (int fj{}; fj <= 3 * N - M; ++fj) {
			// fullLock의 위치

			ret = CheckNow(key, fullLock, fi, fj);
			if (ret) return true;

		}
	}
	return ret;
}

// key : M X M
// lock : N X N 
// M은 항상 N 이하
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	bool answer = true;

	N = static_cast<int>(lock.size());
	M = static_cast<int>(key.size());
	vector<vector<int>> fullLock(3 * N, vector<int>(3 * N, 2)); // 상관없는 값으로 초기화
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			fullLock[N + i][N + j] = lock[i][j];
			if (!lock[i][j]) ++homCnt; // 홈 개수 세기
		}
	}

	// 맞는 key인지 확인 - no rotate
	answer = IsValidKey(key, fullLock);

	if (!answer) {
		for (int i = 0; i < 3; ++i) {
            // 오른쪽으로 90도 돌려가면서 유효한 열쇠가 존재하는지 확인
			Rotate(key);
			answer = IsValidKey(key, fullLock);
			if (answer) break;
		}
	}

	return answer;
}


int main() {
	vector<vector<int>> key{ {0,0,0},{1,0,0},{0,1,1} };
	vector<vector<int>> lock{ {1,1,1},{1,1,0},{1,0,1} };

	//vector<vector<int>> key{ {0,0},{0,0} };
	//vector<vector<int>> lock{ {1,0,0},{1,0,0},{1,1,1} };

	cout << boolalpha << solution(key, lock) << '\n';
	return 0;
}