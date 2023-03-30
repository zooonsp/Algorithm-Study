#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

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

// d l r u
string makeAnswer(vector<int>& cnt, int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    for (int i = 0; i < k; ++i) {
        if (cnt[0] > 0 && x < n) {
            x++;
            cnt[0]--;
            answer += "d";
        }
        else if (cnt[1] > 0 && y > 1) {
            y--;
            cnt[1]--;
            answer += "l";
        }
        else if (cnt[2] > 0 && y < m) {
            y++;
            cnt[2]--;
            answer += "r";
        }
        else if (cnt[3] > 0 && x > 1) {
            x--;
            cnt[3]--;
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
        if (r - x >= 0) cnt[0] += r - x; // down
        else cnt[3] += x - r; // up
        if (c - y >= 0) cnt[2] += c - y; // right
        else cnt[1] += y - c; // left

        if (manhattanDist == k) { // 최단거리 -> 가장 빠른 것
            for (int i = 0; i < 4; ++i) {
                while (cnt[i]) {
                    if (i == 0) answer += "d";
                    else if (i == 1) answer += "l";
                    else if (i == 2) answer += "r";
                    else answer += "u";
                    --cnt[i];
                }
            }
        }
        else {
            int halfLeft = (k - manhattanDist) / 2;
            // 왜 꼭 정확히 반으로 나눠야 한다고 생각했을까..
            // 3 3 0 0
            // 2 2 1 1
            // 1 1 2 2
            // 0 0 3 3
            for (int j = 0; j <= halfLeft; ++j) {
                vector<int> tempCnt(begin(cnt), end(cnt));
                tempCnt[0] += j;
                tempCnt[3] += j;
                tempCnt[1] += halfLeft - j;
                tempCnt[2] += halfLeft - j;

                string str = makeAnswer(tempCnt, n, m, x, y, r, c, k);
                if (answer == "") answer = str;
                else answer = min(answer, str);
            }
        }
    }
    return answer;
}