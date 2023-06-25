#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

struct Book{	// 책
	int start, end;	// start, end: 책 번호가 start 이상 end 이하인 책
};

struct Cmp{	// 책 번호의 끝 번호를 기준으로 오름차순 정렬
	bool operator () (Book left, Book right) const{	// 책의 끝 번호를 기준으로 오름 차순 정렬
		if(left.end != right.end) return left.end > right.end;

		return false;
	} 
};

int N, M;	// N: 책의 갯수, M: 서강대학교 학부생의 수
std::priority_queue<Book, std::vector<Book>, Cmp> pq;	// pq: 책 번호의 end를 기준으로 오름 차순 정렬
bool books[1001];	// books[i]: i 번 책의 대여 여부
int ans;	// ans: 책을 줄 수 있는 최대 학생 수

void reset(){	// 초기화

	memset(books, true, sizeof(books));

	ans = 0;

	return;
}

void sol(){

	reset();

	while(!pq.empty()){
		Book curBook = pq.top();	// curBook: 빌려 줄 책의 범위
		pq.pop();

		for(int i=curBook.start; i<=curBook.end; i++){
			if(books[i] == true){	// 책이 있다면
				books[i] = false;	// 빌려 줌
				ans++;
				break;
			}
		}
	}

	return;
}

void input(){

	std::cin >> N >> M;

	for(int i=0; i<M; i++){
		int start, end;	// start, end: 책 번호가 start 이상 end 이하인 책
		std::cin >> start >> end;
		pq.push({start, end});
	}
	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;	// T: 테스트 케이스 개수

	std::cin >> T;

	for(int tc=0; tc<T; tc++){

		input();

		sol();

		std::cout << ans << '\n';

	}

	return 0;
}