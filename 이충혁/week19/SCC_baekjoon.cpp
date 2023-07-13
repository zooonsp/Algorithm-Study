#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX_NODE = 10101;

// V : 노드 갯수, E 엣지 갯수
int V, E;
// cnt : dfs 할때 노드의 인덱스
int cnt;
// dfsn : visited
int dfsn[MAX_NODE];

// SCC 갯수, 어디 SCC 에 속해 있는지
int SN, sn[MAX_NODE];
vector<int> graph[MAX_NODE];
// SCC 분리가 끝나면 체크
bool finished[MAX_NODE];
stack<int> s;
// 답인 SCC 정보 저장
vector<vector<int>> SCC;


int DFS(int curr)
{
    dfsn[curr] = ++cnt; // dfs 돌때 마다 인덱스 만들어주자
    s.push(curr); 

    int ret = dfsn[curr];
    for (int& next : graph[curr])
    {
        // dfsn이 없는 것은 인덱스 가 안만들어졌다는 거다 ( 아직 방문 안함 )
        if (dfsn[next] == 0) ret = min(ret, DFS(next));
        // 방문 했는데 아직 SCC 구성이 안됐으면 판별 해준다
        else if (!finished[next]) ret = min(ret, dfsn[next]);
    }

    // 자식들이 도달 가능한 제일 높은 정점이 나면 SCC 하나로 구성됨
    if (ret == dfsn[curr])
    {
        vector<int> currSCC;

        while (1)
        {
            int t = s.top();
            s.pop();
            currSCC.push_back(t);
            finished[t] = true;
            // 지금 dfs 중인 SCC 로 갱신
            sn[t] = SN;

            // 자기 자신까지 오면 탈출
            if (t == curr) break;
        }

        sort(currSCC.begin(), currSCC.end());

        SCC.push_back(currSCC);
        SN++;
    }
    return ret;
}


int input()
{
    cin >> V >> E;

    for (int i = 0; i < E; i++) {
        int from, to;
        cin >> from >> to;
        graph[from].push_back(to);
    }

    return 0;
}

int solve_func()
{

    for (int i = 1; i < V; i++)
        if (dfsn[i] == 0) DFS(i);

    sort(SCC.begin(), SCC.end());

    cout << SN << "\n";

    for (auto& currSCC : SCC) {

        for (int curr : currSCC)
            cout << curr << " ";
        cout << "-1\n";
    }

    return 0;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);

    input();
    solve_func();
    return 0;
}