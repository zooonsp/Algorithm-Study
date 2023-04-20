#include <iostream>
#include <vector>

long long num;	// numbers의 원소
bool bit[52];	// bit[i]: 51번째 부터 0번째 까지 2진수 저장
int len, totalLen;	// len: 2진수의 길이, totalLen: 이진 트리로 나타내기위한 길이 -> 트리의 노드의 개수만큼 0 필요
bool flag;	// flag: 이진 트리 표현 가능하면 true

void DFS(int leftIdx, int rightIdx, bool value) {

	if (flag == false) return;	// 이진 트리가 구성될 수 없다고 이미 판단하였음

	if (rightIdx - leftIdx + 1 == 3) {	// 왼쪽 자식 노드, 부모 노드, 오른쪽 자식 노드로 구성됨
		int midIdx = (leftIdx + rightIdx) / 2;	// midIdx: 부모 노드
		if (bit[midIdx] == false) {	// 부모 노드가 0의 값을 갖는다면
			if (bit[leftIdx] == true || bit[rightIdx] == true) {	// 자식 노드가 1의 값을 갖는다면 이진트리가 구성될 수 없음
				flag = false;
			}
		}

		return;
	}

	if (value == true) {	// 부모 노드가 1의 값을 갖는다면
		int midIdx = (leftIdx + rightIdx) / 2;	// midIdx: 새로운 부모 노드 지정

		DFS(leftIdx, midIdx - 1, bit[midIdx]);	// 왼쪽 자식 노드
		DFS(midIdx + 1, rightIdx, bit[midIdx]);	// 오른쪽 자식 노드
	}
	else {	// 부모 노드가 0의 값을 갖는다면
		for (int i = leftIdx; i <= rightIdx; i++) {	// 자식 노드는 모두 0의 값을 가져야함
			if (bit[i] == true) {	// 자식 노드 중 1의 값이 있다면 이진 트리를 구성할 수 없음
				flag = false;
				return;
			}
		}
	}

	return;
}

int sol() {
	int leftIdx = 51 - totalLen + 1;	// leftIdx: 가장 왼쪽의 노드
	int rightIdx = 51;	// rightIdx: 가장 오른쪽의 노드

	int midIdx = (leftIdx + rightIdx) / 2;	// midIdx: 중앙 노드 -> 부모 노드가 될 수 있음

	if (rightIdx - leftIdx + 1 == 3) {	// 왼쪽 자식 노드, 부모 노드, 오른쪽 자식 노드로 구성되었을 경우
		if (bit[midIdx] == false) {	// 부모 노드가 0 이라면
			if (bit[rightIdx] == true || bit[leftIdx] == true) {	// 자식 노드가 1 일 수 없음
				return 0;
			}
		}

		return 1;
	}

	if (bit[midIdx] == false) {	// 부모 노드가 0 이라면
		for (int i = leftIdx; i <= rightIdx; i++) {
			if (bit[i] == true) {	// 모든 자식 노드의 값 중 1이 있을 수 없음
				return 0;
			}
		}
	}

	flag = true;

	DFS(leftIdx, midIdx - 1, bit[midIdx]);	// 왼쪽 자식 노드
	DFS(midIdx + 1, rightIdx, bit[midIdx]);	// 오른쪽 자식 노드

	if (flag == false) return 0;	// 이진 트리로 표현 할 수 없음

	return 1;
}

void convertToBit() {

	int idx = 51;	// idx: 가장 작은 값 부터 채우기

	while (num != 0) {		
		if (num % 2 == 1) bit[idx] = true;	// 1이 남으면 1 채워 줌
		num /= 2;	// 2로 나눔
		idx--;
	}

	len = 51 - idx;	// 2진수의 길이
	totalLen = 1;
	int tmpSum = 2;	// tmpSum: 깊이가 하나 추가될 때마다 추가되는 포화 이진 트리의 노드의 개수
	while (totalLen < len) {
		totalLen += tmpSum;
		tmpSum *= 2;
	}

	return;
}

void reset() {
	
	for (int i = 0; i < 52; i++)
		bit[i] = false;	// 비트 false로 초기화

	return;
}

std::vector<int> solution(std::vector<long long> numbers) {
	std::vector<int> answer;

	int vecSize = numbers.size();	// vecSize: numbers의 길이

	for (int v = 0; v < vecSize; v++) {

		num = numbers[v];

		// 이진 트리의 노드의 개수가 4개일때 부터 가능하므로 1, 2, 3은 하드코딩
		if(num == 1) answer.push_back(1);
		else if (num == 2) answer.push_back(1);
		else if (num == 3) answer.push_back(1);
		else {
			reset();
			convertToBit();
			answer.push_back(sol());
		}
	}

	return answer;

}

int main() {

	std::vector<long long> v = { 96, 2, 3, 4, 1000000000000000 };
	std::vector<int> ans;

	ans = solution(v);

	for (int i = 0; i < ans.size(); i++)
		std::cout << ans[i] << ' ';

	return 0;
}