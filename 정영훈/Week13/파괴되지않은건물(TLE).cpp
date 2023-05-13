#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

struct Data
{
    int value; // 각 열마다 넣어야 하는 값
    int cnt;   // 넣어야 하는 개수
    Data(int value, int cnt) : value(value), cnt(cnt) {}
};

int solution(vector<vector<int>> board, vector<vector<int>> skill)
{
    int answer = 0;
    int row = (int)board.size(), col = (int)board[0].size();

    vector<vector<vector<Data>>> updates(row, vector<vector<Data>>(col));

    for (vector<int> &sk : skill)
    {
        auto [type, r1, c1, r2, c2, degree] = make_tuple(sk[0], sk[1], sk[2], sk[3], sk[4], sk[5]);
        // type r1 c1 r2 c2 degree
        if (type == 1)
        { // attack
            degree = -degree;
        }
        for (int r{r1}; r <= r2; ++r)
        {
            updates[r][c1].push_back(Data(degree, c2 - c1 + 1));
        }
    }

    for (int i{}; i < row; ++i)
    {
        for (int j{}; j < col; ++j)
        {
            for (Data &d : updates[i][j])
            {
                board[i][j] += d.value;
                if (d.cnt > 1)
                    updates[i][j + 1].push_back(Data(d.value, d.cnt - 1));
            }
            if (board[i][j] > 0)
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
    cout << solution(board, skill) << '\n';
}