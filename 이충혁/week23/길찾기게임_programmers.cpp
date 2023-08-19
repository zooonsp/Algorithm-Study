#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

enum
{
    X = 0,
    Y = 1,
    INDEX = 2
};

/*
nodeinfo <= 10000
nodeinfo[i] 는 i + 1의 x, y 좌표이다.

좌표값 <= 100000

트리의 깊이 <= 1000 ( dfs 될거 같다 )

시간복잡도 : 정렬 할때 최악의 경우 nlogn이라고 생각하면 100만. 충분하다.
+ dfs 시간 복잡도는 N? 10000 인가?
*/

vector<pair<int, int>> graph;
vector<vector<int>> nodeinfo_copy;
vector<int> pre_order;
vector<int> post_order;
// 해당 깊이의 index가 시작되는 부분

int make_tree(int stand, vector<int> now)
{
    if (nodeinfo_copy[stand - 1][X] > now[X])
    {
        if (graph[stand].first == stand)
        {
            graph[stand].first = now[INDEX];
            return 0;
        }
        else
        {
            make_tree(graph[stand].first, now);
        }
    }
    else
    {
        if (graph[stand].second == stand)
        {
            graph[stand].second = now[INDEX];
            return 0;
        }
        else
        {
            make_tree(graph[stand].second, now);
        }
    }
    return 0;
}

int pre_func(int now)
{
    pre_order.push_back(now);
    if (graph[now].first != now)
    {
        pre_func(graph[now].first);
    }
    if (graph[now].second != now)
    {
        pre_func(graph[now].second);
    }

    return 0;
}

int post_func(int now)
{
    if (graph[now].first != now)
    {
        post_func(graph[now].first);
    }
    if (graph[now].second != now)
    {
        post_func(graph[now].second);
    }
    post_order.push_back(now);

    return 0;
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;


    // 정렬할 때 origin index를 갖고 정렬할 수 있도록
    for (int i = 0; i < nodeinfo.size(); i++)
        nodeinfo[i].push_back(i + 1);

    nodeinfo_copy.assign(nodeinfo.begin(), nodeinfo.end());

    sort(nodeinfo.begin(), nodeinfo.end(), 
        [](const vector<int>& a, const vector<int>& b)
        {
            if (a[Y] == b[Y])
                return a[X] < b[X];
            
            return a[Y] > b[Y];
        });
    
    // 트리를 만들자
    graph.resize(nodeinfo.size() + 1);
    // 값을 미리 넣어주자
    for (int i = 0; i < nodeinfo.size() + 1; i++)
        graph[i] = { i, i };

    for (int i = 1; i < nodeinfo.size(); i++)
    {
        make_tree(nodeinfo[0][INDEX], nodeinfo[i]);
    }


    pre_func(nodeinfo[0][INDEX]);
    post_func(nodeinfo[0][INDEX]);

    answer.push_back(pre_order);
    answer.push_back(post_order);

    return answer;
}




int main()
{

    vector<vector<int>> ans;

    ans = solution({ {5, 3},{11, 5},{13, 3},{3, 5},{6, 1},{1, 3},{8, 6},{7, 2},{2, 2 } });

    for (auto& pt : ans)
    {
        cout << "x : " << pt[X];
        cout << "    y : " << pt[Y] << endl;
    }

	return 0;
}