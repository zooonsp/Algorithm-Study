#include <iostream>
#include <algorithm>

int N, T;   // N: 사람 수, T: 팀의 수
int arr[501];   // arr[i]: i의 두뇌회전 속도
int sum = 0;    // sum: N명의 두뇌 회전 속도의 총합
int min = 21e8, max = -21e8;    // min: 가장 낮은 두뇌회전 속도, max: 가장 높은 두뇌회전 속도
int ans;    // ans: 정답

int func(int headSum){
    int teamMin = 21e8; // teamMin: headSum을 만족하도록 하는 가장 적은 팀의 수
    int maxSum = 0; // maxSum: 가장 head sum이 큰 팀의 head sum

    for(int start=0; start<N; start++){ // N명이 있으니 N개의 시작점이 생김        
        int tempTeam = 0;   // tempTeam: 팀의 수
        sum = 0;    // headsum 0으로 초기화
        for(int i=0; i<N; i++){ // 모든 사람에 대해 조사하며
            sum += arr[(start + i)%N];
            if(sum >= headSum){ // 목표로 하는 head sum 보다 head sum이 큰 팀이 만들어짐
                tempTeam++; // 팀 증가 하고
                maxSum = std::max(maxSum, sum-arr[(start + i)%N]);  // 가장 큰 head sum 갱신 후
                sum = arr[(start + i)%N];   // 다시 더 해 나가기 시작
            }
        }
        if(sum != 0)    // 남은 sum이 있다면
            tempTeam++; // 팀 한개 추가
        teamMin = std::min(teamMin, tempTeam);  // 해당 head sum 조건에서 가장 적은 팀을 만든것이 필요함
    }
    if(teamMin == T){
        ans = maxSum;   //  조건을 만족하면서 가장 큰 head sum이 정답
    }

    return teamMin;
}

void sol(){
    int left = min * (N/T+1);   // left: N명의 사람이 모두 min의 회전속도를 갖는다고 할 경우 T개의 탐으로 나누면 left가 최저
    int right = max * (N/T+1);  // right: N명의 사람이 모두 max의 회전속도를 갖는다고 할 경우 T개의 팀으로 나누면 right가 최대

    while(left<=right){
        int mid = (left+right) / 2;
        int teamNum = func(mid);    // teamNum: mid의 head sum으로 만들어지는 team의 수

        if(teamNum == T){   // 목표로하는 T개의 팀이 만들어짐
            right = mid - 1;    // 목표로 하는 것은 목표로하는 팀이 만들어지고 나서도 head sum이 가장 작아야 하므로 계속 진행
        }else if(teamNum > T){  // 팀이 너무 많이 만들어 지면
            left = mid + 1; // head sum이 너무 작으니 크게 
        }else if(teamNum < T){  // 팀이 너무 적게 만들어 지면
            right = mid - 1;    // head sum이 너무 크기 작게
        }
    }
}

void input(){
    std::cin >> N >> T;
    for(int i=0; i<N; i++){
        std::cin >> arr[i];
        // min과 max는 이진탐색의 범위를 정할 때 사용함
        min = std::min(min, arr[i]);    // min: 가장 낮은 두뇌 회전 속도
        max = std::max(max, arr[i]);    // max: 가장 높은 두뇌 회전 속도
    }

    return;
}

int main(){
    input();
    sol();
    std::cout << ans;
    return 0;
}