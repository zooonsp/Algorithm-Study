#include <iostream>


#include <string>
#include <vector>
#include <queue>

using namespace std;

/*

BFS 로 풀자

1. 로봇은 상하좌우 움직인다.
2. 로봇은 90도 회전이 가능하며 축이 2 개 이므로 로봇이 총 움직임이 가능한 가지수는 8이다.
3. 로봇은 90도 회전시 차지하는 2*2 블럭에 막힌 부분이 없어야한다.

가장 빨리 N * N 에 도달하는 경우를 찾아야 한다.

*/

struct coordi {
    int y, x;

    bool operator == (const coordi& next)const
    {
        if (y == next.y && x == next.x)
            return 1;

        return 0;
    }
};

const int MAX_BD = 111; // 보드 최대 크기
const int ry[] = { 1, -1, 0, 0 };
const int rx[] = { 0, 0, 1, -1 };

struct robo {
    coordi pt1, pt2;
    int angle; // 0 : 0도, 1: 90도, 수직 수평만 판단하고 pt1, pt2를 정렬하자
    int cnt; // 로봇이 이동한 횟수
};


int visitied[4][MAX_BD][MAX_BD] = { 0, }; // visited는 pt1 기준, [z][y][x] 중 z 는 angle 값

int solution(vector<vector<int>> board) {
    int ans = 0;
    int N = board.size();

    queue<robo> q;
    q.push({ {1,1},{1, 2}, 0, 0});
    visitied[0][1][1] = 1;

    while (!q.empty())
    {
        robo now = q.front();
        robo next;
        q.pop();

        // 도착
        if (now.pt2 == coordi{N, N})
        {
            ans = now.cnt;
            break;
        }

        // 상하좌우 이동
        for (int i = 0; i < 4; i++)
        {
            next = now;
            next.cnt++;

            next.pt1.y += ry[i];
            next.pt1.x += rx[i];
            next.pt2.y += ry[i];
            next.pt2.x += rx[i];

            if ( next.pt2.y > N || next.pt2.x > N ||
                next.pt1.y < 1 || next.pt1.x < 1) continue;

            if (visitied[next.angle][next.pt1.y][next.pt1.x] == 1) continue;

            if (board[next.pt1.y - 1][next.pt1.x - 1] == 1 ||
                board[next.pt2.y - 1][next.pt2.x - 1] == 1) continue;
            
            visitied[next.angle][next.pt1.y][next.pt1.x] = 1;
            q.push(next);
        }

        // 수평에서 수직으로 이동
        if(now.angle == 0)
        {
            if (now.pt2.y + 1 <= N) // 돌릴 공간이 board 넘는지 체크
            {
                if (board[now.pt1.y][now.pt1.x - 1] == 0 &&
                    board[now.pt1.y][now.pt2.x - 1] == 0) // 보드에 모두 빈공간 0 인지 체크
                {
                    if (visitied[1][now.pt1.y][now.pt1.x] == 0) // 이미 방문했는지 체크
                    {
                        visitied[1][now.pt1.y][now.pt1.x] = 1;
                        q.push({ now.pt1, {now.pt1.y + 1, now.pt1.x}, 1 , now.cnt + 1 });
                    }

                    if (visitied[1][now.pt2.y][now.pt2.x] == 0)
                    {
                        visitied[1][now.pt2.y][now.pt2.x] = 1;
                        q.push({ {now.pt1.y, now.pt2.x}, {now.pt1.y + 1, now.pt2.x}, 1 , now.cnt + 1});
                    }

                }
            }

            if (now.pt2.y - 1 > 0)
            {
                if (board[now.pt1.y - 2][now.pt1.x - 1] == 0 &&
                    board[now.pt1.y - 2][now.pt2.x - 1] == 0)
                {
                    if (visitied[1][now.pt1.y - 1][now.pt1.x] == 0)
                    {
                        visitied[1][now.pt1.y - 1][now.pt1.x] = 1;
                        q.push({ {now.pt1.y - 1, now.pt1.x}, now.pt1, 1 , now.cnt + 1});
                    }

                    if (visitied[1][now.pt2.y - 1][now.pt2.x] == 0)
                    {
                        visitied[1][now.pt2.y - 1][now.pt2.x] = 1;
                        q.push({ {now.pt2.y - 1, now.pt2.x}, now.pt2, 1 , now.cnt + 1});
                    }

                }
            }
        }
        // 수직에서 수평으로 이동
        else
        {
            if (now.pt2.x + 1 <= N) 
            {
                if (board[now.pt1.y - 1][now.pt1.x] == 0 &&
                    board[now.pt1.y - 1][now.pt2.x] == 0) 
                {
                    if (visitied[0][now.pt1.y][now.pt1.x] == 0) 
                    {
                        visitied[0][now.pt1.y][now.pt1.x] = 1;
                        q.push({ now.pt1, {now.pt1.y, now.pt1.x + 1}, 0 , now.cnt + 1 });
                    }

                    if (visitied[0][now.pt2.y][now.pt2.x] == 0)
                    {
                        visitied[0][now.pt2.y][now.pt2.x] = 1;
                        q.push({ now.pt2, {now.pt2.y, now.pt2.x + 1}, 0 , now.cnt + 1 });
                    }

                }
            }

            if (now.pt2.x - 1 > 0)
            {
                if (board[now.pt1.y - 1][now.pt1.x - 2] == 0 &&
                    board[now.pt1.y - 1][now.pt2.x - 2] == 0)
                {
                    if (visitied[0][now.pt1.y][now.pt1.x - 1] == 0)
                    {
                        visitied[0][now.pt1.y][now.pt1.x - 1] = 1;
                        q.push({ {now.pt1.y, now.pt1.x - 1}, now.pt1, 0 , now.cnt + 1 });
                    }

                    if (visitied[0][now.pt2.y][now.pt2.x - 1] == 0)
                    {
                        visitied[0][now.pt2.y][now.pt2.x - 1] = 1;
                        q.push({ {now.pt2.y, now.pt2.x - 1}, now.pt2, 0 , now.cnt + 1 });
                    }

                }
            }
        }
    }


    return ans;
}




int main()
{
    int ans = 0;
    solution({ {0, 0, 0, 1, 1},{0, 0, 0, 1, 0},{0, 1, 0, 1, 1},{1, 1, 0, 0, 1},{0, 0, 0, 0, 0 }});

    ans = cout << ans;
    return 0;
}