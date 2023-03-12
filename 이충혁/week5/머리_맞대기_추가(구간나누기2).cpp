#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int MAX = 21e8;

int N, T;
vector<int> person;

int mx = 0; // right 값 제한
int ans = MAX;

int input()
{
  cin >> N >> T;
  for (int i = 0; i < N; i++)
  {
    int temp;
    cin >> temp;
    person.push_back(temp);

    if (mx < temp)
      mx = temp;
  }
  return 0;
}

int possible_func(int mid)
{
  int box_mn = MAX; // 구간별 최소값
  int box_mx = 0;   // 구간별 최대값
  int team_cnt = 1; 
  int i;
  for (i = 0; i < N; i++)
  {
    if (box_mx < person[i])
      box_mx = person[i];
    if (box_mn > person[i])
      box_mn = person[i];

    // 구간별 최대, 최소의 차가 mid보다 크면 team_cnt 갱신 (팀수 증가)
    if (box_mx - box_mn > mid) 
    {
      team_cnt++;
      box_mx = person[i];
      box_mn = person[i];
    }
  }

  if (team_cnt <= T)
  {
    return 1;
  }

  return 0;
}

int solve_func()
{
  int left = 0;
  int right = mx;


  while (left <= right)
  {
    int mid = (left + right) / 2;

    if (possible_func(mid))
    {
      ans = mid;
      right = mid - 1;
    }
    else
    {
      left = mid + 1;
    }
  }

  cout << ans;
  return 0;
}

int main()
{
  //freopen("input.txt", "r", stdin);
  input();
  solve_func();
  return 0;
}
