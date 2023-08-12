#include<iostream>

#include <string>
#include <vector>

using namespace std;

/*
기둥은 바닥위 있거나 보의 한쪽 끝 위에 있거나 다른 기둥 위에 있어야함.
보는 한쪽끝이 기둥 위에 이거나 양쪽 끝이 다른 보와 동시에 연결 되어 있어야함.
 
n 은 5이상 100이하
build_frame 세로는 1이상 1000이하
build_frame 가로는 4

build frame 는
지을 좌표 x, y
기둥인지 보인지 0, 1
짓는지 삭제하는지 0, 1
*/

enum BUILD_FRAME_INFO {
    X = 0,
    Y,
    KIND,
    CMD
};

enum STRUCTURE_INFO {
    POLE = 0,
    BO = 1
};

const int MAX_SIZE = 110;

int structure[MAX_SIZE][MAX_SIZE][2];

bool check_struct(int x, int y, int kind, int n)
{
    if (kind == POLE)
    {
        if (y == 0 ||
            (x > 0 && structure[x - 1][y][1]) ||
            (y < n && structure[x][y][1]) ||
            (y > 0 && structure[x][y - 1][0]))
        {
            return true;
        }
    }
    else // BO!
    {
        if ((y > 0 && structure[x][y - 1][0]) ||
            (x < n && y > 0 && structure[x + 1][y - 1][0]) ||
            (x > 0 && x < n && structure[x - 1][y][1] && structure[x + 1][y][1]))
        {
            return true;
        }
    }


    return false;
}

bool remove_struct(int x, int y, int kind, int n)
{
    structure[x][y][kind] = 0;

    if (kind == POLE)
    {
        if ((y < n && structure[x][y + 1][0] && !check_struct(x, y + 1, 0, n)) ||
            (y < n && structure[x][y + 1][1] && !check_struct(x, y + 1, 1, n)) ||
            (x > 0 && y > n && structure[x - 1][y + 1][1] && !check_struct(x - 1, y + 1, 1, n)))
        {
            return false;
        }
    }
    else // BO!
    {
        if ((structure[x][y][0] && !check_struct(x, y, 0, n)) ||
            (x < n && structure[x + 1][y][0] && !check_struct(x + 1, y, 0, n)) ||
            (x > 0 && structure[x - 1][y][1] && !check_struct(x - 1, y, 1, n)) ||
            (x < n && structure[x + 1][y][1] && !check_struct(x + 1, y, 1, n)))
        {
            return false;
        }
    }


    return true;
}


vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;

    for (auto& frame : build_frame)
    {
        if (frame[CMD] == 1)
        {
            if(check_struct(frame[X], frame[Y], frame[KIND], n))
                structure[frame[X]][frame[Y]][frame[KIND]] = 1;
        }
        else
        {
            if(!remove_struct(frame[X], frame[Y], frame[KIND], n))
                structure[frame[X]][frame[Y]][frame[KIND]] = 1;
        }
    }

    // 출력
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (structure[i][j][POLE])
                answer.push_back({ i, j, POLE });
            if (structure[i][j][BO])
                answer.push_back({ i, j, BO });
        }
    }

    return answer;
}


int main()
{
    solution(5, { {1, 0, 0, 1},{1, 1, 1, 1},{2, 1, 0, 1},{2, 2, 1, 1},{5, 0, 0, 1},{5, 1, 0, 1},{4, 2, 1, 1},{3, 2, 1, 1} });
    //solution(5, { {0, 0, 0, 1},{2, 0, 0, 1},{4, 0, 0, 1},{0, 1, 1, 1},{1, 1, 1, 1},{2, 1, 1, 1},{3, 1, 1, 1},{2, 0, 0, 0},{1, 1, 1, 0},{2, 2, 0, 1} });

    return 0;
}