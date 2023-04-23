#include<iostream>
#include<queue>
using namespace std;

const int MAT_MAX = 110;
const int CNT_MAX = 100;

struct coordi {
    int y, x;

    coordi operator +(const coordi& next)
    {
        coordi temp;
        temp.y = y + next.y;
        temp.x = x + next.x;

        return temp;
    }
};

const coordi rd[] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

struct Info {
    coordi pt;
    int age;

    bool operator <(const Info& next) const
    {
        if (age > next.age)
            return true;
        return false;
    }
};

// 1. 공기를 ( 0, 0 부터 bfs )
// 2. 1을 만나면 시간 + 1, 녹일 치즈 큐에 넣고 카운트도 갱신
// 3. 시간 커지면 답 갱신


int N, M; // N 세로, M 가로
int MAT[MAT_MAX][MAT_MAX];
int visited[MAT_MAX][MAT_MAX] = { 0, };
int melt_cnt[CNT_MAX] = { 0, }; // 각 단계별 녹은 치즈
int max_age = 0;


int input()
{
    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAT[i][j];
        }
    }

    return 0;
}

int solve_func() // bfs
{
    priority_queue<Info> pq; // 녹일 치즈
    pq.push({ {0,0}, 0 });
    visited[0][0] = 1;

    while (!pq.empty())
    {
        Info now = pq.top();
        pq.pop();

        // 답갱신 하자
        if (MAT[now.pt.y][now.pt.x]) // 속에 구멍이 있으면 답갱신이 제대로 안됨 그래서 치즈를 녹일때만 갱신
        {
            if (max_age < now.age)
                max_age = now.age;
            melt_cnt[now.age]++;
        }

        for (int i = 0; i < 4; i++)
        {
            Info next;
            next.pt = now.pt + rd[i];
            next.age = now.age;

            if (next.pt.y < 0 || next.pt.y >= N ||
                next.pt.x < 0 || next.pt.x >= M) continue;
            if (visited[next.pt.y][next.pt.x] == 1) continue;

            visited[next.pt.y][next.pt.x] = 1;
            if (MAT[next.pt.y][next.pt.x] == 1)
                next.age++;
            pq.push(next);
        }
    }

    return 0;
}


int main()
{
    cin.tie(NULL)->sync_with_stdio(false);

    input();
    solve_func();

    cout << max_age << '\n' << melt_cnt[max_age];

    return 0;
}