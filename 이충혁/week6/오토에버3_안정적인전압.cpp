#include<iostream>
#include<unordered_map>
using namespace std;
const int MAX_ARR = 202020;

int N;

long long ori_arr[MAX_ARR]; // 원본 전압 변동 정보
long long add_arr[MAX_ARR]; // 전압 변동 결과 (원본이 더해진 정보)
long long zero_cnt[MAX_ARR]; // 각 부분 마다 0값 카운트 ( left )
unordered_map<int, int> DAT; // 전압 + MAX_ARR 의 DAT

int input()
{
    cin >> N;

    cin >> ori_arr[0];
   

    for (int i = 0; i < N; i++)
    {
        cin >> ori_arr[i];
        
        if (i == 0)
        {
            add_arr[i] = ori_arr[i];
            if (add_arr[i] == 0) // i가 0일 떄 i-1 연산 못해서 따로
                zero_cnt[i] = 1;
            else
                zero_cnt[i] = 0;
        }
        else
        {
            add_arr[i] = add_arr[i - 1] + ori_arr[i];
            if (add_arr[i] == 0)
                zero_cnt[i] = zero_cnt[i - 1] + 1;
            else
                zero_cnt[i] = zero_cnt[i - 1];
        }


        // DAT에 넣어주기

        if (DAT.find(add_arr[i]) == DAT.end())
        {
            DAT.insert({ add_arr[i], 1});
        }
        else
        {
            DAT[add_arr[i]]++;
        }
    }

    return 0;
}

// 

int solve_func()
{
    int ans = 0;

    for (int i = 0; i < N; i++)
    {
        int zero_now = 0; // 이번 index의 0 개수
        
        if (i != 0) // 현재 바뀌는 값의 left에 있는 0 개수를 더함
        {
            zero_now += zero_cnt[i - 1];
        }

        // 바뀌는 index 부터 0으로 바꿀 수 있는 값들을 모두  더함 (right)
        if (DAT.find(ori_arr[i]) != DAT.end())
        {
            zero_now += DAT[ori_arr[i]];
        
        }

        DAT[add_arr[i]]--;

        if (ans < zero_now)
            ans = zero_now;
    }

    return ans;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);

    input();
    

    cout << solve_func();
    return 0;
}