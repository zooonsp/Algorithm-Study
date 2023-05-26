#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Node {
	int left, right, total, max;    // left: 수열의 왼쪽에서 부터의 최대 연속합, right: 수열의 오른쪽에서의 최대 연속합, total: 수열 전체 최대 연속합, max: 앞 세가지 경우의 최대 연속합
};

int N, M;   // N: 수열의 크기, M: 쿼리의 개수
std::vector<int> element;   // element[i]: 수열의 i 번째 원소
std::vector<std::pair<int, int>> query; // query[i]: 수열의 first ~ second
std::vector<Node> segmentTree;  // segementTree[i]: i 노드의 값 -> 해당하는 범위에서의 가장 큰 연속합

Node printQueryResult(int nodeNum, int start, int end, int left, int right) {   // nodeNum: 노드 번호, start ~ end: 현재 노드의 포함 범위 start ~ end, left ~ right: 가장 큰 연속합을 구할 범위

	if (start > right || end < left) return { static_cast<int>(-1'000'000'000), static_cast<int>(-1'000'000'000) , 0, static_cast<int>(-1'000'000'000) };   // 범위를 벗어나는 경위 영향을 미치지 않는 값 return

	if (start >= left && end <= right) return segmentTree[nodeNum]; // 모든 범위가 포함되는 경우 자식 노드로 내려가 보지 않고 현재 노드 return

	int middle = (start + end) / 2; // middle: 왼쪽 자식 노드와 오른쪽 자식 노드를 나누는 기준
	Node leftChildNode = printQueryResult(nodeNum * 2, start, middle, left, right); // leftChildNode: 왼쪽 자식 노드
	Node rightChildNode = printQueryResult(nodeNum * 2 + 1, middle + 1, end, left, right);  // rightChildNode: 오른쪽 자식 노드

	Node cur;   // cur: 현재 노드
	cur.left = std::max(leftChildNode.left, leftChildNode.total + rightChildNode.left); // 왼쪽: 왼쪽 자식 노드의 왼쪽, 왼쪽 자식 노드 전체와 오른쪽 자식 노드의 왼쪽 중 더 큰 값
	cur.right = std::max(leftChildNode.right + rightChildNode.total, rightChildNode.right); // 오른쪽: 왼쪽 자식 노드의 오른쪽과 오른쪽 노드 전체, 오른쪽 자식 노드의 오른쪽 중 더 큰 값
	cur.total = leftChildNode.total + rightChildNode.total; // 전체: 왼쪽 자식 노드 전체와 오른쪽 자식 노드 전체
	cur.max = std::max(std::max(leftChildNode.max, rightChildNode.max), leftChildNode.right + rightChildNode.left); // 왼쪽 자식 노드의 최대 값, 오른쪽 자식 노드의 최대 값, 왼쪽 자식 노드의 오른쪽과 오른쪽 자식 노드의 왼쪽 중 더 큰 값

	return cur; // 노드 값 return
}

Node makeSegmentTree(int nodeNum, int start, int end) { // nodeNum: 노드 번호, start, end: 현재 노드의 포함 범위 start ~ end
	
	if (start == end) return segmentTree[nodeNum] = { element[start],element[start], element[start], element[start]};   // 리프 노드는 수열의 값 넣음

	int middle = (start + end) / 2; // middle: 왼쪽 자식 노드와 오른쪽 자식 노드를 나누는 기준
	Node leftChildNode = makeSegmentTree(nodeNum * 2, start, middle);   // leftChildNode: 왼쪽 자식 노드
	Node rightChildNode = makeSegmentTree(nodeNum * 2 + 1, middle + 1, end);    // rightChildNode: 오른쪽 자식 노드

	Node cur;   // cur: 현재 노드
	cur.left = std::max(leftChildNode.left, leftChildNode.total + rightChildNode.left); // 왼쪽: 왼쪽 자식 노드의 왼쪽, 왼쪽 자식 노드 전체와 오른쪽 자식 노드의 왼쪽 중 더 큰 값
	cur.right = std::max(leftChildNode.right + rightChildNode.total, rightChildNode.right); // 오른쪽: 왼쪽 자식 노드의 오른쪽과 오른쪽 노드 전체, 오른쪽 자식 노드의 오른쪽 중 더 큰 값
	cur.total = leftChildNode.total + rightChildNode.total; // 전체: 왼쪽 자식 노드 전체와 오른쪽 자식 노드 전체
	cur.max = std::max(std::max(leftChildNode.max, rightChildNode.max), leftChildNode.right + rightChildNode.left); // 왼쪽 자식 노드의 최대 값, 오른쪽 자식 노드의 최대 값, 왼쪽 자식 노드의 오른쪽과 오른쪽 자식 노드의 왼쪽 중 더 큰 값
	
	return segmentTree[nodeNum] = cur;  // 세그먼트 트리 값 넣고 return
}

void sol() {

	int treeDepth = std::ceil(std::log2(N));    // treeDepth: 세그먼트 트리의 높이
	int treeSize = 1 << (treeDepth + 1);    // treeSize: 세그먼트 트리의 크기
	segmentTree.resize(treeSize);   // 세그먼트 트리 공간 할당

	makeSegmentTree(1, 0, N-1);

	for (int i = 0; i < M; i++) {
		std::pair<int, int> cur = query[i]; // cur: 실행할 쿼리 -> first ~ second 범위

		std::cout << printQueryResult(1, 0, N - 1, cur.first, cur.second).max << '\n';
	}

	return;
}

void input() {

	std::cin >> N;

	for (int i = 0; i < N; i++) {
		int n;  // n: i 번째 수열의 값
		std::cin >> n;
		element.push_back(n);
	}

	std::cin >> M;

	for (int i = 0; i < M; i++) {
		int left, right;    // left, right: left ~ right 에서의 가장 큰 연속합을 구할 범위
		std::cin >> left >> right;
		query.push_back({ left - 1, right - 1 });   // 수열은 0 부터 시작하므로 -1 하여 저장
	}

	return;
}


int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();    // 입력

	sol();  // 해결

	return 0;
}