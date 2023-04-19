#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <set>
using namespace std;

const int MAT_MAX = 1010;
const int ry[] = { 1, -1, 0, 0 }; // 기본 방향 배열은 0~3은 상하좌우
const int rx[] = { 0, 0, -1, 1 };

const int cy[] = { 0, 1, 1, 1 }; // graph 연결에 써먹을 방향 배열
const int cx[] = { 1, 1, 0, -1 };

const int MAX_ANS = 21e8;

struct coordi {
    int y, x;
};

struct Info {
    int to;
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
// 2. 주변에 붙은 땅들 그래프로 묶자
// graph에는 가중치도 같이 각 노드별 가중치로
// 그리고 땅 들 시작 땅과 도착 땅으로 나누자
// 3. 만든 정보로 시작땅 부터 다익스트라 돌려서
// 최솟값 찾고 찾는중에 최솟값 넘으면 가지치기

int N;
string MAT_str[MAT_MAX];
int MAT[MAT_MAX][MAT_MAX] = { 0, };  // 그래프 만들 때 쓰기 위한 땅 number 저장
int land_size = 0; // 알파벳은 겹치는 경우가 있다. 다시 num 붙여주면서 땅 칸수도 같이 세자
int land_cnt[MAT_MAX * MAT_MAX] = { 0, }; // 각 땅별 칸 수
set<int> us[MAT_MAX * MAT_MAX]; // us[from].find(set) 으로 연결이 되어있는지 용도로 쓸거임 

vector<Info> graph[MAT_MAX * MAT_MAX];
set<int> st_land, ed_land; // 시작 땅, 종료 땅
int dist[MAT_MAX * MAT_MAX];

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

int dijkstra()
{
    // dijk init
    for (int i = 1; i <= land_size; i++)
        dist[i] = MAX_ANS;

    priority_queue<Info> pq;

    for (int i = 1; i <= land_size; i++)
    {
        auto iter = st_land.find(i);
        if (iter == st_land.end()) continue; // 시작 지점 아니면 건너 뜀

        iter = ed_land.find(i);
        if (iter != ed_land.end()) // 시작 지점이 곧 종료 지점이면 
        {
            if (ans > land_cnt[i])
                ans = land_cnt[i];
            continue;
        }
        pq.push({ i, land_cnt[i] });
        dist[i] = land_cnt[i];
    }


    while (!pq.empty())
    {
        Info now = pq.top();
        pq.pop();
        if (dist[now.to] < now.d)
            continue;

        if (ed_land.find(now.to) != ed_land.end())
        {
            ans = dist[now.to];
            return 0;
        }

        for (auto next : graph[now.to])
        {
            int ndist = now.d + next.d;
            if (dist[next.to] <= ndist) continue;
            if (ans <= ndist) continue;
            dist[next.to] = ndist;

            pq.push({ next.to, ndist });
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

    // 2. 그래프로 묶자 
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (MAT[i][j] == 0) continue;
            for (int k = 0; k < 4; k++)
            {
                coordi next = { i, j };
                next.y += cy[k];
                next.x += cx[k];


                if (MAT[next.y][next.x] <= 0) continue; // 로미오 줄리엣, 울타리면 건너 뜀
                if (MAT[next.y][next.x] == MAT[i][j]) continue; // 같은 땅이면 건너 뜀

                auto iter = us[MAT[i][j]].find(MAT[next.y][next.x]);
                if (iter != us[MAT[i][j]].end()) continue;

                us[MAT[i][j]].insert(MAT[next.y][next.x]);
                us[MAT[next.y][next.x]].insert(MAT[i][j]);

                graph[MAT[i][j]].push_back({ MAT[next.y][next.x], land_cnt[MAT[next.y][next.x]] });
                graph[MAT[next.y][next.x]].push_back({ MAT[i][j] , land_cnt[MAT[i][j]] });

            }


            // 시작 지점 종료 지점도 이 루틴에서 같이 찾자
            if ((i == 1 || j == N) && !(i == 1 && j == 1))
            {
                auto iter = st_land.find(MAT[i][j]);
                if (iter == st_land.end())
                {
                    st_land.insert(MAT[i][j]);
                }
            }

            if ((i == N || j == 1) && !(i == N && j == N))
            {
                auto iter = ed_land.find(MAT[i][j]);
                if (iter == ed_land.end())
                {
                    ed_land.insert(MAT[i][j]);
                }
            }

        }
    }

    // 3. 다익스트라 시작지점 여러개 같이
    dijkstra(); // ans 여기서 갱신


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