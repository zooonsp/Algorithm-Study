#include <iostream>
#include<string> // 이건 뭐지
#include <vector>
#include <queue>

using namespace std;
const int MAX_NUM = 21e8;
const int MAX_NODE = 50505;

struct Info { // 그래프 구조체
    int to;
    int time; // 걸리는 시간

    bool operator<(Info next) const
    {
        if (time > next.time)
            return true;

        return false;
    }
};

// 최소 가중치를 모두 더하는 방법이 아닌 한번 씩 체크하는 형태의 다익스트라로 풀이
// 정답은 가장 최소 시간한계 + 최소 봉우리 수 이기 때문에 마지막에 계산


vector<Info> graph[MAX_NODE]; // 간선(비용, 번호)
int dist[MAX_NODE]; // 다익스트라 최댓갑 ( 더해지는 연산 말고 최대 비교 연산만 함 )

int summit_check[MAX_NODE] = { 0, };

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {

    for (int i = 0; i < paths.size(); i++) 
    {
        graph[paths[i][0]].push_back({ paths[i][1], paths[i][2] });
        graph[paths[i][1]].push_back({ paths[i][0], paths[i][2] });
    }

    // 도착 정보 기입
    for (int i = 0; i < summits.size(); i++)
        summit_check[summits[i]] = 1;

    for (int i = 0; i < MAX_NODE; i++)
    {
        dist[i] = 21e8;
    }

    priority_queue<Info> pq;
    for (int i = 0; i < gates.size(); i++)
    {
        dist[gates[i]] = 0;
        pq.push({ gates[i], dist[gates[i]] });
    }
    while (!pq.empty()) 
    {
        Info now = pq.top(); 
        pq.pop();
        if (dist[now.to] != now.time)
            continue;
        for (int i = 0; i < graph[now.to].size(); i++) 
        {
            if (dist[graph[now.to][i].to] <= max(dist[now.to], graph[now.to][i].time))
                continue;
            dist[graph[now.to][i].to] = max(dist[now.to], graph[now.to][i].time);
            if (!summit_check[graph[now.to][i].to])
                pq.push({ graph[now.to][i].to, dist[graph[now.to][i].to] });
        }
    }

    // 구해진 봉우리들 중 기준에 맞는거 찾기
    int ans = summits[0];
    for (int i=0; i<summits.size(); i++)
    {
        if (dist[summits[i]] < dist[ans])
            ans = summits[i];
        else if (dist[summits[i]] == dist[ans] && summits[i] < ans)
            ans = summits[i];
    }
    return vector<int>({ ans, dist[ans] });
}


int main()
{
    vector<int> ans;
    ans = solution(6, { {1, 2, 3},{2, 3, 5},{2, 4, 2}, {2, 5, 4},{3, 4, 4},{4, 5, 3},{4, 6, 1},{5, 6, 1} }, { 1, 3 }, { 5 });
    
    cout << ans[0] << " " << ans[1];
    return 0;
}