#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX = 21e8;
const int MAX_DP = 200;

struct Info {
	int alp, cop;
};

enum PB_CONST {
	alp_req, cop_req, alp_rwd, cop_rwd, cost
};

Info max_limit; // 최소, 최대 알고력 코딩력

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int DP[MAX_DP][MAX_DP] = { 0, }; // alp, cop

int solution(int alp, int cop, vector<vector<int>> &problems) {

	// 알고력, 코딩력의 최대 최소를 구함
	for (int i = 0; i < problems.size(); i++)
	{
		if (max_limit.alp < problems[i][alp_req])
			max_limit.alp = problems[i][alp_req];

		if (max_limit.cop < problems[i][cop_req])
			max_limit.cop = problems[i][cop_req];
	}

	// init 
	for (int i = 0; i < MAX_DP; i++) // alp
	{
		for (int j = 0; j < MAX_DP; j++) // cop
		{
			DP[i][j] = MAX;
		}
	}

	if (alp > max_limit.alp)
		alp = max_limit.alp;

	if (cop > max_limit.cop)
		cop = max_limit.cop;

	DP[alp][cop] = 0;

	for (int i = alp; i <= max_limit.alp; i++) // alp
	{
		for (int j = cop; j <= max_limit.cop; j++) // cop
		{
			DP[i + 1][j] = min(DP[i + 1][j], DP[i][j] + 1); // 1씩 alp, cop 증가시키는 부분 DP 채우기
			DP[i][j + 1] = min(DP[i][j + 1], DP[i][j] + 1);

			for (int k = 0; k < problems.size(); k++)
			{

				if (i < problems[k][alp_req] || j < problems[k][cop_req]) // 지금 알고력 코딩력이 목표치에 다다르지 않으면
					continue;

				int alp_index = i + problems[k][alp_rwd];
				int cop_index = j + problems[k][cop_rwd];

				if (alp_index > max_limit.alp) // alp, cop가 최대치를 넘어서면 최대치로 바꾸기
				{
					alp_index = max_limit.alp;
				}
				if (cop_index > max_limit.cop)
				{
					cop_index = max_limit.cop;
				}

				DP[alp_index][cop_index] = min(DP[alp_index][cop_index], DP[i][j] + problems[k][cost]); 

			}
		}
	}

	if (DP[max_limit.alp][max_limit.cop] == MAX)
		DP[max_limit.alp][max_limit.cop] = 0;
	return DP[max_limit.alp][max_limit.cop];
}





// 여기서부터는 입출력용

int input(int& alp, int& cop, vector<vector<int>>& temp_pb)
{
	cin >> alp;
	cin >> cop;

	int size;
	cin >> size;

	int temp[5];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 5; j++)
			cin >> temp[j];

		temp_pb.push_back({ temp[0], temp[1], temp[2], temp[3], temp[4] });
	}

	return 0;
}

int main()
{
	freopen("input.txt", "r", stdin);


	int alp, cop;
	vector<vector<int>> temp_pb;
	input(alp, cop, temp_pb);
	cout << solution(alp, cop, temp_pb);

	return 0;
}
