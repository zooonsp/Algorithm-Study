#include <iostream>
#include <vector>
#include <queue>

int n;	// n: 팀 수
std::vector<int> lastYearOrder;	// lastYearOrder[i]: 작년 i 등 팀 번호
int m;	// m: 상대적인 등수가 바뀐 쌍의 수
std::vector<std::pair<int, int>> change;	// change[i]: 상대적인 등수가 바뀐 i 번째 팀, first 팀과 second 팀의 상대 등수 바뀜
std::vector<std::vector<bool>> adj;	// adj[i][j]: i 팀이 j 팀 보다 앞썬 등수면 true, 반대면 false
std::vector<int> inDegree;	// inDegree[i]: i 팀 보다 앞에 있는 팀의 수
std::vector<int> ans;	// ans[i]: 올해 팀 순위
int ansFlag;	// ansFlag: 순위의 상태 -> 0: 정상 순위 가능, 1: 확실한 순위를 찾을 수 없음, 2: 데이터에 일관성이 없어서 순위를 정할 수 없음

void solution(){

	adj.assign(n+1, std::vector<bool>(n+1, false));	// 인접 행렬 공간 할당 -> 초기 값 false
	inDegree.assign(n+1, 0);	// 위상 정렬할 공간 할당

	for(int j=0; j<n; j++){
		for(int i=j+1; i<n; i++){
			int now = lastYearOrder[j];	// now: 현재 팀
			int next = lastYearOrder[i];	// next: 현재 팀 보다 뒤에 있는 팀

			adj[now][next] = true;	// 참 값으로 변경
			inDegree[next]++;	// next 팀은 앞에 now 팀이 있으므로 값 +1
		}
	}

	for(int i=0; i<m; i++){
		// A, B: 상대 순위가 바뀔 두 팀 번호
		int A = change[i].first;
		int B = change[i].second;

		if(adj[A][B]){	// A 팀이 B 팀 보다 앞썬 순위일 경우
			adj[A][B] = false;
			inDegree[B]--;
			adj[B][A] = true;
			inDegree[A]++;
		}
		else{	// B 팀이 A 팀 보다 앞썬 순위일 경우
			adj[B][A] = false;
			inDegree[A]--;			
			adj[A][B] = true;
			inDegree[B]++;
		}
	}

	while(ans.size()) ans.pop_back();	// 올해 순위 벡터 비우기
	ansFlag = 0;

	std::queue<int> q;	// q: 순위 후보

	for(int i=1; i<n+1; i++){
		if(!inDegree[i]) q.push(i);	// 앞썬 팀이 없는 팀 후보에 넣음
	}

	while(!q.empty()){
		if(q.size() > 1){	// 후보에 1개 이상에 팀이 있는 경우
			ansFlag = 1;	// 확실한 순위를 찾을 수 없음
			return;
		}

		int cur = q.front();	// cur: 이번 순위의 팀
		q.pop();

		ans.push_back(cur);

		for(int i=1; i<n+1; i++){
			if(!adj[cur][i]) continue;	// 이번 순위 팀의 바로 뒤에 있는 팀이 아닌 경우 continue

			int next = i;	// next: 다음 팀이 될 후보

			inDegree[next]--;
			if(!inDegree[next]) q.push(next);	// 앞썬 팀이 없다면 큐에 넣음
		}
	}

	if(ans.size() != n) ansFlag = 2;	// 순위를 정할 수 없는 경우

	return;
}

void input(){

	std::cin >> n;

	lastYearOrder.assign(n, 0);	// 작년 순위 공간 할당

	for(int i=0; i<n; i++) std::cin >> lastYearOrder[i];

	std::cin >> m;

	change.assign(m, std::pair<int, int>(0, 0));	// 바뀐 상대 등수 쌍 공간 할당

	for(int i=0; i<m; i++){
		std::cin >> change[i].first >> change[i].second;
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;	// T: 테스트 케이스의 개수
	std::cin >> T;

	for(int tc=0; tc<T; tc++){

		input();

		solution();

		if(ansFlag == 0){
			for(int i=0; i<n; i++) std::cout << ans[i] << ' ';
		}
		else if(ansFlag == 1) std::cout << "?";
		else if(ansFlag == 2) std::cout << "IMPOSSIBLE";
		
		std::cout << '\n';
	}

	return 0;
}