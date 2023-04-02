#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum class Dir : int {
	Down, Left, Right, Up
};

constexpr int Down = static_cast<int>(Dir::Down);
constexpr int Left = static_cast<int>(Dir::Left);
constexpr int Right = static_cast<int>(Dir::Right);
constexpr int Up = static_cast<int>(Dir::Up);

// https://unikys.tistory.com/376
// https://blockdmask.tistory.com/405

int ManhattanDistance(int x, int y, int r, int c) {
	int manhattanDistX = x - r < 0 ? r - x : x - r;
	int manhattanDistY = y - c < 0 ? c - y : y - c;
	return manhattanDistX + manhattanDistY;
}

// n, m : 행, 열
// x, y : 출발
// r, c : 탈출
// k : 
// (x, y) -> (r, c)

string makeAnswer(string& before, vector<int>& cnt, int n, int m, int x, int y, int r, int c, int k) {
	// before : 이미 앞에서 구한 답
	string answer = "";
	for (int i = 0; i < k; ++i) {
		// 더 빨라질 줄 알았는데 더 느림.
		// if (before.length()!=0 && before.compare(answer) < 0) return "z"; // 이전에 구한 답이 더 빠름.
		// 아마 compare하는 과정에서 시간을 더 먹는 듯함.
		if (cnt[Down] > 0 && x < n) {
			x++;
			cnt[Down]--;
			answer += "d";
		}
		else if (cnt[Left] > 0 && y > 1) {
			y--;
			cnt[Left]--;
			answer += "l";
		}
		else if (cnt[Right] > 0 && y < m) {
			y++;
			cnt[Right]--;
			answer += "r";
		}
		else if (cnt[Up] > 0 && x > 1) {
			x--;
			cnt[Up]--;
			answer += "u";
		}
	}
	return answer;
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
	string answer = "";
	int manhattanDist = ManhattanDistance(x, y, r, c);
	if (manhattanDist > k || (manhattanDist & 1) != (k & 1)) {
		answer = "impossible";
	}
	else if (manhattanDist <= k) {
		vector<int> cnt(4, 0);
		// d l r u
		// r - x (u, d)
		// c - y (l, r)
		if (r - x >= 0) cnt[Down] += r - x; // down
		else cnt[Up] += x - r; // up
		if (c - y >= 0) cnt[Right] += c - y; // right
		else cnt[Left] += y - c; // left

		if (manhattanDist == k) { // 최단거리 -> 가장 빠른 것
			for (int i = 0; i < 4; ++i) {
				while (cnt[i]) {
					if (i == Down) answer += "d";
					else if (i == Left) answer += "l";
					else if (i == Right) answer += "r";
					else if (i == Up) answer += "u";
					--cnt[i];
				}
			}
		}
		else {
			int halfLeft = (k - manhattanDist) / 2;
			// 왜 꼭 정확히 반으로 나눠야 한다고 생각했을까.. 
			// halfLeft가 3인 경우에..
			// 3 3 0 0
			// 2 2 1 1
			// 1 1 2 2
			// 0 0 3 3
			for (int j = 0; j <= halfLeft; ++j) {
				vector<int> tempCnt(begin(cnt), end(cnt));
				tempCnt[Down] += j;
				tempCnt[Up] += j;
				tempCnt[Left] += halfLeft - j;
				tempCnt[Right] += halfLeft - j;

				string str = makeAnswer(answer, tempCnt, n, m, x, y, r, c, k);
				if (answer == "") answer = str;
				else answer = min(answer, str);
			}
		}
	}
	return answer;
}