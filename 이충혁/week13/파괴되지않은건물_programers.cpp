#include<iostream>

#include <string>
#include <vector>
using namespace std;

const int MAT_MAX = 1010;

enum SKILL_INFO {
    TYPE = 0, R1, C1, R2, C2, DEGREE
};

// 공격인지, 회복인지 의미하고 TYPE 그대로 가져다 쓰려고 3으로 잡음
const int type_weight[3] = { 0, -1, 1 };

// 2차원 prefix sum 으로 풀자
// 1. 입력으로 들어오는 각 skill 의 degree를 저장
// 250000( skill max ) * 500( degree max) = 125,000,000 int 형 가능
// r1 + 1, c1 + 1 하나에만 저장하고, r2 + 2, c2 + 2 에 한번 더 저장
// r1 + 1, c2 + 2 와 r2 + 2, c1 + 1 에 -1 곱해서 하나씩 저장
// 모든 좌표에 + 1 하는 이유는 prefix sum 할 때 1, 1 부터 하려고 
// 다 저장 후 prefix sum 하고 마지막에 board 랑 연산해서  이게 > 0 이면 answer 증가

int MAT[MAT_MAX][MAT_MAX];

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;

    // 모든 스킬 돌려가면서 prefix sum 저장 하자
    // 크기 더 많이 잡아놔서 울타리 비교 안해도 됨!
    for (auto once : skill)
    {
        MAT[once[R1] + 1][once[C1] + 1] += type_weight[once[TYPE]] * once[DEGREE];
        MAT[once[R2] + 2][once[C2] + 2] += type_weight[once[TYPE]] * once[DEGREE];
        MAT[once[R1] + 1][once[C2] + 2] += type_weight[once[TYPE]] * once[DEGREE] * -1;
        MAT[once[R2] + 2][once[C1] + 1] += type_weight[once[TYPE]] * once[DEGREE] * -1;
    }

    // prefixsum 하자!
    for (int i = 1; i <= board.size(); i++)
    {
        for (int j = 1; j <= board[0].size(); j++)
        {
            MAT[i][j] += (MAT[i - 1][j] + MAT[i][j - 1] - MAT[i - 1][j - 1]);

            // 원래 건물 내구도 더해서 내구도 0이 아니라면 answer 증가
            if (0 < MAT[i][j] + board[i - 1][j - 1])
                answer++;
        }
    }

    return answer;
}


int main()
{
    int ans = solution({ {5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5},{5,5,5,5,5} },
        { {1, 0, 0, 3, 4, 4},{1, 2, 0, 2, 3, 2},{2, 1, 0, 3, 1, 2},{1, 0, 1, 3, 3, 1} });

    cout << ans;
    return 0;
}