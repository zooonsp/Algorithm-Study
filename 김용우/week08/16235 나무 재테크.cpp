#include <iostream>
#include <algorithm>

int N, M, K;    // N: 땅의 한 변의 길이, M: 상도가 심은 나무의 수, K: 년도
int A[10][10];    // A[i][j]: S2D2가 추가하는 양분
int FOOD[10][10];   // FOOD[i][j]: i행 j열의 양분
int TREES[10][10][1100];  // TREES[i][j][k]: i행 j열의 나무 나이 k  -> TREES[i][j][0]에 i행 j열 나무의 최대 나이 저장
int ALIVETREES[10][10][1100];    // ALIVETREES[i][j]: i행 j열의 산 나무의 나이 k -> ALIVETREES[i][j][0]에 i행 j열 나무의 최대 나이 저장
int DEADTREES[10][10];  // DEADTREES[i][j]: i행 j열의 죽은 나무가 변한 양분
int ans;

// 방향 벡터
int dirY[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dirX[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void sol(){
    // 가장 처음 양분은 모든 칸에 5
    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
            FOOD[j][i] = 5;
        }
    }

    while(K>0){
        // 봄
            // 어린 나무부터 자신의 나이만큼 양분을 먹고 나이가 1증가
            // 양분이 부족하면 즉시 죽음
        for(int j=0; j<N; j++){
            for(int i=0; i<N; i++){
                if(TREES[j][i][0] == 0) continue;   // j행 i열에 가장 나이가 많은 나무가 0 살이면 continue
                for(int k=1; k<=TREES[j][i][0]; k++){
                    if(TREES[j][i][k] == 0) continue;   // j행 i열에 k살인 나무가 없으면 continue

                    int age = k;    // age: 나무의 나이
                    int cnt = TREES[j][i][k];   // cnt: age 나이인 나무의 수

                    for(int l=0; l<cnt; l++){
                        FOOD[j][i] -= age;
                        if(FOOD[j][i] >= 0){    // 자신의 나이만큼 양분을 먹을 수 있다면
                            ALIVETREES[j][i][age+1]++;  // 살아있는 나무에 추가 -> 나이 증가에 유의
                            ALIVETREES[j][i][0] = std::max(ALIVETREES[j][i][0], age+1); // 나이 최대값 갱신
                        }else{  // 자신의 나이만큼 양분을 먹을 수 없다면
                            DEADTREES[j][i] += age / 2; // 나이를 2로 나눈 값이 양분으로 추가
                            FOOD[j][i] += age;  // 땅 양분 복구
                        }   
                    }
                    TREES[j][i][k] = 0; // k 나이 나무 수 초기화
                }
                TREES[j][i][0] = 0; // j행 i열의 최대 나무 나이 초기화
            }
        }
        // 여름
            // 봄에 죽은 나무가 양분으로 변함
            // 각각의 죽은 나무마다 나이를 2로 나눈 값
        for(int j=0; j<N; j++){
            for(int i=0; i<N; i++){
                FOOD[j][i] += DEADTREES[j][i];  // 양분 추가
                DEADTREES[j][i] = 0;    // 양분 주고 0으로 변화
            }
        }
        // 가을
            // 나이가 5배수인 나무 인접한 8칸에 번식
        for(int j=0; j<N; j++){
            for(int i=0; i<N; i++){
                if(ALIVETREES[j][i][0] == 0) continue;  // j행 i열에 가장 나이가 많은 나무가 0 살이면 continue
                for(int k=1; k<=ALIVETREES[j][i][0]; k++){
                    if(ALIVETREES[j][i][k] == 0) continue;  // j행 i열에 k살인 나무가 없으면 continue

                    int age = k;    // age: 나무의 나이
                    int cnt = ALIVETREES[j][i][k];  // cnt: age 나이인 나무의 수

                    // 값 복사
                    TREES[j][i][k] = cnt;
                    TREES[j][i][0] = std::max(TREES[j][i][0], age);

                    if(k%5 == 0){   // 나무의 나이가 5의 배수이기 때문에 번식
                        for(int dir = 0; dir < 8; dir++){
                            // newY, newX: 인접한 칸 (8 방향)
                            int newY = j + dirY[dir];
                            int newX = i + dirX[dir];

                            if(newY < 0 || newX < 0 || newY >= N || newX >= N) continue;    // 상도의 땅 벗어나는 칸에는 나무가 생기지 않음

                            TREES[newY][newX][1] += cnt;    // 1살 나무 나무의 수만큼 증가
                            TREES[newY][newX][0] = std::max(TREES[newY][newX][0], 1);   // 최대값 갱신
                        }
                    }
                    ALIVETREES[j][i][k] = 0;    // k 나이 살아있는 나무 수 초기화
                }
                ALIVETREES[j][i][0] = 0;    // j행 i열에 살아남은 나무 최대 나이 초기화
            }
        }
        // 겨울
            // 땅에 양분을 추가
        for(int j=0; j<N; j++){
            for(int i=0; i<N; i++){
                FOOD[j][i] += A[j][i];
            }
        }
        K--;    // 1년 지남
    }

    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
            if(TREES[j][i][0] == 0) continue;   // j행 i열에 나무 없으면 continue
            for(int k=1; k<=TREES[j][i][0]; k++){
                if(TREES[j][i][k] == 0) continue; // j행 i열에 k 나이 나무 없으면 continue
                ans += TREES[j][i][k];  // 남아있는 나무 수 카운트
            }
        }
    }

    return;
}

void input(){
    std::cin >> N >> M >> K;
    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
            std::cin >> A[j][i];    // 매년 로봇 S2D2에 추가되는 양분
        }
    }
    for(int m=0; m<M; m++){
        int y, x, z;    //  y, x: 나무 위치(1~N), z: 나무의 나이
        std::cin >> y >> x >> z;
        y--;
        x--;
        TREES[y][x][z]++;   // y행 x열의 z나이 나무 증가
        TREES[y][x][0] = std::max(TREES[y][x][0], z);   // y행 x열의 0번째 인덱스에 y행 x열에 있는 나무의 최대 나이 저장
    }
    
    return;
}

int main(){
    input();
    sol();
    std::cout << ans;

    return 0;
}