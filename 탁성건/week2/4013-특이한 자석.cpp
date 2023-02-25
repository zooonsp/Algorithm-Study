#include <iostream>
#include <deque>
#include <vector>
#include <cmath>
using namespace std;

int K;
deque<int> gear[4];

enum {
	T = 0, L = 6, R = 2
};

bool isValid(int left, int right) {
	return gear[left][R] != gear[right][L];
}

void rotateGear(int id, int dir) {
	if (dir == 1) {
		gear[id].push_front(gear[id].back());
		gear[id].pop_back();
	}
	else if (dir == -1) {
		gear[id].push_back(gear[id].front());
		gear[id].pop_front();
	}
}

void chainRotate(int id, int dir) {
	vector<pair<int, int>> opers;
	opers.push_back({ id, dir });

	if (id == 0) {
		if (isValid(0, 1)) {
			opers.push_back({ 1, -dir });
			if (isValid(1, 2)) {
				opers.push_back({ 2, dir });
				if (isValid(2, 3)) {
					opers.push_back({ 3, -dir });
				}
			}
		}
	}
	else if (id == 1) {
		if (isValid(0, 1))
			opers.push_back({ 0, -dir });
		if (isValid(1, 2)) {
			opers.push_back({ 2, -dir });
			if (isValid(2, 3)) {
				opers.push_back({ 3, dir });
			}
		}
	}
	else if (id == 2) {
		if (isValid(1, 2)) {
			opers.push_back({ 1, -dir });
			if (isValid(0, 1)) {
				opers.push_back({ 0, dir });
			}
		}
		if (isValid(2, 3))
			opers.push_back({ 3, -dir });
	}
	else if (id == 3) {
		if (isValid(2, 3)) {
			opers.push_back({ 2, -dir });
			if (isValid(1, 2)) {
				opers.push_back({ 1, dir });
				if (isValid(0, 1)) {
					opers.push_back({ 0, -dir });
				}
			}
		}
	}

	for (auto oper : opers)
		rotateGear(oper.first, oper.second);
}

int main(void) {
	int TC;
	cin >> TC;

	for (int tc = 1; tc <= TC; tc++) {
		cout << '#' << tc << ' ';

		for (int i = 0; i < 4; i++)
			gear[i] = deque<int>(8);

		cin >> K;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 8; j++)
				cin >> gear[i][j];

		for (int i = 0; i < K; i++) {
			int id, dir;
			cin >> id >> dir;
			chainRotate(id - 1, dir);
		}

		int score = 0;

		for (int i = 0; i < 4; i++)
			score += gear[i][T] * pow(2, i);

		cout << score << '\n';
	}

	return 0;
}
