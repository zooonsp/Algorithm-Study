#include <string>
#include <vector>

using namespace std;

struct Skill {
    vector<vector<int>> board;
    Skill(int row, int column);
    void add(vector<int> &query);
    void process_queries();
};

Skill::Skill(int row, int column) {
    board = vector<vector<int>>(row + 1, vector<int>(column + 1, 0));
}

void Skill::add(vector<int> &query) {
    int &type = query[0];
    int degree = type == 1 ? - query[5] : query[5];
    int &r1 = query[1];
    int &c1 = query[2];
    int &r2 = query[3];
    int &c2 = query[4];
    board[r1][c1] += degree;
    board[r1][c2 + 1] += -degree;
    board[r2 + 1][c1] += -degree;
    board[r2 + 1][c2 + 1] += degree;
}

void Skill::process_queries() {
    int row = board.size() - 1;
    int column = board[0].size() - 1;
    for(int row_it = 0; row_it < row; ++row_it) {
        for(int column_it = 1; column_it < column; ++column_it) {
            board[row_it][column_it] += board[row_it][column_it - 1];
        }
    }
    for(int column_it = 0; column_it < column; ++column_it) {
        for(int row_it = 1; row_it < row; ++row_it) {
            board[row_it][column_it] += board[row_it - 1][column_it];
        }
    }
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int row = board.size();
    int column = board[0].size();
    Skill merged(row, column);
    for(vector<int> &query : skill) {merged.add(query);}
    merged.process_queries();
    int answer = 0;
    for(int row_it = 0; row_it < row; ++row_it) {
        for(int column_it = 0; column_it < column; ++column_it) {
            answer += board[row_it][column_it] + merged.board[row_it][column_it] > 0 ? 1 : 0;
        }
    }
    return answer;
}