#include <iostream>
#include <vector>
#include <queue>

int N, M;	// N: 문제의 수, M: 먼저 푸는 것이 좋은 문제에 대한 정보의 개수
std::vector<int> inDegree;	// inDegree[i]: i 문제보다 먼저 푸는 것이 좋은 문제의 개수
std::vector<std::vector<int>> order;	// order[i][j]: i 보다 먼저 풀어야하는 j 번째 문제 번호
std::vector<int> ans;	// ans[i]: 민오가 풀 i 번째 문제

struct Cmp{	// 문제 번호 오름차순 정렬 우선 순위 큐
	bool operator () (int left, int right) const {
		if(left != right) return left > right;

		return false;
	}
};

void solution(){

	std::priority_queue<int, std::vector<int>, Cmp> q;	// q[i]: i 번째로 풀 문제 번호 -> 문제 번호가 작은 것이 먼저 나오게 됨

	for(int i=1; i<=N; i++){
		if(!inDegree[i]) q.push(i);	// 먼저 풀어야 할 문제가 없으면 우선 순위 큐에 넣음
	}

	while(!q.empty()){
		int cur = q.top();	// cur: 풀어야 하는 문제의 번호
		q.pop();

		ans.push_back(cur);	// 문제 리스트에 넣음

		for(int i=0; i<order[cur].size(); i++){
			int next = order[cur][i];	// next: cur문제 다음에 풀 수 있는 문제의 번호
			inDegree[next]--;	// 앞써 풀어야하는 cur 문제를 풀었으므로 -1
			if(!inDegree[next]) q.push(next);	// 먼저 풀어야할 문제가 없으면 우선 순위 큐에 넣음
		}
	}

	return;
}

void input(){

	std::cin >> N >> M;

	// 공간 할당
	inDegree.assign(N+1, 0);
	order.assign(N+1, std::vector<int>(0,0));

	for(int i=0; i<M; i++){
		int A, B;	// A, B: 문제 번호, B 문제보다 A 문제를 먼저 푸는 것이 좋음
		std::cin >> A >> B;

		order[A].push_back(B);	// A 문제 다음에 B 문제를 풀어야함
		inDegree[B]++;	// B 문제를 풀기 위한 문제가 +1
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	for(int i=0; i<N; i++) std::cout << ans[i] << ' ';

	return 0;
}