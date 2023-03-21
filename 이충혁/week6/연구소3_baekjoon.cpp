#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<cstring>

using namespace std;
const int MAX = 21e8;
const int MAX_MAT = 55;

struct coordi {
    int y, x;
};

struct Info {
    coordi pt;
    int cnt;
};

const int ry[] = { -1, 1, 0, 0 };
const int rx[] = { 0, 0, -1, 1 };
int MAT[MAX_MAT][MAX_MAT];
int MAT_COPY[MAX_MAT][MAX_MAT]; // bfs 쓸려고 복사
vector<coordi> virus;

int N, M; // N(맵크기), M(선택 바이러스 수)
int empty_cnt = 0;

int input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> MAT[i][j];
            if (MAT[i][j] == 2)
            {
                virus.push_back({ i,j });
            }
            else if (MAT[i][j] == 0)
            {
                empty_cnt++;
            }
        }
    }
    return 0;
}

int ans = MAX;
int virus_select[MAX_MAT * MAX_MAT];

int bfs()
{
    queue<Info> q;

    // 복사
    for (int i = 0; i < MAX_MAT; i++)
    {
        for (int j = 0; j < MAX_MAT; j++)
        {
            MAT_COPY[i][j] = MAT[i][j];
        }
    }


    for (int i = 0; i < virus.size(); i++)
    {
        if (virus_select[i] == 0) continue;
        q.push({ virus[i], 0 });
        ;
    }

    int max_cnt = 0;

    int fill_cnt = 0;

    while (!q.empty())
    {
        Info now = q.front();
        q.pop();

        if (fill_cnt == empty_cnt)
        {
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            Info next;
            next.pt.y = now.pt.y + ry[i];
            next.pt.x = now.pt.x + rx[i];

            if (next.pt.y < 0 || next.pt.y >= N ||
                next.pt.x < 0 || next.pt.x >= N) continue;

            if (MAT_COPY[next.pt.y][next.pt.x] == 1) continue;

            if (MAT_COPY[next.pt.y][next.pt.x] == 0)
                fill_cnt++;

            MAT_COPY[next.pt.y][next.pt.x] = 1;
            next.cnt = now.cnt + 1;

            if (max_cnt < next.cnt)
                max_cnt = next.cnt;

            q.push(next);

        }
    }


    if (ans > max_cnt && fill_cnt == empty_cnt)
        ans = max_cnt;

    return 0;
}



int select_cnt = 0; // 뽑은 바이러스 수

// 바이러스를 갯수 만큼 뽑는다.
void dfs(int now)
{
    // 기저조건 2개
    if (select_cnt == M)
    {
        bfs();
        return;
    }
    if (virus.size() == now)
    {
        return;
    }

    for (int i = now; i < virus.size(); i++)
    {
        virus_select[i] = 1;
        select_cnt++;
        dfs(i + 1);
        virus_select[i] = 0;
        select_cnt--;
    }

    return;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // freopen("input.txt", "r", stdin);

    input();

    // 이미 풀인지
    int full_flag = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (MAT[i][j] == 0)
            {
                full_flag = 0;
            }
        }
    }

    if (full_flag)
    {
        cout << 0;
        return 0;
    }


    dfs(0);

    if (ans == MAX)
        ans = -1;

    cout << ans;

    return 0;
}
