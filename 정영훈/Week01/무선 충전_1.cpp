// 접근 1. 맵에 갈 수 있는 모든 충전기 정해버리기 800
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
 
inline int Abs(int x, int y) { return x - y < 0 ? y - x : x - y; }
 
using namespace std;
 
struct charger {
    int x, y; // 위치
    int canCover; // 커버 가능 범위
    int capacity; // 충전량
    charger(int x, int y, int can, int cap) : x(x), y(y), canCover(can), capacity(cap) {}
    charger() {}
};
 
struct coord {
    int x, y;
    coord(int x, int y) : x(x), y(y) {}
};
 
// 제자리, 상, 우, 하, 좌
int dx[]{ 0,-1,0,1,0 };
int dy[]{ 0,0,1,0,-1 };
int M{}, A{};
int aMove[110]{};
int bMove[110]{};
int ans{};
charger chargers[10]{};
coord Acoord(0, 0), Bcoord(0, 0);
 
// (1,1) 부터 시작
 

// 접근 2. 매 시간마다 충전 가능한 충전기 구하기 16 * (20 ~ 100)
 
vector<int> Map[11][11]{}; // 가능한 충전기들
 
void Reset() {
    // Map
    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            Map[i][j].clear();
        }
    }
    // coord
    Acoord.x = Acoord.y = 1;
    Bcoord.x = Bcoord.y = 10;
 
    // ans
    ans = 0;
}
 
void getMax() {
    if (Map[Acoord.x][Acoord.y].size() == 0 && Map[Bcoord.x][Bcoord.y].size() == 0) return;
    if (Map[Acoord.x][Acoord.y].size() == 0) {
        ans += chargers[Map[Bcoord.x][Bcoord.y][0]].capacity;
    }
    else if (Map[Bcoord.x][Bcoord.y].size() == 0) {
        ans += chargers[Map[Acoord.x][Acoord.y][0]].capacity;
    }
    else { // 둘 다 가능한 충전기가 1개 이상일 때
        if (Map[Acoord.x][Acoord.y][0] == Map[Bcoord.x][Bcoord.y][0]) { // 둘이 같은 경우
            if (Map[Acoord.x][Acoord.y].size() == 1 && Map[Bcoord.x][Bcoord.y].size() == 1) {
                ans += chargers[Map[Acoord.x][Acoord.y][0]].capacity;
            }
            else if (Map[Acoord.x][Acoord.y].size() == 1) {
                ans += chargers[Map[Acoord.x][Acoord.y][0]].capacity;
                ans += chargers[Map[Bcoord.x][Bcoord.y][1]].capacity;
            }
            else if (Map[Bcoord.x][Bcoord.y].size() == 1) {
                ans += chargers[Map[Acoord.x][Acoord.y][1]].capacity;
                ans += chargers[Map[Bcoord.x][Bcoord.y][0]].capacity;
            }
            else { // 둘 다 2개 이상 가능할 때
                if (chargers[Map[Acoord.x][Acoord.y][1]].capacity > chargers[Map[Bcoord.x][Bcoord.y][1]].capacity) {
                    ans += chargers[Map[Acoord.x][Acoord.y][1]].capacity;
                    ans += chargers[Map[Bcoord.x][Bcoord.y][0]].capacity;
                }
                else {
                    ans += chargers[Map[Acoord.x][Acoord.y][0]].capacity;
                    ans += chargers[Map[Bcoord.x][Bcoord.y][1]].capacity;
                }
            }
        }
        else { // 두 개가 다를 때
            ans += chargers[Map[Acoord.x][Acoord.y][0]].capacity;
            ans += chargers[Map[Bcoord.x][Bcoord.y][0]].capacity;
        }
    }
}
 
int main() {
    // freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int test_case = 1; test_case <= T; ++test_case) {
        Reset();
        cin >> M >> A;
        for (int m = 0; m < M; ++m) cin >> aMove[m];
        for (int m = 0; m < M; ++m) cin >> bMove[m];
 
        for (int a = 0; a < A; ++a) {
            cin >> chargers[a].y >> chargers[a].x >> chargers[a].canCover >> chargers[a].capacity;
        }
        auto compare = [](const charger& a, const charger& b) {
            return a.capacity > b.capacity;
        };
        sort(chargers, chargers + A, compare); // 충전량 순으로 정렬
 
        // 좌표마다 충전 가능한 충전기 정리
        for (int a = 0; a < A; ++a) {
            for (int i = 1; i <= 10; ++i) {
                for (int j = 1; j <= 10; ++j) {
                    int dist = Abs(chargers[a].x, i) + Abs(chargers[a].y, j);
                    if (dist <= chargers[a].canCover) {
                        Map[i][j].push_back(a);
                    }
                }
            }
        }
 
        getMax(); // 시작점
 
        for (int t = 0; t < M; ++t) {
            Acoord.x += dx[aMove[t]];
            Acoord.y += dy[aMove[t]];
            Bcoord.x += dx[bMove[t]];
            Bcoord.y += dy[bMove[t]];
            getMax();
        }
     
        cout << "#" << test_case << " " << ans << endl;
    }
 
    return 0;
}