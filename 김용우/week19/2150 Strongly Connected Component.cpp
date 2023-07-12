#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

int V, E;    // V: 정점의 개수, E: 간선의 개수
std::vector<std::vector<int>> v;    // v[i][j]: i 정점과 연결되어 있는 j 번째 정점 번호
std::vector<int> dfsNum;    // dfsNum[i]: 정점의 번호 (dfs를 돌면서 처음 만난 순서)
int nodeCnt;    // nodeCnt: dfs를 돌면서 만난 노드의 개수 
std::stack<int> s;    // s[i]: scc를 탐색하며 쌓은 노드 번호
std::vector<bool> finished;    // finished[i]: i 번째 노드가 SCC로 묶임
int sccN;	// sccN: 노드 번호
std::vector<int> sccNum;	// sccNum[i]: i 노드가 소속된 SCC 번호
std::vector<std::vector<int>> scc;	// scc[i]: i 번째 SCC

int dfs(int curr) {    // curr: 현재 노드
    dfsNum[curr] = ++nodeCnt;    // 노드 번호 할당
    s.push(curr);    // 스택에 넣음

    int result = dfsNum[curr];    // result: 노드 번호
    int nextSize = v[curr].size();    // nextSize: 현재 노드에서 갈 수 있는 노드 개수
    for (int i = 0; i < nextSize; ++i) {
        int next = v[curr][i];    // next: curr 노드에 연결되어 있는 노드 번호
        if (!dfsNum[next]) result = std::min(result, dfs(next));    // next 노드를 방문한 적이 없으면, 탐색 진행
        else if (!finished[next]) result = std::min(result, dfsNum[next]);	// SCC로 묶이지 않은 노드면, 최소값 찾음
    }

    if (result == dfsNum[curr]) {	// 현재 노드 번호와 노드 번호가 같으면
        std::vector<int> currSCC;	// currSCC: 현재 SCC
        while (true) {
            int top = s.top();	// top: 스택의 가장 위에 있는 노드 번호
            s.pop();

            currSCC.push_back(top);
            finished[top] = true;	// 이 노드는 SCC로 묶임
            sccNum[top] = sccN;	// SCC로 묶이는 노드가 어떤 노드로 묶였는지 기록
            if (top == curr) break;
        }
        std::sort(currSCC.begin(), currSCC.end());
        scc.push_back(currSCC);
        sccN++;
    }

    return result;
}

void solution() {

    dfsNum.assign(V, 0);
    finished.assign(V, false);
    sccNum.assign(V, 0);

    for (int i = 0; i < V; ++i) {
        if (!dfsNum[i]) dfs(i);    // dfs를 통해 방문하지 못한 노드를 시작으로 dfs
    }
    std::sort(scc.begin(), scc.end());

    return;
}

void input() {

    std::cin >> V >> E;

    v.assign(V, std::vector<int>(0, 0));    // 노드와 연결되어있는 노드 정보 공간 할당

    for (int i = 0; i < E; ++i) {
        int A, B;    // A, B: A에서 B로 연결되어 있는 간선
        std::cin >> A >> B;
        v[A - 1].push_back(B - 1);
    }

    return;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    input();

    solution();

    std::cout << sccN << '\n';
    for (int j = 0; j < sccN; ++j) {
        int currSize = scc[j].size();
        for (int i = 0; i < currSize; ++i) {
            std::cout << scc[j][i] + 1 << ' ';
        }
        std::cout << "-1\n";
    }

    return 0;
}