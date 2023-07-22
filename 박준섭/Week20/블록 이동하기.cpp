#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct node {
    int y, x, direction, cnt;
};

int visited[101][101][4];

int d[2][4] = {
    -1, 0, 1, 0,
    0, 1, 0, -1
};

int solution(vector<vector<int>> board) {

    int answer = 0;
    // MAP size 받기
    int n = board.size();

    queue<node> q;

    // 두 칸의 블록을 하나하나씩 따로 봄
    // 1번 축에서 오른쪽에 있는 것
    // 2번 축에서 왼쪽에 있는 것으로 시작
    q.push({ 1, 1, 1, 0 });
    q.push({ 1, 2, 3, 0 });

    visited[1][1][1] = 1;
    visited[1][2][3] = 1;

    while (!q.empty()) {

        node now1 = q.front(); q.pop();
        node now2;
        now2.y = now1.y + d[0][now1.direction];
        now2.x = now1.x + d[1][now1.direction];
        now2.direction = (now1.direction + 2) % 4;
        

        // 블록이 n, n에 도착한 경우
        if (now1.y == n && now1.x == n || now2.y == n && now2.x == n) {
            answer = now1.cnt;
            break;
        }

        for (int dir = 0; dir < 4; dir++) {
            int dy1 = now1.y + d[0][dir];
            int dx1 = now1.x + d[1][dir];
            int dy2 = now2.y + d[0][dir];
            int dx2 = now2.x + d[1][dir];

            // 블록이 맵 범위를 벗어나는 경우
            if (dy1 == 0 || dx1 == 0 || dy2 == 0 || dx2 == 0 ||
                dy1 > n || dx1 > n || dy2 > n || dx2 > n) continue;

            // 블록이 벽에 겹치는 경우
            if (board[dy1 - 1][dx1 - 1] == 1 || board[dy2 - 1][dx2 - 1] == 1) continue;

            // 움직여진 1번축을 기준으로 방문하지 않았을 경우
            if (visited[dy1][dx1][now1.direction] == 0) {
                visited[dy1][dx1][now1.direction] = 1;
                q.push({ dy1, dx1, now1.direction, now1.cnt + 1 });
            }

            // 움직여진 2번축을 기준으로 방문하지 않았을 경우
            if (visited[dy2][dx2][now2.direction] == 0) {
                visited[dy2][dx2][now2.direction] == 1;
                q.push({ dy2, dx2, now2.direction, now1.cnt + 1 });
            }

            // 수직으로 움직일 경우
            if ((now1.direction + 1) % 2 == dir % 2) {
                if (visited[now1.y][now1.x][dir] == 0) {
                    visited[now1.y][now1.x][dir] = 1;
                    q.push({ now1.y, now1.x, dir, now1.cnt + 1 });
                }

                if (visited[now2.y][now2.x][dir] == 0) {
                    visited[now2.y][now2.x][dir] = 1;
                    q.push({ now2.y, now2.x, dir, now1.cnt + 1 });
                }
            }
        }
    }
    return answer;
}
