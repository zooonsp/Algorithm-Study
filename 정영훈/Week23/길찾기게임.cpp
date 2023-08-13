// 전위 순회 : Root - Left - Right
// 후위 순회 : Left - Right - Root
/*
트리 노드 구성 규칙
- 트리를 구성하는 모든 노드의 x, y 좌표 값은 정수이다.
- 모든 노드는 서로 다른 x값을 가진다.
- 같은 레벨(level)에 있는 노드는 같은 y 좌표를 가진다.
- 자식 노드의 y 값은 항상 부모 노드보다 작다.
- 임의의 노드 V의 왼쪽 서브 트리(left subtree)에 있는 모든 노드의 x값은 V의 x값보다 작다.
- 임의의 노드 V의 오른쪽 서브 트리(right subtree)에 있는 모든 노드의 x값은 V의 x값보다 크다.
*/
#include<bits/stdc++.h>

using namespace std;
constexpr int BORDER = 100'010;

struct Vertex{
	int x, y, index;
	Vertex(int x, int y, int index) : x(x), y(y), index(index) {}
};
int verticesSize;

void MakePreorder(vector<vector<int>>& answer, vector<int>& visited, vector<Vertex>& vertices, int index, int border = BORDER) {
	answer[0].push_back(vertices[index].index);
	visited[index] = 1;
	for (int i = index + 1; i < verticesSize; ++i) {
		if (vertices[index].y == vertices[i].y) continue;
		// 이후엔 무조건 현재(index)보다 y좌표가 작다.
		if (visited[i] == 0 && vertices[index].x > vertices[i].x && vertices[i].x < border) MakePreorder(answer, visited, vertices, i, vertices[index].x); // left
		if (visited[i] == 0 && vertices[index].x < vertices[i].x && vertices[i].x < border) MakePreorder(answer, visited, vertices, i, border); // right
	}
}

void MakePostorder(vector<vector<int>>& answer, vector<int>& visited, vector<Vertex>& vertices, int index, int border = BORDER) {
	for (int i = index + 1; i < verticesSize; ++i) {
		if (vertices[index].y == vertices[i].y) continue;
		// 이후엔 무조건 현재(index)보다 y좌표가 작다.
		if (visited[i] == 0 && vertices[index].x > vertices[i].x && vertices[i].x < border) MakePostorder(answer, visited, vertices, i, vertices[index].x); // left
		if (visited[i] == 0 && vertices[index].x < vertices[i].x && vertices[i].x < border) MakePostorder(answer, visited, vertices, i, border); // right
	}
	answer[1].push_back(vertices[index].index);
	visited[index] = 1;
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector<vector<int>> answer(2); // 전위 순회, 후위 순회
	vector<Vertex> vertices;

	int index = 1;
	for (vector<int>& coord : nodeinfo) {
		vertices.emplace_back(coord[0], coord[1], index++);
	}
	verticesSize = static_cast<int>(vertices.size());

	sort(begin(vertices), end(vertices), [](const Vertex& v1, const Vertex& v2){
		if (v1.y == v2.y) return v1.x < v2.x;
		return v1.y > v2.y;
	}); // y좌표 큰 애들 기준으로 정렬 (y가 같으면 x가 작은 순서대로)
	
	vector<int> visited(verticesSize + 1, 0);
	MakePreorder(answer, visited, vertices, 0);
	visited.assign(verticesSize + 1, 0);
	MakePostorder(answer, visited, vertices, 0);

	return answer;
}

template<typename T>
void Print(vector<vector<T>>& vec) {
	for (auto& row : vec) {
		for (auto& v : row) {
			cout << v << ' ';
		}
		cout << '\n';
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	
	auto result = solution({{5, 3}, {11, 5}, {13, 3}, {3, 5}, {6, 1}, {1, 3}, {8, 6}, {7, 2}, {2, 2}});
	Print(result);
}