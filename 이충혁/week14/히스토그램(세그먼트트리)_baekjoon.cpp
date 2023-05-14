// https://xkdlaldfjtnl.tistory.com/12

#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int NUM_MAX = 101010;
const int DEPTH_MAX = 18; // log_2 100000 : 약 17 ( 16.6 이지만 "1 << 깊이 + 1" 해줘야함 !)

int N;
ll num[NUM_MAX];
ll tree[1 << DEPTH_MAX];

// 작은 값들이 루트로 되도록 세그먼트 트리를 만든다.
void init(int node, int start, int end) {
	if (start == end) {
		tree[node] = start;
		return;
	}
	else {
		int mid = (start + end) / 2;
		init(node * 2, start, mid);
		init(node * 2 + 1, mid + 1, end);

		if (num[tree[node * 2]] <= num[tree[node * 2 + 1]])
			tree[node] = tree[node * 2];

		else
			tree[node] = tree[node * 2 + 1];
	}
}

// 해당 left, right 사이에서 가장 작은 곳의 index를 return
int query(int node, int start, int end, int left, int right)
{

	if (left > end || right < start)
		return -1; 

	if (end <= right && start >= left)
		return tree[node];

	int mid = (start + end) / 2;
	int m1 = query(node * 2, start, mid, left, right); // m 기준 제일 작은 왼쪽 index
	int m2 = query(node * 2 + 1, mid + 1, end, left, right); // m 기준 제일 작은 오른쪽 index

	// m1 m2 중 작은 값을 반환 한다.
	if (m1 == -1)  
		return m2;

	else if (m2 == -1)
		return m1;

	else {
		if (num[m1] <= num[m2])
			return m1;

		else
			return m2;

	}
}

ll getMAX(int left, int right) {
	int m = query(1, 0, N - 1, left, right);

	// 가장 작은값 * 폭 = 너비
	ll area = (ll)(right - left + 1) * (ll)num[m];

	// 반환 받은 m index 기준으로 왼쪽 오른쪽을 따로 구한다
	// 가장 작은 값인 m 에서 잘리기 때문에!

	if (m + 1 <= right) {
		ll tmp = getMAX(m + 1, right);

		if (area < tmp) area = tmp;
	}
	if (m - 1 >= left) {
		ll tmp = getMAX(left, m - 1);

		if (area < tmp) area = tmp;
	}
	return area;
}

int input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> num[i];
    return 0;
}

int solve_func()
{
    // 세그 트리 만들기
    init(1, 0, N - 1);

    cout << getMAX(0, N - 1);
    return 0;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);

    input();
    solve_func();

    return 0;
}