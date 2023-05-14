// 94.4 - TC 16번엔 누가 살고 있는 것인가..
// 루트 노드에서 출발.
// 양의 수보다 늑대의 수가 같거나 더 많아지면 모든 양을 잡아 먹음.
// 양이 늑대에게 잡아먹히지 않도록 하면서 최대한 많은 수의 양을 모아서 다시 루트 노드로 돌아오기.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

using Graph = vector<vector<int>>;
Graph graph;

constexpr int WOLF = 1;
constexpr int SHEEP = 0;

struct Info
{
    int node, sheep, wolf, visitedBit;
    Info(int n, int s, int w, int vb) : node(n), sheep(s), wolf(w), visitedBit(vb) {}
};

int solution(vector<int> info, vector<vector<int>> edges)
{
    int answer = 0;
    int N = static_cast<int>(info.size());
    graph = vector<vector<int>>(N);
    const int ALLVISITED = (1 << N);
    vector<int> sheep(N, 0);
    vector<set<int>> sheepVisited(N);
    vector<int> wolf(N, 0);
    for (vector<int> &edge : edges)
    {
        int &from = edge[0], &to = edge[1];
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    queue<Info> q;
    q.push(Info(0, 1, 0, 1));
    answer = sheep[0] = 1;
    sheepVisited[0].insert(0);
    while (!q.empty())
    {
        Info now = q.front();
        q.pop();

        for (int &next : graph[now.node])
        {
            if (info[next] == WOLF)
            {
                if (now.visitedBit & (1 << next))
                { // 기존에 감
                    if (sheep[next] < now.sheep)
                    {
                        q.push(Info(next, now.sheep, now.wolf, now.visitedBit));
                        wolf[next] = now.wolf;
                        sheep[next] = now.sheep;
                        sheepVisited[next].clear();
                        sheepVisited[next].insert(now.visitedBit);
                        answer = max(answer, sheep[next]);
                    }
                    else if (sheep[next] == now.sheep)
                    {
                        if (wolf[next] > now.wolf)
                        {
                            q.push(Info(next, now.sheep, now.wolf, now.visitedBit));
                            wolf[next] = now.wolf;
                            sheep[next] = now.sheep;
                            sheepVisited[next].clear();
                            sheepVisited[next].insert(now.visitedBit);
                            answer = max(answer, sheep[next]);
                        }
                    }
                }
                else
                { // 새로 방문
                    if (now.wolf + 1 < now.sheep)
                    {
                        if (sheep[next] < now.sheep)
                        {
                            int newVisitedBit = now.visitedBit | (1 << next);
                            q.push(Info(next, now.sheep, now.wolf + 1, newVisitedBit));
                            wolf[next] = now.wolf + 1;
                            sheep[next] = now.sheep;
                            sheepVisited[next].clear();
                            sheepVisited[next].insert(newVisitedBit);
                            answer = max(answer, sheep[next]);
                        }
                        else if (sheep[next] == now.sheep)
                        {
                            int newVisitedBit = now.visitedBit | (1 << next);
                            q.push(Info(next, now.sheep, now.wolf + 1, newVisitedBit));
                            wolf[next] = now.wolf + 1;
                            sheep[next] = now.sheep;
                            sheepVisited[next].insert(newVisitedBit);
                            answer = max(answer, sheep[next]);
                        }
                    }
                }
            }
            else
            { // SHEEP
                if (now.visitedBit & (1 << next))
                { // 기존에 감
                    if (sheep[next] < now.sheep)
                    {
                        q.push(Info(next, now.sheep, now.wolf, now.visitedBit));
                        wolf[next] = now.wolf;
                        sheep[next] = now.sheep;
                        sheepVisited[next].clear();
                        sheepVisited[next].insert(now.visitedBit);
                        answer = max(answer, sheep[next]);
                    }
                    else if (sheep[next] == now.sheep)
                    {
                        if (wolf[next] > now.wolf)
                        {
                            q.push(Info(next, now.sheep, now.wolf, now.visitedBit));
                            wolf[next] = now.wolf;
                            sheep[next] = now.sheep;
                            sheepVisited[next].clear();
                            sheepVisited[next].insert(now.visitedBit);
                            answer = max(answer, sheep[next]);
                        }
                        else if (wolf[next] == now.wolf)
                        {
                            if (sheepVisited[next].find(now.visitedBit) == sheepVisited[next].end())
                            {
                                q.push(Info(next, now.sheep, now.wolf, now.visitedBit));
                                wolf[next] = now.wolf;
                                sheep[next] = now.sheep;
                                sheepVisited[next].insert(now.visitedBit);
                                answer = max(answer, sheep[next]);
                            }
                        }
                    }
                }
                else
                {
                    if (sheep[next] < now.sheep + 1)
                    {
                        int newVisitedBit = now.visitedBit | (1 << next);
                        q.push(Info(next, now.sheep + 1, now.wolf, newVisitedBit));
                        wolf[next] = now.wolf;
                        sheep[next] = now.sheep + 1;
                        sheepVisited[next].clear();
                        sheepVisited[next].insert(newVisitedBit);
                        answer = max(answer, sheep[next]);
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
    vector<int> info2{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<vector<int>> edges2{{0, 1}, {1, 2}, {1, 4}, {0, 8}, {8, 7}, {9, 10}, {9, 11}, {4, 3}, {6, 5}, {4, 6}, {8, 9}};
    cout << solution(info2, edges2) << '\n';

    return 0;
}