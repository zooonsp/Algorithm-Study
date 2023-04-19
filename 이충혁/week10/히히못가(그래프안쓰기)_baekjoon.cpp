#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <set>
using namespace std;

const int MAT_MAX = 1010;
const int ry[] = { 1, -1, 0, 0, 1, 1, -1, -1 }; // 기본 방향 배열은 0~3은 상하좌우
const int rx[] = { 0, 0, -1, 1, 1, -1, -1, 1 };

const int MAX_ANS = 21e8;

struct coordi {
    int y, x;
};

struct Info {
    coordi pt;
    int d;

    bool operator < (Info next) const
    {
        if (d > next.d)
            return true;
        return false;
    }
};


// 1. 각 땅별로 칸수 세기
// 칸수 세면서 MAT 배열에 각 땅의 num(bfs 한번 돌릴 때 마다 1씩 커짐)
// 과 땅의 칸수 land_cnt를 저장한다. ( MAT 배열은 visited 역할도 같이 한다 )
// 2. 만든 MAT에서 가중치를 적게 가져가도록 bfs 하는데 같은 땅을 밟으면 가중치 증가하지 않고
// 이전에 밟은 것 보다 지금이 더 적은 가중치라면 갱신 하면서 진행

int N;
string MAT_str[MAT_MAX];
int MAT[MAT_MAX][MAT_MAX] = { 0, };  // 그래프 만들 때 쓰기 위한 땅 number 저장
int land_size = 0; // 알파벳은 겹치는 경우가 있다. 다시 num 붙여주면서 땅 칸수도 같이 세자
int land_cnt[MAT_MAX * MAT_MAX] = { 0, }; // 각 땅별 칸 수
set<int> start_set; // 시작 부분 어디를 썼는지 체크

int ans = MAX_ANS;

int init()
{
    for (int i = 0; i < MAT_MAX; i++)
    {
        for (int j = 0; j < MAT_MAX; j++)
        {
            MAT[i][j] = -1; // 울타리
        }
    }

    return 0;
}

int input()
{
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            MAT[i][j] = 0; // 울타리 외의 부분 다시 0으로
        }
    }

    string str;
    for (int i = 1; i <= N; i++)
    {
        cin >> str;
        MAT_str[i] = ' ' + str;
    }

    return 0;
}

// 땅별로 칸수 세고 땅 정보를 MAT int 배열로 바꾸자
int bfs_cnt(coordi st)
{
    land_size++;
    land_cnt[land_size] = 1;
    queue<coordi> q;
    q.push(st);
    MAT[st.y][st.x] = land_size;
    char land_name = MAT_str[st.y][st.x];

    while (!q.empty())
    {
        coordi now = q.front();
        q.pop();


        for (int i = 0; i < 4; i++)
        {
            coordi next = now;
            next.y += ry[i];
            next.x += rx[i];

            if (MAT[next.y][next.x] != 0) continue;
            if (land_name != MAT_str[next.y][next.x]) continue;

            MAT[next.y][next.x] = land_size;
            land_cnt[land_size]++;

            q.push(next);
        }
    }

    return 0;
}

int visited[MAT_MAX][MAT_MAX] = { 0, };

int bfs_ans()
{
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            visited[i][j] = MAX_ANS;

    priority_queue<Info> pq;



    for (int i = 1; i <= N; i++)
    {
        if (start_set.find(MAT[1][i]) == start_set.end() &&
            i != 1)
        {
            start_set.insert(MAT[1][i]);
            pq.push({ {1, i}, land_cnt[MAT[1][i]]});
            visited[1][i] = land_cnt[MAT[1][i]];
        }

        if (start_set.find(MAT[i][N]) == start_set.end() &&
            i != N)
        {
            start_set.insert(MAT[i][N]);
            pq.push({ {i, N}, land_cnt[MAT[i][N]] });
            visited[i][N] = land_cnt[MAT[i][N]];
        }

    }


    while (!pq.empty())
    {
        Info now = pq.top();
        pq.pop();

        if (now.pt.y == N || now.pt.x == 1)
        {
            if (ans > now.d)
                ans = now.d;
            return 0;
        }

        for (int i = 0; i < 8; i++)
        {
            Info next = now;
            next.pt.y += ry[i];
            next.pt.x += rx[i];

            if (MAT[next.pt.y][next.pt.x] <= 0) continue;

            if (MAT[now.pt.y][now.pt.x] != MAT[next.pt.y][next.pt.x])
                next.d += land_cnt[MAT[next.pt.y][next.pt.x]];

            if (visited[next.pt.y][next.pt.x] <= next.d)
            {
                continue;
            }

            visited[next.pt.y][next.pt.x] = next.d;
            pq.push(next);
        }
    }

    return 0;
}

int solve_func()
{
    // 1. 연결된 부분 땅의 칸 수 세기

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (MAT_str[i][j] == '.') continue;
            if (MAT[i][j] != 0) continue;

            bfs_cnt({ i, j });
        }
    }

    // 2. 가중치 관련 그래프 안쓰고 탐색 하기 (다익스트라 비슷)
    bfs_ans();

    return 0;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    freopen("input.txt", "r", stdin);

    init();
    input();
    solve_func();

    cout << ans;

    return 0;
}