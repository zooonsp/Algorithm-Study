#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

enum class DIR : int { CW, CCW };

unordered_map<char, int> face2idx{{'U', 0}, {'D', 1}, {'F', 2}, {'B', 3},
                                  {'L', 4}, {'R', 5}, {'T', 6}};

int idx2face[6] = {'U', 'D', 'F', 'B', 'L', 'R'};
char idx2color[6] = {'w', 'y', 'r', 'o', 'g', 'b'};

class Cube {
private:
  char board[7][3][3];

  void faceCpy(char des, char ori, int level = 3) {
    for (int y = 0; y < level; y++)
      for (int x = 0; x < 3; x++)
        board[face2idx[des]][y][x] = board[face2idx[ori]][y][x];
  }

  void faceRotate(char src, DIR dir, int cnt = 1) {
    for (int i = 0; i < cnt % 4; i++) {
      char(*temp)[3] = board[face2idx['T']];

      for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
          if (dir == DIR::CW)
            temp[x][2 - y] = board[face2idx[src]][y][x];
          else if (dir == DIR::CCW)
            temp[2 - x][y] = board[face2idx[src]][y][x];

      faceCpy(src, 'T');
    }
  }

public:
  Cube() {
    for (int i = 0; i < 6; i++)
      for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
          board[i][y][x] = idx2color[i];
  }

  void front2up() {
    string order = "TBUFDT";

    for (int i = 0; i < 5; i++)
      faceCpy(order[i], order[i + 1]);

    faceRotate('L', DIR::CCW);
    faceRotate('R', DIR::CW);
  }

  void front2right() {
    string order = "TBRFLT";

    faceRotate('B', DIR::CW, 2);

    for (int i = 0; i < 5; i++)
      faceCpy(order[i], order[i + 1]);

    faceRotate('B', DIR::CW, 2);

    faceRotate('U', DIR::CCW);
    faceRotate('D', DIR::CW);
  }

  void rotateTop(DIR dir) {
    faceRotate('U', dir);

    string order;

    if (dir == DIR::CW)
      order = "TBLFRT";
    else if (dir == DIR::CCW)
      order = "TBRFLT";

    faceRotate('B', DIR::CW, 2);

    for (int i = 0; i < 5; i++)
      faceCpy(order[i], order[i + 1], 1);

    faceRotate('B', DIR::CW, 2);
  }

  void setTarget2up(char target) {
    char color = idx2color[face2idx[target]];
    char idx = 0;

    for (int i = 0; i < 6; i++) {
      if (board[i][1][1] == color) {
        idx = i;
        break;
      }
    }

    char face = idx2face[idx];

    if (face == 'D') {
      front2up();
      front2up();
    } else if (face == 'F') {
      front2up();
    } else if (face == 'B') {
      front2up();
      front2up();
      front2up();
    } else if (face == 'L') {
      front2right();
      front2up();
    } else if (face == 'R') {
      front2right();
      front2up();
      front2up();
      front2up();
    }
  }

  void printUp() {
    setTarget2up('U');

    while (board[face2idx['F']][1][1] != idx2color[face2idx['F']])
      front2right();

    for (int y = 0; y < 3; y++) {
      for (int x = 0; x < 3; x++)
        cout << board[face2idx['U']][y][x];
      cout << '\n';
    }
  }
};

int main(void) {
  cin.tie(NULL)->sync_with_stdio(false);

  int T;
  cin >> T;

  for (int tc = 1; tc <= T; tc++) {
    int N;
    string cmd;
    Cube cube;

    cin >> N;

    for (int i = 0; i < N; i++) {
      cin >> cmd;

      cube.setTarget2up(cmd[0]);

      if (cmd[1] == '+')
        cube.rotateTop(DIR::CW);
      else
        cube.rotateTop(DIR::CCW);
    }

    cube.printUp();
  }

  return 0;
}
