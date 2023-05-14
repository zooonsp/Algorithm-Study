#include<iostream>
#include <string>
#include <vector>

using namespace std;

/*
노드 수 최대 17 -> DFS로 돌려보자

다음 경로를 저장하는 부분을 처음에 DAT로 했는데
DAT에 특정 값을 찾는 게 잘 안되서 시간초과 났음

vector로 다시 구현해서 erase 하며 경로 지우기
*/

const int NODE_MAX = 20;

vector<int> graph[NODE_MAX];
vector<int> info_copy;

int answer = 0;

// dfs에서 다음 경로들을 의미
int DAT[NODE_MAX] = { 0, };
int visited[NODE_MAX] = { 0, };

// 인자 : 현재 노드, 양의 수, 늑대의 수
int dfs(int now, vector<int> next_nodes, int sheep, int wolf)
{
    // 0 양, 1 늑대
    if (info_copy[now] == 0)
        sheep++;
    else
        wolf++;

    // 늑대가 양보다 많으면 더이상 탐색 하지 않는다! (양이 잡아먹히지 않게라는 조건)
    if (wolf >= sheep)
        return 0;

    if (sheep > wolf && answer < sheep)
        answer = sheep;

    // 다음 경로를 하나씩 전부 탐색한다.
    for (int i = 0; i < next_nodes.size(); i++)
    {
        vector<int> next_copy = next_nodes;

        // 탐색하면 그부분은 경로에서 삭제
        next_copy.erase(next_copy.begin() + i);

        // 가는 다음 부분의 경로들을 추가해준다
        for (int node : graph[next_nodes[i]])
            next_copy.push_back(node);

        dfs(next_nodes[i], next_copy, sheep, wolf);
    }
  
    return 0;
}

int solution(vector<int> info, vector<vector<int>> edges) 
{
    info_copy = info;

    // 1. 엣지 정보로 트리 만들어 주자
    for (vector<int> & edge : edges)
    {
        graph[edge[0]].push_back(edge[1]);
    }

    // 2. dfs 하는데 갈 수 있는 경로를 전달 하면서 구하자
   
    dfs(0, graph[0], 0, 0);

    return answer;
}


int main()
{
    int ans = solution({ 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 }, { {0, 1},{1, 2},{1, 4},{0, 8},
        {8, 7},{9, 10},{9, 11},{4, 3},{6, 5},{4, 6},{8, 9} });
    cout << ans << endl;
    return 0;
}