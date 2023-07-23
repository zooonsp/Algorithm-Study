#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAX_ANS = 21e8;

int solution(int n, vector<int> weak, vector<int> dist) {

    int answer = MAX_ANS;

    sort(dist.begin(), dist.end(), greater<>());
    // 한바퀴 더 돌리기 위해 weak 2배 만들어 주기
    int weak_size = weak.size(); // 미리 size 안정해주면 무한루프
    for (int i = 0; i < weak_size; i++)
        weak.push_back(n + weak[i]);


    for (int w = 0; w < weak_size; w++)
    {
        int fail_flag = 0; // 수리가 불가능한 경우 check
        int total; // 몇명의 친구가 수리에 투입 됐는지
        int cnt; // 친구가 몇개의 벽을 수리했는지
        int friend_num; // 벽을 어떤 친구가 수리하는지

        while (1)
        {
            // 순열 바뀔 때마다 초기화
            friend_num = 0;
            cnt = 0;
            total = 0;
            fail_flag = 0;

            // 수리해야할 벽을 w 부터 한바퀴 돌린다.
            for (int i = w; i < weak_size + w; i++)
            {
                if (cnt == 0) // 시작지점 continue;
                {
                    cnt++;
                    continue;
                }

                // 이번 수리해야할 외벽 까지가 갈수 있는 거리를 초과 했을 때
                if (dist[friend_num] - (weak[i] - weak[i - 1]) < 0)
                {
                    i--;
                    cnt = 0;
                    total++;
                    if (total + 1 >= answer || total == dist.size())
                    {
                        fail_flag = 1;
                        break;
                    }
                    friend_num++;
                }
                else
                {
                    cnt++;
                    dist[friend_num] = dist[friend_num] - (weak[i] - weak[i - 1]);
                }

            }

            // 외벽을 수리하는게 성공했고, 최소가 갱신되면 답 갱신
            if (fail_flag == 0 && answer > total + 1)
            {
                answer = total + 1;
            }

            // 순열 돌리자
            if (!prev_permutation(dist.begin(), dist.end()))
            {
                break;
            }
        }
    }


    if (answer == MAX_ANS) 
        answer = -1;

    return answer;
}

int main()
{
    int ans = 0;

    //ans = solution(12, { 1, 5, 6, 10 }, { 1, 2, 3, 4 });
    // ans = solution(12, {1, 3, 4, 9, 10}	{3, 5, 7});
    ans = solution(200, { 0, 100 }, { 1, 1 });

    cout << ans;

    return 0;
}