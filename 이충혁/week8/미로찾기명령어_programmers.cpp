#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

const int DIR = 4;

enum {
    DOWN, LEFT, RIGHT, UP
};

struct coordi {
    int x, y;
};

bool possible_func(int dist, int k)
{
    // 1. 거리가 k 보다 클 때
    if (dist > k)
        return false;

    // 2. dist 와 k 가 홀짝이 다를 때
    if (dist % 2 != k % 2)
        return false;

    return true;
}


// n, m : 격자 좌표
// x, y : 출발 - x, r 이 세로축 이다 조심하자
// r, c : 도착
string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";

    // 4가지 방향 DAT (몇번인지 카운트)
    int DAT[DIR] = { 0, };

    int dist = abs(x - r) + abs(y - c);

    // 도착지 에 도착이 가능한지 판단 ( 거리, 홀수 짝수 )
    if (!possible_func(dist, k)) {
        answer = "impossible";
        return answer;
    }

    // 도착지 출발지 차이로 필수로 가져야 하는 방향 갯수 계산
    if (r - x >= 0)
        DAT[DOWN] = r - x;
    else
        DAT[UP] = x - r;

    if (c - y >= 0)
        DAT[RIGHT] = c - y;
    else
        DAT[LEFT] = y - c;

    // k 와 dist차이 / 2 만큼 왓다갓다 해야함
    // 왓다갓다 의 조건 은
    // 1. 정해진 좌표 한계를 초과하면 안되고
    // 2. (d, u), (l, r), (r, l) 의 왓다갓다만 유효함 (u, d)는 백과사전 밀림
    // 3. (d, u), (l, r)은 따로 안세도 되지만 (r, l) 은 l 문자열 추가하는 부분 뒤에 추가 할 예정이므로 따로 빼자
    int return_cnt = (k - dist) / 2;
    coordi now = { x + DAT[DOWN], y - DAT[LEFT] }; // 문자열 대로면 down과 left가 먼저오니 미리 더한다.
    int RL_cnt = 0;
    while (return_cnt > 0)
    {
        return_cnt--; // continue 할거라 미리 cnt 빼주기

        if (now.x + 1 <= n) // 시작점에서 밑으로 가도
        {
            DAT[DOWN]++;
            DAT[UP]++;
            now.x++;
            continue;
        }

        else if (now.y - 1 > 0)
        {
            DAT[LEFT]++;
            DAT[RIGHT]++;
            now.y--;
            continue;
        }

        // 나머지 는 r, l 
        RL_cnt++;
    }


    // answer 문자열을 만들자
    //  DOWN, LEFT, RIGHT, UP 순서
    for (int i = 0; i < 4; i++) // 문자 작은거 순서대로
    {
        while (DAT[i] > 0)
        {
            switch (i)
            {
            case 0:
                answer += 'd';
                break;
            case 1:
                answer += 'l';
                break;
            case 2:
                answer += 'r';
                break;
            case 3:
                answer += 'u';
                break;

            }

            DAT[i]--;
        }

        if (i == LEFT)
        {
            while (RL_cnt > 0)
            {
                answer += "rl";
                RL_cnt--;
            }
        }
    }

    return answer;
}

int main()
{
    //cout <<solution(3,	3,	1,	2,	3,	3,	4);
    //cout << solution(3, 4, 2, 3, 3, 1, 5);
    //cout << solution(2, 2, 1, 1, 2, 2, 2);

    return 0;
}