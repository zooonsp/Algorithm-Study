#include<iostream>
#include<algorithm>
using namespace std;

/*
출처 : https://blog.naver.com/july1981/110017366573

벡터의 외적의 크기는 벡터의 정의에서 보면 두 벡터를 이웃으로하는 평행사변형의 넓이이다.
이를 이용해 다각형 면적을 구할 수 있다.

증명 참고 : https://darkpgmr.tistory.com/86
*/

using ll = long long;

struct coordi
{
	ll y, x;
};

const int PT_MAX = 10101;

coordi pt[PT_MAX]; // 다각형의 점들

ll cross(coordi a, coordi b)
{
	return a.x * b.y - b.x * a.y;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	int n;

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> pt[i].x >> pt[i].y;
	}

	double ans = 0;
	
	for (int i = 2; i < n; i++)
	{
		// 다각형 면적 구할 때 고정점(0)를 옮기면 안되는데 계속 옮겨서 ;; 많이 틀렸다.
		ans += cross({ pt[i - 1].y - pt[0].y, pt[i - 1].x - pt[0].x }, { pt[i].y - pt[0].y, pt[i].x - pt[0].x }) / (double)2;
	}

	cout << fixed;
	cout.precision(1);
	cout << abs(ans);

	return 0;
}