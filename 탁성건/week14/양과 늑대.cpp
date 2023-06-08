// https://velog.io/@thguss/%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%A8%B8%EC%8A%A4-L3-%EC%96%91%EA%B3%BC-%EB%8A%91%EB%8C%80-python
#include <vector>
using namespace std;

int answer;
vector<int> visited;

void dfs(int sheep, int wolf, const vector<int> &info,
         const vector<vector<int>> &edges) {
  if (sheep <= wolf)
    return;

  answer = answer > sheep ? answer : sheep;

  for (const vector<int> &edge : edges) {
    int p = edge[0];
    int c = edge[1];

    if (visited[p] && !visited[c]) {
      visited[c] = 1;
      info[c] == 0 ? dfs(sheep + 1, wolf, info, edges)
                   : dfs(sheep, wolf + 1, info, edges);
      visited[c] = 0;
    }
  }
}

int solution(vector<int> info, vector<vector<int>> edges) {
  answer = 0;

  vector<int>(info.size()).swap(visited);
  visited[0] = 1;

  dfs(1, 0, info, edges);

  return answer;
}
