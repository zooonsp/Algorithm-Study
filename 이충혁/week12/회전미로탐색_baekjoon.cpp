#include<iostream>
#include<queue>
#include<string>
#include<cstring>
using namespace std;

const int ROTA_SIZE = 4;
const int MAT_MAX = 510;

const int ry[] = { -1, 1, 0, 0 };
const int rx[] = { 0, 0, -1, 1 };

struct coordi {
    int y, x;

    bool operator == (coordi next) const
    {
        if (y == next.y && x == next.x)
            return true;
        return false;
    }
};

struct Info {
    coordi pt;
    int cnt;
    int rot;

    bool operator <(Info next)const
    {
        if (cnt > next.cnt)
            return true;

        return false;
    }
};

int K;
int MAT[MAT_MAX][MAT_MAX];
coordi st, ed; // 출발 도착지 좌표


int input()
{
    cin >> K;
    string temp;
    memset(MAT, -1, sizeof(MAT));
    for (int i = 0; i < K * ROTA_SIZE; i++)
    {
        cin >> temp;
        for (int j = 0; j < K * ROTA_SIZE; j++)
        {
            if (temp[j] == 'S')
            {
                st = { i + 1, j + 1 };
            }
            else if (temp[j] == 'E')
            {
                ed = { i + 1, j + 1 };
            }

            if (temp[j] != '#')
            {
                MAT[i + 1][j + 1] = 0;
            }
        }
    }
    return 0;
}

int visited[4][MAT_MAX][MAT_MAX]; // 4* 4 개별 좌표

coordi real_index(coordi pt, const coordi& stand, const int& rot)
{
    for (int i = 0; i < rot; i++)
    {
        coordi temp;
        // 90도 회전시
        // 다음 y = 현재 x - 기준 x + 기준 y
        // 다음 x = ( N + 1 - ( 현재 y - 기준 y)) + 기준 x
        temp.y = pt.x - stand.x + stand.y;
        temp.x = (ROTA_SIZE + 1 - (pt.y - stand.y)) + stand.x;

        pt = temp;
    }

    return pt;
}


int solve_func() // bfs
{
    priority_queue<Info> pq;
    pq.push({ st, 0, 0 });
    visited[0][st.y][st.x] = 1;

    coordi real_ed = ed;

    while (!pq.empty())
    {
        Info now = pq.top();
        pq.pop();

        coordi stand, stand_mx, stand_mn, real;
        stand.y = (now.pt.y - 1) / ROTA_SIZE * ROTA_SIZE;
        stand.x = (now.pt.x - 1) / ROTA_SIZE * ROTA_SIZE;

        stand_mn.y = stand.y + 1;
        stand_mx.y = stand.y + ROTA_SIZE;

        stand_mn.x = stand.x + 1;
        stand_mx.x = stand.x + ROTA_SIZE;

        // 도착지점 확인

        if (now.pt == ed)
        {
            return now.cnt;
        }

        if (visited[(now.rot + 1) % ROTA_SIZE][now.pt.y][now.pt.x] == 0)
        {
            visited[(now.rot + 1) % ROTA_SIZE][now.pt.y][now.pt.x] = 1;
            pq.push({ now.pt , now.cnt + 1, (now.rot + 1) % ROTA_SIZE }); // 가만히 있을때 도는 경우
        }


        for (int i = 0; i < 4; i++) // 상하좌우로 가고 도는 경우
        {
            Info next = now;
            next.pt.y += ry[i];
            next.pt.x += rx[i];

            next.cnt++;

            // 4*4 구간 넘었을 떄 처리
            if (next.pt.y < stand_mn.y || next.pt.y > stand_mx.y ||
                next.pt.x < stand_mn.x || next.pt.x > stand_mx.x)
            {
                real = real_index(next.pt, stand, next.rot);

                if (MAT[real.y][real.x] == -1) continue;
                if (visited[0][real.y][real.x] == 1) continue;

                //visited[0][real.y][real.x] = 1;
                visited[1][real.y][real.x] = 1;
                pq.push({ real, next.cnt, 1 });
                continue;
            }
            next.rot = (next.rot + 1) % ROTA_SIZE;

            if (MAT[next.pt.y][next.pt.x] == -1) continue;
            if (visited[next.rot][next.pt.y][next.pt.x]) continue;

            //visited[0][next.pt.y][next.pt.x] = 1;
            visited[next.rot][next.pt.y][next.pt.x] = 1;

            pq.push(next);

        }
    }

    return -1;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);

    input();
    cout << solve_func();

    return 0;
}