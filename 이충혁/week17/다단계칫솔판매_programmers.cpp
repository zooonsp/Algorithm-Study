#include<iostream>

/*
자신의 이익 : (칫솔 판매값 + 소개시킨 사람의 영업이익 10%)에 소캐시켜준 사람이 있으면
90% 만가져간다.

enroll에 써있는대로 각자 이익을 구하자

1. 자신을 소개해준 사람을 map으로 묶자
2. 자신의 이익을 구하고 소개해준 사람이 있다면 - 10% 그리고 소개시켜준 사람의 영업 이익
을 재귀로 구한다.

*/


#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

struct Info {
	string name;
	int earn;
};

unordered_map<string, int> profit;
unordered_map<string, string> parent;

int calculate(string seller, int sell_profit)
{
	queue<Info> q;
	q.push({ seller, sell_profit });

	while (!q.empty())
	{
		Info now = q.front();
		q.pop();

		if (now.name == "-")
			return 0;

		int expand = now.earn * 0.1;
		profit[now.name] += now.earn - expand;
		
		// 이부분에서 expand 가 적으면 return 하는 부분 안넣으면 core dump난다....
		if (expand < 1)
			return 0;

		q.push({parent[now.name], expand});
	}
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;

	// map initial
	for (int i = 0; i < enroll.size(); i++)
	{
		profit[enroll[i]] = 0;
		parent[enroll[i]] = referral[i];
	}
	
	for (int i = 0; i < seller.size(); i++)
	{
		calculate(seller[i], amount[i] * 100);
	}


	for (int i = 0; i < enroll.size(); i++)
		answer.push_back(profit[enroll[i]]);
		
    return answer;
}



int main()
{
    vector<int> ans;


    ans = solution(
		{ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" },
		{ "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" },
		{ "young", "john", "tod", "emily", "mary" },
		{ 12,4,2,5,10 }
	);

	/*
	ans = solution(
	{ "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" },
	{ "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" },
	{ "sam", "emily", "jaimie", "edward" },
	{ 2, 3, 5, 4 }
	);*/

    for (auto val : ans)
        cout << val << "\n";
    return 0;
}