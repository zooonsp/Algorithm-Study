// https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/#%EB%AC%B8%EC%A0%9C-6-%ED%8C%8C%EA%B4%B4%EB%90%98%EC%A7%80-%EC%95%8A%EC%9D%80-%EA%B1%B4%EB%AC%BC
// ¹Ì¶í..
// O(K + N * M)
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skill)
{
    int answer = 0;
    int row = (int)board.size(), col = (int)board[0].size();

    vector<vector<int>> updates(row, vector<int>(col, 0));

    for (vector<int> &sk : skill)
    {
        auto [type, r1, c1, r2, c2, degree] = make_tuple(sk[0], sk[1], sk[2], sk[3], sk[4], sk[5]);
        if (type == 1)
            degree = -degree;
        updates[r1][c1] += degree;
        if (r2 + 1 < row)
            updates[r2 + 1][c1] += -degree;
        if (c2 + 1 < col)
            updates[r1][c2 + 1] += -degree;
        if (r2 + 1 < row && c2 + 1 < col)
            updates[r2 + 1][c2 + 1] += degree;
    }

    // Çò°¥¸®¸é µû·Îµû·Î
    for (int i{0}; i < row; ++i)
    {
        for (int j{0}; j < col; ++j)
        {
            if (i)
                updates[i][j] += updates[i - 1][j];
            if (j)
                updates[i][j] += updates[i][j - 1];
            if (i && j)
                updates[i][j] -= updates[i - 1][j - 1];
            if (board[i][j] + updates[i][j] > 0)
                ++answer;
        }
    }

    return answer;
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<vector<int>> board{{5, 5, 5, 5, 5}, {5, 5, 5, 5, 5}, {5, 5, 5, 5, 5}, {5, 5, 5, 5, 5}};
    vector<vector<int>> skill{{1, 0, 0, 3, 4, 4}, {1, 2, 0, 2, 3, 2}, {2, 1, 0, 3, 1, 2}, {1, 0, 1, 3, 3, 1}};

    // vector<vector<int>> board{ {1, 2, 3},{4, 5, 6},{7, 8, 9}};
    // vector<vector<int>> skill{ {1,1,1,2,2,4}, {1,0,0,1,1,2},{ 2,2,0,2,0,100} };

    cout << solution(board, skill) << '\n';
} // https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/#%EB%AC%B8%EC%A0%9C-6-%ED%8C%8C%EA%B4%B4%EB%90%98%EC%A7%80-%EC%95%8A%EC%9D%80-%EA%B1%B4%EB%AC%BC
// ¹Ì¶í..
// O(K + N * M)
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skill)
{
    int answer = 0;
    int row = (int)board.size(), col = (int)board[0].size();

    vector<vector<int>> updates(row, vector<int>(col, 0));

    for (vector<int> &sk : skill)
    {
        auto [type, r1, c1, r2, c2, degree] = make_tuple(sk[0], sk[1], sk[2], sk[3], sk[4], sk[5]);
        if (type == 1)
            degree = -degree;
        updates[r1][c1] += degree;
        if (r2 + 1 < row)
            updates[r2 + 1][c1] += -degree;
        if (c2 + 1 < col)
            updates[r1][c2 + 1] += -degree;
        if (r2 + 1 < row && c2 + 1 < col)
            updates[r2 + 1][c2 + 1] += degree;
    }

    // Çò°¥¸®¸é µû·Îµû·Î
    for (int i{0}; i < row; ++i)
    {
        for (int j{0}; j < col; ++j)
        {
            if (i)
                updates[i][j] += updates[i - 1][j];
            if (j)
                updates[i][j] += updates[i][j - 1];
            if (i && j)
                updates[i][j] -= updates[i - 1][j - 1];
            if (board[i][j] + updates[i][j] > 0)
                ++answer;
        }
    }

    return answer;
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<vector<int>> board{{5, 5, 5, 5, 5}, {5, 5, 5, 5, 5}, {5, 5, 5, 5, 5}, {5, 5, 5, 5, 5}};
    vector<vector<int>> skill{{1, 0, 0, 3, 4, 4}, {1, 2, 0, 2, 3, 2}, {2, 1, 0, 3, 1, 2}, {1, 0, 1, 3, 3, 1}};

    // vector<vector<int>> board{ {1, 2, 3},{4, 5, 6},{7, 8, 9}};
    // vector<vector<int>> skill{ {1,1,1,2,2,4}, {1,0,0,1,1,2},{ 2,2,0,2,0,100} };

    cout << solution(board, skill) << '\n';
}