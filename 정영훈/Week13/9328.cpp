#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <bitset>

using namespace std;
constexpr int DOC = 53;
bitset<27> haveKeys;

struct coord
{
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
};
queue<coord> disableQueues[27]{};

int dx[]{-1, 1, 0, 0};
int dy[]{0, 0, -1, 1};
int H, W;

void Input(vector<vector<int>> &Map)
{
	for (int h{}; h < H; ++h)
	{
		for (int w{}; w < W; ++w)
		{
			int &c = Map[h][w];
			char ch{};
			cin >> ch;
			if ('a' <= (ch | ' ') && (ch | ' ') <= 'z')
			{ // ' ' = 0x20
				if (ch & ' ')
				{					   // lower = key
					c = ch - 'a' + 27; // 27 ~ 52
				}
				else
				{					  // upper = door
					c = ch - 'A' + 1; // 1 ~ 26
				}
			}
			else if (ch == '*')
				c = -1;
			else if (ch == '$')
				c = DOC;
			else // .
				c = 0;
		}
	}

	string initialKeys;
	cin >> initialKeys;
	for (char &ch : initialKeys)
	{
		if ('a' <= (ch | ' ') && (ch | ' ') <= 'z') // lower letter
		{
			haveKeys[ch - 'a' + 1] = 1;
		}
	}
}

inline bool EnableToGo(int value)
{
	// 열쇠가 있는 문이거나 DOC($)거나 .이거나
	return (value == DOC || !value || ((1 <= value && value <= 26) && haveKeys[value]));
}

inline bool IsKey(int value)
{
	return (27 <= value && value <= 52);
}

void CheckPossible(vector<vector<int>> &Map, vector<vector<int>> &visited, queue<coord> &enableQ, int h, int w)
{
	int value = Map[h][w];
	if (value != -1 && !visited[h][w])
	{
		visited[h][w] = 1;
		if (IsKey(value))
		{
			int idx = value - 26;
			haveKeys[idx] = 1;
			while (!disableQueues[idx].empty())
			{
				coord nowCanGo = disableQueues[idx].front();
				disableQueues[idx].pop();
				enableQ.push(nowCanGo);
			}
			enableQ.push(coord(h, w));
		}
		else if (EnableToGo(value))
		{ // EnableTogo를 그냥 적어놨네..
			enableQ.push(coord(h, w));
		}
		else
		{
			disableQueues[value].push(coord(h, w));
		}
	}
}

void setInitialQueue(vector<vector<int>> &Map, vector<vector<int>> &visited, queue<coord> &enableQ)
{
	for (int h{}; h < H; ++h)
	{
		CheckPossible(Map, visited, enableQ, h, 0);
		CheckPossible(Map, visited, enableQ, h, W - 1);
	}
	for (int w{}; w < W; ++w)
	{
		CheckPossible(Map, visited, enableQ, 0, w);
		CheckPossible(Map, visited, enableQ, H - 1, w);
	}
}

void Init()
{
	haveKeys.reset(); // set all bit 0
	for (int idx{1}; idx < 27; ++idx)
	{
		while (!disableQueues[idx].empty())
		{
			disableQueues[idx].pop();
		}
	}
}

int main()
{
	cin.tie(nullptr)->sync_with_stdio(false);
	int T{};
	cin >> T;
	for (int t{}; t < T; ++t)
	{
		Init();
		cin >> H >> W;
		vector<vector<int>> Map(H, vector<int>(W, 0)), visited(H, vector<int>(W, 0));

		Input(Map);

		queue<coord> enableQ;
		setInitialQueue(Map, visited, enableQ);

		int answer{};
		while (!enableQ.empty())
		{
			coord now = enableQ.front();
			enableQ.pop();

			if (Map[now.x][now.y] == DOC)
				++answer;

			for (int dir{}; dir < 4; ++dir)
			{
				int nx = now.x + dx[dir];
				int ny = now.y + dy[dir];
				if (nx < 0 || nx >= H || ny < 0 || ny >= W)
					continue;
				if (Map[nx][ny] == -1)
					continue;
				if (visited[nx][ny])
					continue;
				visited[nx][ny] = 1;
				if (27 <= Map[nx][ny] && Map[nx][ny] <= 52)
				{								// key
					int idx = Map[nx][ny] - 26; // 1 ~ 26
					haveKeys[idx] = 1;
					while (!disableQueues[idx].empty())
					{
						coord nowCanGo = disableQueues[idx].front();
						disableQueues[idx].pop();
						enableQ.push(nowCanGo);
					}
					// key도 넣어야 되는데..
					enableQ.push(coord(nx, ny));
				}
				else if (1 <= Map[nx][ny] && Map[nx][ny] <= 26)
				{ // door
					if (haveKeys[Map[nx][ny]])
					{
						enableQ.push(coord(nx, ny));
					}
					else
					{
						disableQueues[Map[nx][ny]].push(coord(nx, ny));
					}
				}
				else // 0 or DOC
				{
					enableQ.push(coord(nx, ny));
				}
			}
		}
		cout << answer << '\n';
	}

	return 0;
}