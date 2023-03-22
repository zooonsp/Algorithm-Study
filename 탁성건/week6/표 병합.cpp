#include <string>
#include <vector>
using namespace std;

const int SIZE = 50;
// 2차원 표를 1차원으로 변경해서 사용 => 크기는 50*50
vector<string> table;
int parent[SIZE * SIZE];

int Find(int x) {
  if (parent[x] == x)
    return x;
  return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {
  int pa = Find(a);
  int pb = Find(b);
  if (pa == pb)
    return;
  // MERGE할 때 앞의 셀 기준으로 병합
  parent[pb] = pa;

  // 앞의 셀 값이 비어있고 뒤의 셀이 값을 가지고 있으면
  // 병합된 셀은 그 값을 가지게 된다.
  if (table[pa].empty() && !table[pb].empty())
    table[pa] = table[pb];

  // 최상단 부모만 데이터를 가지고 있을 수 있도록 clear
  table[pb].clear();
}

// (y, x) 좌표값을 1차원 index로 변경
int pos2idx(int y, int x) { return y * SIZE + x; }

vector<string> solution(vector<string> commands) {
  vector<string> answer;

  // 2차원 표를 1차원으로 변경해서 사용 => 크기는 50*50
  table = vector<string>(SIZE * SIZE);

  // parent 초기화
  for (int i = 0; i < SIZE * SIZE; i++)
    parent[i] = i;

  // 모든 명령어 실행
  for (string str : commands) {
    vector<string> cmd; // parsing한 명령어를 담을 vector

    // 명령어 parsing
    while (true) {
      int idx = str.find(' '); // 공백의 index 찾기
      if (idx == string::npos) // 공백이 없으면 break
        break;
      // 시작부터 공백 전까지 잘라서 cmd에 push
      cmd.push_back(str.substr(0, idx));
      str = str.substr(idx + 1); // 남은 명령어는 공백 이후부터 끝까지
    }

    cmd.push_back(str); // 마지막 남은 명령어 push

    string oper = cmd[0];

    // UPDATE
    if (oper == "UPDATE") {
      // 명령어 개수가 4개라면 (r, c)위치의 셀 선택
      if (cmd.size() == 4) {
        int r = stoi(cmd[1]) - 1, c = stoi(cmd[2]) - 1;
        string value = cmd[3];

        // 선택한 셀의 값을 value로 변경
        // 좌표를 index로 변경
        // 모든 데이터는 최상단 부모가 가지고 있으므로 Find 사용
        table[Find(pos2idx(r, c))] = value;
      }
      // 아니라면 value1을 값으로 가지고 있는 모든 셀 선택
      else {
        string value1 = cmd[1], value2 = cmd[2];

        // table의 모든 index 확인
        for (int i = 0; i < SIZE * SIZE; i++) {
          int p = Find(i);
          // 최상단 부모가 가지고 있는 값이 value1이라면 value2로 변경
          if (table[p] == value1)
            table[p] = value2;
        }
      }
    }
    // MERGE
    else if (oper == "MERGE") {
      int r1 = stoi(cmd[1]) - 1, c1 = stoi(cmd[2]) - 1, r2 = stoi(cmd[3]) - 1,
          c2 = stoi(cmd[4]) - 1;

      // (r1, c1)위치의 셀과 (r2, c2)위치의 셀 병합
      Union(pos2idx(r1, c1), pos2idx(r2, c2));
    }
    // UNMERGE
    else if (oper == "UNMERGE") {
      int r = stoi(cmd[1]) - 1, c = stoi(cmd[2]) - 1;
      int p = Find(pos2idx(r, c)); // 최상단 부모

      string value = table[p]; // 병합 해제 전 셀의 값 저장
      table[p].clear();        // 셀의 값 clear

      vector<int> target; // 병합 해제할 셀의 index

      // 선택한 셀과 같은 그룹이면 target에 push
      for (int i = 0; i < SIZE * SIZE; i++)
        if (Find(i) == p)
          target.push_back(i);

      // parent를 자기 자신으로 초기화
      for (int i : target)
        parent[i] = i;

      // 병합 해제 전 셀이 값을 가지고 있었을 경우
      // (r, c)위치의 셀이 그 값을 가지게 된다.
      table[pos2idx(r, c)] = value;
    }
    // PRINT
    else if (oper == "PRINT") {
      int r = stoi(cmd[1]) - 1, c = stoi(cmd[2]) - 1;

      // 선택한 셀의 최상단 부모가 가지고 있는 값
      string result = table[Find(pos2idx(r, c))];

      if (result.empty())
        answer.push_back("EMPTY");
      else
        answer.push_back(result);
    }
  }

  return answer;
}
