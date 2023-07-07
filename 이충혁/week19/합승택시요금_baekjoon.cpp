#include <iostream>
#include <string>
#include <vector>
#include<algorithm>

using namespace std;


/*
n 지점 갯수 : 3 ~ 200
s 출발 지점, a b 도착지점
fares 크기 : 2 ~ n * (n -1 ) / 2 -> 약 20,000
요금 : 1 ~ 100,000

최대 요금 20억, 더해지면 int 초과 ( mst 구하므로 최대요금이 되진 않지만..)
시간 복잡도 V^3 = 200^3 = 8,000,000 

*/

typedef long long ll;

enum {
    FROM = 0,
    TO = 1,
    W = 2 // weight
};

const ll MAX_VAL = ll(40e8);
const int MAX_POINT = 222;

ll dist[MAX_POINT][MAX_POINT];


int make_dist(const vector<vector<int>> &fares)
{
    for (int i = 0; i < MAX_POINT; i++)
    {
        for (int j = 0; j < MAX_POINT; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = MAX_VAL;
        }
    }

    for (auto& now : fares)
    {
        dist[now[FROM]][now[TO]] = min(dist[now[FROM]][now[TO]], ll( now[W] ));
        dist[now[TO]][now[FROM]] = min(dist[now[TO]][now[FROM]], ll( now[W] ));
    }

    return 0;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;

    make_dist(fares);

    // 플로이드
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }

    answer = min(dist[s][a] + dist[a][b], min(dist[s][b] + dist[b][a], dist[s][a] + dist[s][b]));

    for (int i = 1; i <= n; i++)
    {
        answer = (int)min(ll(answer), ll(dist[s][i] + dist[i][a] + dist[i][b]));
    }

    return answer;
}

int main()
{
    int ans;
    ans = solution(6, 4, 6, 2, { {4, 1, 10},{3, 5, 24},{5, 6, 2},{3, 1, 41},{5, 1, 24},{4, 6, 50},{2, 4, 66},{2, 3, 22},{1, 6, 25} });
    //ans = solution(7, 3, 4, 1, { {5, 7, 9},{4, 6, 4},{3, 6, 1},{3, 2, 3},{2, 1, 6} });
    //ans = solution(6, 4, 5, 6, { {2, 6, 6},{6, 3, 7},{4, 6, 7},{6, 5, 11},{2, 5, 12},{5, 3, 20},{2, 4, 8},{4, 3, 9} });



    cout << ans << endl;
    return 0;
}