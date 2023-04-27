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

// 1. 공기를 ( 0, 0 ) 부터 bfs 
// 2. 공기면 visited 2로 만들면서 갱신
// 3. 치즈면 visited ++ 해주고 2가 되면 age + 1, pq push


int N, M; // N 세로, M 가로
int MAT[MAT_MAX][MAT_MAX];
int visited[MAT_MAX][MAT_MAX] = { 0, }; // 2 이상 이면 공기
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
    visited[0][0] = 2;

    while (!pq.empty())
    {
        Info now = pq.top();
        pq.pop();

        if (MAT[now.pt.y][now.pt.x])
        {
            if (max_age < now.age)
                max_age = now.age;
        }

        for (int i = 0; i < 4; i++)
        {
            Info next;
            next.pt = now.pt + rd[i];
            next.age = now.age;

            if (next.pt.y < 0 || next.pt.y >= N ||
                next.pt.x < 0 || next.pt.x >= M) continue;
            if (visited[next.pt.y][next.pt.x] >= 2) continue;

            if (MAT[next.pt.y][next.pt.x] == 1) 
            {
                visited[next.pt.y][next.pt.x]++;
                if (visited[next.pt.y][next.pt.x] < 2) continue; // 접촉 부분 2개가 아닐때

                next.age++;
            }
            else
            {
                visited[next.pt.y][next.pt.x] = 2;
            }
   
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

    cout << max_age;

    return 0;
}