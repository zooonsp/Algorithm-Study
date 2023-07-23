#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = 987654321;
    int weakSize = weak.size();

    // 원형인 상태를 선형으로 바꾸는 작업
    for (int i = 0; i < weakSize; ++i) {
        weak.push_back(weak[i] + n);
    }    
    
    // next_permutation을 사용하기 위한 초기 작업(오름차순)
    sort(dist.begin(), dist.end());
    
  
    do {
        
        for (int i = 0; i < weakSize; ++i) {
            int s = weak[i];
            // 한 바퀴 돌고나서 자기 자신의 인덱스
            int e = weak[i + weakSize - 1];
            
            for (int j = 0; j < dist.size(); ++j) 
            {
                // 주어진 이동거리만큼 이동
                s += dist[j];
                
                // 한 바퀴를 돌거나 넘는경우
                if (s >= e) {
                    // dist 인덱스에 + 1이 투입된 인원
                    answer = min(answer, j+ 1);
                    break;
                }
                
                // s -> e까지 실패했다면 s를 갱신시켜줘야함
                for (int k = i + 1; k < i + weakSize; ++k) {
                    if (weak[k] > s) {
                        s = weak[k];
                        break;
                    }
                }
            }
        }
        //순열 사용(중복도 제거해줌)
    } while(next_permutation(dist.begin(), dist.end()));
    
    if (answer == 987654321) return -1;
    
    return answer;
}
