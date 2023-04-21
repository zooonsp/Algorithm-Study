#include <string>
#include <vector>
#include <cstring>

using namespace std;

int N , M;  // N: 자물쇠의 크기, M: 열쇠의 크기
int keyArr[21][21];	// keyArr[i][j]: i행 j열의 열쇠 돌기 정보, 0 홈 1 돌기
int arr[60][60];	// arr[i][j]: i행 j열의 자물쇠 정보
constexpr int idx = 20;	// idx: 자물쇠 시작 위치 (idx, idx)

void rotate(){	// 열쇠 돌리기
    int tmpArr[21][21] = {0,};	// tmpArr[i][j]: 열쇠 회전 정보 임시 저장
    
    for(int j = 0; j < M; j++){
        for(int i = 0; i < M; i++){
            tmpArr[i][M-j-1] = keyArr[j][i];
        }
    }
    memcpy(keyArr, tmpArr, sizeof(keyArr));
    
    return;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {  
    
	int hole = 0;	// hole: 자물쇠의 홈 개수 -> 홈을 모두 채워야 자물쇠 열림

    N = lock.size();	// 자물쇠 크기
    M = key.size();	// 열쇠 크기
	    
    memset(arr, 0, sizeof(arr));	// 자물쇠 정보 초기화
    
    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
            arr[j+idx][i+idx] = lock[j][i];	// 자물쇠 정보 복사
			if(lock[j][i] == 0)
				hole++;	// 자물쇠의 홀 개수 -> 자물쇠의 홀은 꼭 열쇠의 돌기로 채워져야함
        }
    }
    for(int j=0; j<M; j++){
        for(int i=0; i<M; i++){
            keyArr[j][i] = key[j][i];	// 열쇠 정보 복사
        }
    }
    
	for(int roll = 0; roll < 4; roll++){	// 90도 회전은 총 4개의 다른 모양을 만듦      
		rotate();	// 열쇠 회전
		int len = N + (2 * M) - 2;	// len: 확인해봐야하는 경우의 수 len * len
		int startIdx = idx - M + 1;	// startIdx: 열쇠의 시작 위치
		
		for(int j = 0; j < len; j++){
			for(int i = 0; i < len; i++){
				int chk = 0;	// chk: 가능한 열쇠면 0, 아니면 1
				int cnt = 0;	// cnt: 자물쇠에 홈에 들어간 열쇠의 돌기

				for(int l = 0; l < M; l++){	// 열쇠 y 방향
					for(int k = 0; k < M; k++){	// 열쇠 x 방향
						int y = startIdx + l + j;	// y: 열쇠 비교 y축 위치
						int x = startIdx + k + i;	// x: 열쇠 비교 x축 위치
						if(y < idx || x < idx || y >= (idx + N) || x >= (idx + N) ) continue;	// 자물쇠 범위를 벗어난 곳은 continue
						if(arr[y][x] == 1){	// 자물쇠의 돌기 부분에
							if(keyArr[l][k] == 1){	// 열쇠의 돌기가 있으면 안됨 -> 홈은 괜찮음
								chk = 1;
								break;
							}
						}else{	// 자물쇠의 홈 부분에
							if(keyArr[l][k] == 0){	// 열쇠의 홈이 있으면 안됨 -> 돌기는 괜찮음
								chk = 1;
								break;
							}else{
								cnt++;	// 자물쇠의 홈을 메움
							}
						}
					}
					if(chk == 1)	// 불가능한 열쇠
						break;
				}
				if(chk == 0 && hole == cnt){	// 열쇠가 자물쇠에 들어가면서 자물쇠의 모든 홈을 메운 경우 return true
					return true;
				}
			}
		}            
	}    
    
    return false;	// 모든 경우의 수를 해봤음에도 맞는 열쇠가 없었다면 false
}