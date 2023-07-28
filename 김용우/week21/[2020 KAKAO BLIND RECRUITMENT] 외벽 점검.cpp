#include <string>
#include <vector>
#include <algorithm>

constexpr int INF = 21e8;   // INF: 나올 수 없는 값

int solution(int n, std::vector<int> weak, std::vector<int> dist) { // n: 외벽의 총 둘레, weak[i]: i 번째 취약한 지점, dist[i]: i 친구가 1시간 동안 이동할 수 있는 거리
    
    int answer = INF;   // answer: 취약 지점을 점검하기 위해 보내야 하는 친구 수의 최소값
    
    int weakSize = weak.size(); // weakSize: 취약한 지점의 개수
    int distSize = dist.size(); // distSize: 친구들의 수
    
    weak.resize(weakSize*2);    // 성벽은 원형으로 구성되어 있기 때문에 같은 배열을 한번 더 복사하여 사용
    
    for(int i=0; i<weakSize; ++i){
        weak[weakSize+i] = weak[i] + n; // 반복되는 취약점은 외벽의 총 둘레 + 위치
    }
    
    std::sort(dist.begin(), dist.end());    // 순열을 사용하기 위해 오름차순 정렬
    
    do{
        for(int i=0; i<weakSize; ++i){
            int left = weak[i]; // left: 0에서 가장 가까운 취약점
            int right = weak[i + weakSize - 1]; // right: 0에서 가장 먼 취약점 -> 이 지점을 넘어가면 모든 취약점에 대하여 검사를 했다고 판단
            
            for(int j=0; j<distSize; ++j){  // 순열에 따라 첫 번째 친구부터 점검하기 위해 보냄
                left += dist[j];    // left 까지는 점검 완료
                
                if(left >= right){  // 가장 먼 취약점 꺼지 검사를 완료
                    answer = std::min(answer, j + 1);   // 내보낸 친구의 수 갱신
                    break;
                }
                
                int next = upper_bound(weak.begin(), weak.end(), left)  - weak.begin();  // 다음 탐색을 시작할 위치는 마지막으로 점(left)를 초과하는 위치 중 취약점이 있는 위치
                left = weak[next];  // left를 갱신 -> 해당 취약점부터 친구를 내보내 탐색 계속
            }
        }
    }while(next_permutation(dist.begin(), dist.end())); // 중복되지 않는 다음 조합 생성
        
    if(answer == INF) answer = -1;  // 친구들을 모두 투입해도 취약 지점을 전부 점검할 수 없는 경우 -1
    
    return answer;
}