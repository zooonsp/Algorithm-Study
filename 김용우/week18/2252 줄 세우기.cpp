#include <iostream>
#include <vector>
#include <queue>

int N, M;	// N: 학생의 수, M: 키를 비교한 횟수
std::vector<std::vector<int>> order;	// order[i][j]: i 번 학생 뒤에 서야하는 j 번째 학생 번호
std::vector<int> inDegree;	// inDegree[i]: i 학생 보다 앞에 서야하는 학생의 수 -> inDegree는 노드의 진입 차수
std::vector<int> ans;	// ans[i]: i 번째로 선 학생 번호

void solution(){

	std::queue<int> q;	// q[i]: 줄을 설 수 있는 학생의 번호

	for(int i=1; i<=N; i++){	// 앞에 줄을 서야 하는 학생이 없는 경우 큐에 넣음
		if(!inDegree[i]) q.push(i);
	}

	while(!q.empty()){
		int cur = q.front();	// cur: 이번에 줄을 설 학생 번호
		q.pop();

		ans.push_back(cur);	// 줄 섬

		for(int i=0; i<order[cur].size(); i++){
			int next = order[cur][i];	// next: cur 학생 다음에 줄을 설 학생 번호 -> order 그래프를 통해 구할 수 있음

			inDegree[next]--;	// 이번 학생이 줄을 섰기 때문에 다음 학생 앞에 학생 수 -1 -> 진입차수 감소
			if(!inDegree[next]) q.push(next);	// 다음 학생 앞에 줄 설 학생이 없다면 줄을 서는 큐에 넣음
		}
	}

	return;
}

void input(){

	std::cin >> N >> M;

	// 공간 할당
	order.assign(N+1, std::vector<int>(0,0));
	inDegree.assign(N+1, 0);

	for(int i=0; i<M; i++){
		int A, B;	// A, B: A 학생 뒤에 B 학생이 서야 함
		std::cin >> A >> B;
		order[A].push_back(B);	// A 학생 뒤에 B 학생이 연결되어 있는 그래프
		inDegree[B]++;	// B 학생 앞에 서야 하는 학생 수 증가
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