#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int dist[202][202];

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;

    //dist 배열 INF로 초기화
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!(i == j)) dist[i][j] = INF;
              // 자기자신 제외
            else dist[i][j] = 0;
        }
    }

    // 각 경로에 대한 최솟값 갱신
    for (int i = 0; i < fares.size(); i++) {
        int c = fares[i][0], d = fares[i][1], f = fares[i][2];
        dist[c][d] = min(dist[c][d], f);
        dist[d][c] = min(dist[d][c], f);
    }

    // 플로이드 워셜!
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // 3가지 경우로 나눠서 계산
    
    // 1. 출발점에서 a 혹은 b를 갔다가 남은 장소로 가는 경우
    int aTob = dist[s][a] + dist[a][b];
    int bToa = dist[s][b] + dist[b][a];
    answer = min(aTob, bToa);

    // 2. 택시를 따로 타고 가는 경우
    answer = min(answer, dist[s][a] + dist[s][b]);
    
    // 3. 어느 중간지점에서 따로 집으로 가는경
    for (int i = 1; i <= n; i++) {
        if (i == s || i == a || i == b) continue;
        if (dist[s][i] == INF || dist[i][a] == INF || dist[i][b] == INF) continue;
        answer = min(answer, dist[s][i] + dist[i][a] + dist[i][b]);
    }

    return answer;


}
