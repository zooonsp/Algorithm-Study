#include <string>
#include <vector>
#include <queue>

struct Coordinate {  // Coordinate: 좌표
    int y, x;   // y, x: 좌표
};

struct Robot {  // Robot: 로봇의 정보
    int time;   // time: 이동 시간
    int y, x;   // y, x: 좌표
    int dir;    // dir: 로봇의 다른 부위의 상대 위치
};

// 우 하 좌 상
int dirY[] = { 0, 1, 0, -1 };
int dirX[] = { 1, 0, -1, 0 };

// 회전 반경 검사
Coordinate aClock[] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };   // aClock[i]: i 방향을 기준으로 시계 방향으로 회전할 경우 필요한 공간
Coordinate countClock[] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };   // countClock[i]: i 뱡향을 기준으로 반시계 방향으로 회전할 경우 필요한 공간

int bfs(std::vector<std::vector<int>>& board, int N) {  // board[i][j]: i 행 j열의 정보 -> 0 빈칸 1 벽, N: 지도의 한 변의 길이

    std::vector<std::vector<std::vector<bool>>> visited;    // visited[i][j][k]: i 행 j 열에 로봇의 다른 부위의 상대 위치가 k 방향을 향하는 경우를 탐색했다면 true
    std::queue<Robot> q;    // q: 로봇의 상태를 넣을 큐

    visited.assign(N, std::vector<std::vector<bool>>(N, std::vector<bool>(4, false)));  // 벡터 공간 할당 visited[N][N][4]

    // 로봇의 초기 위치
    q.push({ 0, 0, 0, 0 });
    visited[0][0][0] = true;

    q.push({ 0, 0, 1, 2 });
    visited[0][1][2] = true;

    while (!q.empty()) {
        Robot curr = q.front(); // curr: 기준으로 할 로봇의 부위
        q.pop();

        if (curr.y == N - 1 && curr.x == N - 1) return curr.time;    // 도착

        // 회전
        int rotate = 1; // rotate: 로봇의 회전 방향 -> 1 반시계 -1 시계
        for (int dir = 0; dir < 2; ++dir) {   // dir: 90도로 시계, 반시계 회전 가능
            rotate *= -1;   // 시계부터 탐색
            int nextDir = (curr.dir + rotate + 4) % 4;  // nextDir: 회전 후 로봇의 다른 위치를 기준으로의 위치
            Robot next = { curr.time + 1, curr.y + dirY[curr.dir] + dirY[nextDir], curr.x + dirX[curr.dir] + dirX[nextDir], (nextDir + 2) % 4 };  // next: 회전한 후 변화된 위치

            if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) continue;    // 범위 벗어나면 continue
            if (visited[next.y][next.x][next.dir]) continue; // 이미 확인한 경우라면 continue

            if (board[next.y][next.x]) continue; // 벽이 있는 경우 continue
            // 회전 반경 확인
            if (rotate == -1) {   // 시계
                if (board[curr.y + aClock[curr.dir].y][curr.x + aClock[curr.dir].x]) continue;
            }
            else {   // 반시계
                if (board[curr.y + countClock[curr.dir].y][curr.x + countClock[curr.dir].x]) continue;
            }

            // 방문 체크
            visited[next.y][next.x][next.dir] = true;
            visited[curr.y + dirY[curr.dir]][curr.x + dirX[curr.dir]][(next.dir + 2) % 4] = true;

            // 다음 방문을 위하여 큐에 넣음
            q.push(next);
            q.push({ next.time, curr.y + dirY[curr.dir], curr.x + dirX[curr.dir], (next.dir + 2) % 4 });
        }

        // 진행방향으로
        for (int dir = 0; dir < 4; ++dir) {
            Robot next = { curr.time + 1, curr.y + dirY[dir], curr.x + dirX[dir], curr.dir }; // next: 현재 부위의 다음 이동 위치

            if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) continue;    // 범위 벗어나면 continue
            if (next.y + dirY[next.dir] < 0 || next.x + dirX[next.dir] < 0 || next.y + dirY[next.dir] >= N || next.x + dirX[next.dir] >= N) continue;    // 로봇의 다른 부위가 범위 벗어나면 continue

            // 이미 확인한 경우는 continue
            if (visited[next.y][next.x][next.dir]) continue;
            if (visited[next.y + dirY[next.dir]][next.x + dirX[next.dir]][(next.dir + 2) % 4]) continue;

            // 벽이 있어 갈 수 없는 경우 continue
            if (board[next.y][next.x]) continue;
            if (board[next.y + dirY[next.dir]][next.x + dirX[next.dir]]) continue;

            // 방문 체크
            visited[next.y][next.x][next.dir] = true;
            visited[next.y + dirY[next.dir]][next.x + dirX[next.dir]][(next.dir + 2) % 4] = true;

            // 다음 방문을 위하여 큐에 넣음
            q.push(next);
            q.push({ next.time, next.y + dirY[next.dir], next.x + dirX[next.dir], (next.dir + 2) % 4 });
        }
    }

    return -1;  // 답이 없는 경우는 없으므로 -1로 return 되는 경우는 없음
}

int solution(std::vector<std::vector<int>> board) {
    int answer = 0;

    answer = bfs(board, board.size());

    return answer;
}