// 출처 : https://ljhyunstory.tistory.com/146ㄴ

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 보드가 5*5 이니 완전 탐색 하자
// 순서가 오면 모든 경우를 dfs로 끝까지 가본다 (A, B 는 각 순서에 맞춰 교대로 재귀된다)
// 그 순서에 어떤 경우라도 이기는 경우가 없다면 늦게 지는 멀리간 값을 저장
// 이기는 경우가 있다면 가장 빨리 이기는 경우의 빨리 이기는 가까운 값을 저장
// 반복하며 횟수를 세자
// dfs에서 넘어온 횟수가 짝수면 플레이어의 패배
// 홀수면 승리가 된다.


const int dy[4] = { -1,1,0,0 };
const int dx[4] = { 0,0,-1,1 };

struct coordi
{
    int y, x;

};


int row, col;

int visited[5][5];
// 1 : 발판이 사라짐을 의미한다. -> 1갱신을 다른 곳으로 이동할 때 해줘야하고 있는곳이 사라지는 것을 재귀할 때 마다 체크하자
vector<vector<int>> board_copy;


int dfs(coordi now_play, coordi next_play)
{

    if (visited[now_play.y][now_play.x])
    {
        return 0;
    }

    int ret = 0;

    for (int i = 0; i < 4; i++)
    {
        coordi pt = now_play;
        pt.y += dy[i];
        pt.x += dx[i];

        if (pt.y < 0 || pt.y >= row ||
            pt.x < 0 || pt.x >= col) continue;

        if (visited[pt.y][pt.x] == 1) continue;

        if (board_copy[pt.y][pt.x] == 0) continue;


        visited[now_play.y][now_play.x] = 1;
        int win = dfs(next_play, pt) + 1;
        visited[now_play.y][now_play.x] = 0;

        // 처음 승리 값이 들어오면 갱신한다.
        if (ret % 2 == 0 && win % 2 == 1)
            ret = win; 
   
        // 지금 까지 모든 경우가 패배이면 늦게 지는 걸 선택한다
        else if (ret % 2 == 0 && win % 2 == 0) {
            ret = max(ret, win); 
        }
        // 이전에도 승리한 적이 있다면 둘중 빨리 이기는 것을 선택한다
        else if (ret % 2 == 1 && win % 2 == 1) {
            ret = min(ret, win);
        }

    }
    return ret;
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
 

    board_copy = board;
    row = board.size();
    col = board[0].size();

    int answer = dfs({ aloc[0], aloc[1] }, { bloc[0], bloc[1] });

    return answer;
}

int main()
{
    int ans;
    ans = solution({ {1, 1, 1}, {1, 1, 1}, {1, 1, 1} }, { 1, 0 }, { 1, 2 });
    /*
    ans = solution({1, 1, 1}, {1, 0, 1}, {1, 1, 1}}	{1, 0},	{1, 2});
    ans = solution({{1, 1, 1, 1, 1}},	{0, 0},	{0, 4});
    ans = solution({{1}},	{0, 0},	{0, 0});
    */
    cout << ans;
    return 0;
}