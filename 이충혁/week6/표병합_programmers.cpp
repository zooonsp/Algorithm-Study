#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

const int MAT_MAX = 55;

struct coordi {
	int y, x;

	bool operator == (coordi next) const {
		if (y == next.y && x == next.x)
			return true;

		return false;
	}
};

coordi parent[MAT_MAX][MAT_MAX]; // UF
string graph[MAT_MAX][MAT_MAX]; // UF 가 반영된 표 정보

coordi Find(coordi now)
{
	if (parent[now.y][now.x] == now)
	{
		return now;
	}

	return parent[now.y][now.x] = Find(parent[now.y][now.x]);
}

int Union(coordi r1, coordi r2)
{
	coordi pr1 = Find(r1);
	coordi pr2 = Find(r2);

	if (pr1 == pr2)
		return 0;

	parent[pr2.y][pr2.x] = pr1;
	graph[pr2.y][pr2.x] = "EMPTY";

	return 0;
}

int update_str(string &before, string &after)
{
	coordi p;
	for (int i = 1; i <= 50; i++)
	{
		for (int j = 1; j <= 50; j++)
		{
			p = Find({ i, j });

			if (graph[p.y][p.x] != before) continue;



			graph[p.y][p.x] = after;
		}
	}

	return 0;
}

vector<string> solution(vector<string>& commands) {
	vector<string> answer;
	coordi pt1, pt2; // merge 되는 좌표
	coordi p1, p2;

	// init
	for (int i = 1; i < MAT_MAX; i++)
	{
		for (int j = 1; j < MAT_MAX; j++)
		{
			parent[i][j] = { i, j };
			graph[i][j] = "EMPTY";
		}
	}


	for (int i = 0; i < commands.size(); i++) {
		string command = commands[i];

		vector<string> str; // 공백 별로 문자열 파싱
		stringstream ss(command);
		string token;
		while (ss >> token) str.push_back(token);

		if (str[0] == "UPDATE")
		{
			if (str.size() == 4) // "UPDATE r c value"
			{
				pt1.y = stoi(str[1]);
				pt1.x = stoi(str[2]);

				p1 = Find(pt1);

				graph[p1.y][p1.x] = str[3];
			}
			else // "UPDATE value1 value2"
			{
				update_str(str[1], str[2]);
			}
		}
		else if (str[0] == "MERGE") //"MERGE r1 c1 r2 c2"
		{
			pt1.y = stoi(str[1]);
			pt1.x = stoi(str[2]);
			pt2.y = stoi(str[3]);
			pt2.x = stoi(str[4]);

			p1 = Find(pt1);
			p2 = Find(pt2);

			if (graph[p1.y][p1.x] == "EMPTY") 
			{
				Union(p2, p1);
			}
			else
			{
				Union(p1, p2);
			}
		}
		else if (str[0] == "UNMERGE")//"UNMERGE r c"
		{
			vector <coordi> unmerge;

			pt1.y = stoi(str[1]);
			pt1.x = stoi(str[2]);

			p1 = Find(pt1);
			graph[pt1.y][pt1.x] = graph[p1.y][p1.x];


			for (int y = 1; y <= 50; y++)
			{
				for (int x = 1; x <= 50; x++)
				{
					Find({ y, x });
					if (p1 == parent[y][x])
						unmerge.push_back({ y, x });
				}
			}

			// unmerge 따로 
			for (int i = 0; i < unmerge.size(); i++)
			{
				coordi temp = unmerge[i];
				parent[temp.y][temp.x] = temp;

				if (temp == pt1) continue;

				graph[temp.y][temp.x] = "EMPTY";
			}
		}
		else if (str[0] == "PRINT")//"PRINT r c"
		{
			pt1.y = stoi(str[1]);
			pt1.x = stoi(str[2]);

			p1 = Find(pt1);

			answer.push_back(graph[p1.y][p1.x]);
		}
	}


	return answer;
}
int main()
{
	vector<string> commands = {"UPDATE 1 1 A", "UPDATE 2 2 B", "UPDATE 3 3 C",
		"UPDATE 4 4 D", "MERGE 1 1 2 2", "MERGE 3 3 4 4", "MERGE 1 1 4 4", "UNMERGE 3 3", "PRINT 1 1", "PRINT 2 2", "PRINT 3 3", "PRINT 4 4"
	};

	vector<string> ans = solution(commands);

	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << "\n";
	}

	return 0;
}