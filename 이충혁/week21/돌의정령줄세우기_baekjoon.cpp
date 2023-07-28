#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 70707;

int N; // 돌의 정령 무리 수

int A[MAX_SIZE]; // 입력 받는 A 배열
int ans[MAX_SIZE];

int input()
{
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    return 0;
}

int solve_func()
{
    int mn = 0, mx = N + 1;

    for (int i = 0; i < N; i++)
    {
        if (A[i] < 0)
            ans[i] = (++mn);
        else
            ans[i] = (--mx);
    }


    if (A[N - 1] < 0)
        cout << -1;
    else
        for (int i = 0; i < N; i++)
            cout << ans[i] << " ";

    return 0;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);

    input();
    solve_func();

    return 0;
}