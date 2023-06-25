#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct coordi {
    int y, x;
};

struct Info {
    coordi pt;
    int cnt;
};

const int MAX_ANS = 21e8;

const int dy[] = { -1, 1, 0 ,0 };
const int dx[] = { 0, 0, -1, 1 };

vector<vector<int>> board_copy;
coordi pt_now;

int bfs(int permi_now)
{
    int visited[4][4] = { 0, };
    visited[pt_now.y][pt_now.x] = 1;
    queue<Info> q;
    q.push({ pt_now, 0 });

    while (!q.empty())
    {
        Info now = q.front();
        q.pop();

        if (board_copy[now.pt.y][now.pt.x] == permi_now)
        {
            board_copy[now.pt.y][now.pt.x] = 0;
            pt_now = now.pt;
            return now.cnt + 1;
        }

        for (int i = 0; i < 4; i++)
        {
            Info next = now;
            next.pt.y += dy[i];
            next.pt.x += dx[i];
            next.cnt++;

            if (next.pt.y < 0 || next.pt.y >= 4 ||
                next.pt.x < 0 || next.pt.x >= 4) continue;

            if (visited[next.pt.y][next.pt.x] == 0)
            {
                visited[next.pt.y][next.pt.x] = 1;
                q.push(next);
            }

            next.pt = now.pt; // 바로 다음에 카드가 있는경우를 고려하기 위해 다시 초기화 해주자

            // ctrl 눌렀을 때 bfs의 경우도 세어야한다.
            while (next.pt.y + dy[i] >= 0 && next.pt.y + dy[i] < 4 &&
                next.pt.x + dx[i] >= 0 && next.pt.x + dx[i] < 4)
            {
                next.pt.y += dy[i];
                next.pt.x += dx[i];

                if (board_copy[next.pt.y][next.pt.x] != 0) break;
            }

            if (visited[next.pt.y][next.pt.x] == 0)
            {
                visited[next.pt.y][next.pt.x] = 1;
                q.push(next);
            }
        }
    }


    return 0;
}

vector<int> permi;

int solution(vector<vector<int>> board, int r, int c) {
    int answer = MAX_ANS;

    // 중복되지 않게 어떤 카드가 있는지 저장하자
    int card_visited[7] = { 0, };
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] != 0)
            {
                if (card_visited[board[i][j]] == 0)
                {
                    card_visited[board[i][j]] = 1;
                    permi.push_back(board[i][j]);
                }
            }

        }
    }

    sort(permi.begin(), permi.end());

    // 순열 대로 bfs 하자
    do
    {
        board_copy = board;
        pt_now = { r, c };
        int temp = 0;

        for (int i = 0; i < permi.size(); i++)
        {
            temp += bfs(permi[i]) + bfs(permi[i]);
        }

        if (answer > temp)
            answer = temp;

    } while (next_permutation(permi.begin(), permi.end()));



    return answer;
}


int main()
{
    int ans;
    //ans = solution({ {1, 0, 0, 3},{2, 0, 0, 0},{0, 0, 0, 2 }, { 3, 0, 1, 0 }}, 1, 0);
    ans = solution({ {3, 0, 0, 2},{0, 0, 1, 0},{0, 1, 0, 0},{2, 0, 0, 3} }, 0, 1);
    //ans = solution({ {0, 0, 0, 1},{0, 0, 0, 0},{0, 1, 0, 0},{0, 0, 0, 0} }, 0, 3);

    cout << ans;
    return 0;
}