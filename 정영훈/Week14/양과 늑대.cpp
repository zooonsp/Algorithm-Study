// https://wadekang.tistory.com/10 (하다가 안 되서 참고..)

// 루트 노드에서 출발.
// 양의 수보다 늑대의 수가 같거나 더 많아지면 모든 양을 잡아 먹음.
// 양이 늑대에게 잡아먹히지 않도록 하면서 최대한 많은 수의 양을 모아서 다시 루트 노드로 돌아오기.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using Graph = vector<vector<int>>;
Graph graph;

constexpr int WOLF = 1;

struct Info
{
    int sheep, wolf, visitedBit;
    Info(int s, int w, int vb) : sheep(s), wolf(w), visitedBit(vb) {}
};

// visitedBit(방문했던 곳들의 좌표)가 정해지면 그에 해당하는 상태는 하나임. - 포인트!
// 노드 정보를 저장할 필요 없음.

int solution(vector<int> info, vector<vector<int>> edges)
{
    int answer = 0;
    int N = static_cast<int>(info.size());
    graph = vector<vector<int>>(N);
    const int ALLVISITED = (1 << N);
    vector<int> visited(ALLVISITED, 0);
    for (vector<int> &edge : edges)
    {
        int &from = edge[0], &to = edge[1]; // 부모 노드 -> 자식 노드 (문제 읽지도 않음..)
        graph[from].push_back(to);
        // graph[to].push_back(from); - 필요 없음.
    }

    queue<Info> q;
    q.push(Info(1, 0, 1));
    answer = 1;
    while (!q.empty())
    {
        Info now = q.front();
        q.pop();

        for (int i{}; i < N; ++i)
        { // bitfield DP처럼
            if (now.visitedBit & (1 << i))
            { // 현재 방문한 정점인 경우 확장
                for (int &next : graph[i])
                {
                    if (now.visitedBit & (1 << next))
                        continue; // 이미 방문
                    int newVisit = now.visitedBit | (1 << next);
                    if (visited[newVisit])
                        continue; // 이미 해당 상태는 체크 완료

                    if (info[next] == WOLF)
                    {
                        if (now.wolf + 1 >= now.sheep)
                            continue; // 못 감
                        visited[newVisit] = 1;
                        answer = max(answer, now.sheep);
                        q.push(Info(now.sheep, now.wolf + 1, newVisit));
                    }
                    else
                    {
                        visited[newVisit] = 1;
                        answer = max(answer, now.sheep + 1);
                        q.push(Info(now.sheep + 1, now.wolf, newVisit));
                    }
                }
            }
        }
    }

    return answer;
}

int main()
{

    vector<int> info{0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1};
    vector<vector<int>> edges{{0, 1}, {1, 2}, {1, 4}, {0, 8}, {8, 7}, {9, 10}, {9, 11}, {4, 3}, {6, 5}, {4, 6}, {8, 9}};
    cout << solution(info, edges) << '\n';

    vector<int> info1{0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0};
    vector<vector<int>> edges1{{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {3, 7}, {4, 8}, {6, 9}, {9, 10}};
    cout << solution(info1, edges1) << '\n';

    // 12, 16
    // https://school.programmers.co.kr/questions/44699
    vector<int> info2{0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0};
    vector<vector<int>> edges2{{0, 1}, {1, 2}, {1, 4}, {0, 8}, {8, 7}, {9, 10}, {9, 11}, {4, 3}, {6, 5}, {4, 6}, {8, 9}};
    cout << solution(info2, edges2) << '\n';

    return 0;
}