#include<iostream>
using namespace std;

/*
추가 설명 : https://yabitemporary.tistory.com/entry/BOJ-11758-CCW-Python3

CW, CCW는 벡터의 외적으로 판별이 가능하며
외적이 음수인지 양수인지에 따라 판별한다.
*/

struct coordi
{
	int y, x;
};

int cross(coordi a, coordi b)
{
	return a.x * b.y - b.x * a.y;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);

	coordi pt[3];

	for (int i = 0; i < 3; i++)
	{
		cin >> pt[i].x >> pt[i].y;
	}

	int ret = cross({ pt[1].y - pt[0].y, pt[1].x - pt[0].x }, { pt[2].y - pt[1].y, pt[2].x - pt[1].x });

	if (ret == 0)
		cout << 0;
	else if (ret > 0)
		cout << 1;
	else
		cout << -1;

	return 0;
}