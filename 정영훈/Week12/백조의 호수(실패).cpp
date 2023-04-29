#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <set>

#define FASTIO cin.tie(NULL)->sync_with_stdio(false)

using namespace std;

struct UnionFind {
	vector<int> par;
	UnionFind(int n) : par(n, -1) {}

	int Find(int a) {
		if (par[a] < 0) return a;
		return par[a] = Find(par[a]);
	}

	bool Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (!(a^b)) return false; // a == b
		if (Size(a) < Size(b)) swap(a, b);
		par[a] += par[b];
		par[b] = a;
		return true;
	}

	int Size(int a) {
		a = Find(a);
		return -par[a];
	}

	bool IsSame(int a, int b) {
		a = Find(a), b = Find(b);
		return a == b;
	}
};

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
	coord() = default;
};

coord swan1(-1,-1), swan2(-1,-1);
int swan1Index, swan2Index;

int R, C;
vector<string> Map;
vector<queue<coord>> unionBorderCoordLists; // border
vector<vector<int>> visited;
bool alreadyUnioned{ false };

inline int CoordToIndex(coord&& c) {
	return C * c.x + c.y;
}

void MakeUnion(UnionFind& uf, coord&& start) {
	queue<coord> Q;
	Q.push(start);
	int groupIndex = uf.Find(CoordToIndex(move(start)));
	visited[start.x][start.y] = groupIndex;
	unionBorderCoordLists[groupIndex].push(start);
	while (!Q.empty()) {
		coord now = Q.front(); Q.pop();
		int nowIndex = uf.Find(CoordToIndex(move(now)));
		for (int d{}; d < 4; ++d) {
			int nx = now.x + "0211"[d] - '1';
			int ny = now.y + "1102"[d] - '1';
			if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
			if (Map[nx][ny] == 'X') continue;
			if (visited[nx][ny] != -1) continue;
			visited[nx][ny] = groupIndex;
			coord newC(nx, ny);
			int newIndex = CoordToIndex(move(newC));
			if (uf.IsSame(newIndex, nowIndex)) continue; // 같은 구역
			uf.Union(nowIndex, newIndex);
			Q.push(newC);
			unionBorderCoordLists[groupIndex].push(newC);
		}
	}
}

void Expand(UnionFind& uf, int idx, vector<string>& tmpMap) {
	int idxPar = uf.Find(idx);
	int siz = (int)unionBorderCoordLists[idx].size();
	while (siz--) {
		coord now = unionBorderCoordLists[idx].front(); unionBorderCoordLists[idx].pop();
		int nowIndex = uf.Find(CoordToIndex(move(now)));
		for (int d{}; d < 4; ++d) {
			int nx = now.x + "0211"[d] - '1';
			int ny = now.y + "1102"[d] - '1';
			if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
			coord newC(nx, ny);
			int newIndex = CoordToIndex(move(newC));
			
			if (uf.IsSame(newIndex, nowIndex)) continue; // 같은 구역

			if (Map[nx][ny] == 'X') {
				if(uf.Union(nowIndex, newIndex)) unionBorderCoordLists[idxPar].push(newC);
				tmpMap[nx][ny] = '.';
			}
			else {
				uf.Union(nowIndex, newIndex);
				if (uf.IsSame(swan1Index, swan2Index)) {
					alreadyUnioned = true;
					return;
				}
			}
		}
	}
}

int main() {
	FASTIO;
	freopen("labudovi.i04", "r", stdin);
	cin >> R >> C;
	UnionFind uf(R * C);
	Map = vector<string>(R);
	visited.assign(R, vector<int>(C, -1));
	unionBorderCoordLists.assign(R*C, queue<coord>());
	vector<int> groupLists; // Union의 top 저장
	for (int r{}; r < R;++r) {
		cin >> Map[r];
	}

	for (int r{}; r < R; ++r) {
		for (int c{}; c < C; ++c) {
			if (Map[r][c] == 'X') continue;
			if (Map[r][c] == 'L') {
				if (swan1.x == -1 && swan1.y == -1) swan1 = { r,c };
				else swan2 = { r,c };
			}
			if (visited[r][c] != -1) continue;
			MakeUnion(uf, move(coord(r, c)));
			groupLists.push_back(CoordToIndex(coord(r, c)));
		}
	}

	swan1Index = CoordToIndex(move(swan1)), swan2Index = CoordToIndex(move(swan2));
	if (uf.IsSame(swan1Index, swan2Index)) alreadyUnioned = true;

	for (int time{ 1 };; ++time) {
		if (time) {
			set<int> tmpGroupLists;
			vector<string> tmpMap(begin(Map), end(Map));
			for (int& groupIdx : groupLists) {
				Expand(uf, groupIdx, tmpMap);
				if (alreadyUnioned) break;
				if(!unionBorderCoordLists[groupIdx].empty())
					tmpGroupLists.insert(groupIdx); // 중복 방지 필요
			}
			groupLists.assign(begin(tmpGroupLists), end(tmpGroupLists));
			Map.swap(tmpMap);
		}

		if(alreadyUnioned) {
			cout << time - 1 << '\n';
			break;
		}

		if (uf.IsSame(swan1Index, swan2Index)) {
			cout << time << '\n';
			break;
		}
	}
		
	return 0;
}

