#include <iostream>
#include <vector>

int N;	// N: 돌의 정령 무리의 수
std::vector<int> A;	// A[i]: i 번째 돌정령의 시야점수의 제한
std::vector<int> order;	// order[i]: i 번째 돌정령의 순서

void solution(){

	int left = 1, right = N;	// left: 왼쪽 순서, right: 오른쪽 순서

	order.assign(N, 0);
	
	for(int i=0; i<N; ++i){	// 모든 돌 정령 무리에 대하여
		if(A[i] > 0) order[i] = right--;	// 시야점수가 양수라면 오른쪽부터
		else order[i] = left++;	// 시야점수가 음수라면 왼쪽부터
	}

	return;
}

void input(){

	std::cin >> N;

	A.assign(N, 0);

	for(int i=0; i<N; ++i) std::cin >> A[i];

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	input();

	if(A[N-1] < 0) {	// 가장 오른쪽의 정령의 시아 점수는 음수가 될 수 없음
		std::cout << "-1";	// 조건을 만족하는 배치가 없음
		return 0;
	}

	solution();
	
	for(int i=0; i<N; ++i) std::cout << order[i] << ' ';

	return 0;
}