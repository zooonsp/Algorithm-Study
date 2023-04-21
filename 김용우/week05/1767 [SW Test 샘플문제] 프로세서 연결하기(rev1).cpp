#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

struct Coordinate{  // 좌표 정보
    int y, x;
};

int N;  // N: 맥시노스 한 변의 cell의 수
int MAP[15][15];    // MAP[j][i]: j행 i열의 cell 정보
std::vector<Coordinate> core;   // core: core의 좌표 정보
int wireMin[15];    // wireMin[i]: i개의 core가 연결 되었을 경우 최소 전선의 길이
int visited[15];    // visited[i]: 방문 체크
int ans = 0;    // ans: 가장 많은 core를 연결하면서 가장 적은 전선 사용

// 방향 벡터 -> 좌 하 상 우
int dirY[] = {0, 1, -1, 0};
int dirX[] = {-1, 0, 0, 1};

void DFS(int num, int len){ // num: 연결된 core의 개수, len: 전선의 길이

    if(num != 0){
        wireMin[num] = std::min(wireMin[num], len); // num개의 core를 연결하였을 경우 최소 전선의 길이 업데이트
    }
    if(num == core.size())  // 모둔 core가 연결되었다면 return
        return;

    for(int i=0; i<core.size(); i++){
        if(visited[i] == 1) continue;

        for(int dir=0; dir<4; dir++){   // 4가지 방향으로 탐색
            std::vector<Coordinate> v;  // v: 전선의 좌표 정보
            int flag = -1;  //  flag: 1 이면 연결 불가능 0이면 연결 가능
            int nextY = core[i].y;  // nextY: 다음 연결할 y좌표
            int nextX = core[i].x;  // nextX: 다음 연결할 x좌표
            while(true){
                nextY += dirY[dir];
                nextX += dirX[dir];

                if(MAP[nextY][nextX] == 1 || MAP[nextY][nextX] == 2){   // 다른 Core를 만나거나, 전선을 만나 연결 못함
                    flag = 1;
                    break;
                }
                if(MAP[nextY][nextX] == -1){    // 전원에 연결 됨 -> 연결 가능
                    flag = 0;
                    break;
                }
                v.push_back({nextY, nextX});    // 경로를 벡터에 저장
            }
            if(flag == 1) continue; // 연결 못하는 경우는 continue
            
            for(int j=0; j<v.size(); j++){  // 전선 연결
                MAP[v[j].y][v[j].x] = 2;
            }
            visited[i] = 1; // 방문 체크
            DFS(num+1, len+v.size());
            for(int j=0; j<v.size(); j++){  // 전선 원상 복구
                MAP[v[j].y][v[j].x] = 0;
            }
            visited[i] = 0;

        }
    }
}

void sol(){
    DFS(0, 0);
    for(int i=0; i<15; i++){    // 가장 많이 Core를 연결한 경우 탐색
        if(wireMin[i] != 21e8)
            ans = wireMin[i];
    }
}

void input(){
    std::cin >> N;
    for(int j=1; j<=N; j++){
        for(int i=1; i<=N; i++){
            std::cin >> MAP[j][i];
            if(MAP[j][i] == 1){
                if(j==1 || j==N || i==1 || i==N) continue;  // 이미 전원에 연결되어있는 경우 continue
                core.push_back({j, i}); // Core 위치 정보 저장
            }
        }
    }
    
    return;
}

// 초기화
void reset(){
    memset(MAP, -1, sizeof(MAP));
    for(int i=0; i<15; i++){
        wireMin[i] = 21e8;
        visited[i] = 0;
    }
    while(!core.empty()){
        core.pop_back();
    }

    return;
}

int main(){
    int T;

    std::cin >> T;
    for(int tc=1; tc<=T; tc++){
        reset();
        input();
        sol();
        std::cout << '#' << tc << ' ' << ans << std::endl;
    }
}