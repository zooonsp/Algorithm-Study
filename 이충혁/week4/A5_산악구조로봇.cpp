#include<iostream>
using namespace std;

int init()
{
	return 0;
}

int input()
{
	return 0;
}

int solve_func()
{
	return 0;
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		solve_func();

		cout << "#" << tc << " " << "\n";
	}
	return 0;
}