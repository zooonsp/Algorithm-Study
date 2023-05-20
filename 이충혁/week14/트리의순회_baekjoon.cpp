#include <iostream>

using namespace std;

const int TREE_MAX = 101010;

int N; // 정점 수
int inorder[TREE_MAX];
int postorder[TREE_MAX];


int input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> inorder[i];
    
    for (int i = 0; i < N; i++)
        cin >> postorder[i];

    return 0;
}

int dfs(int in_L, int in_R, int post_L, int post_R) // 재귀... dfs라고 봐도 되나?
{
    // 기저 조건
    if (in_L > in_R || post_L > post_R)
        return 0;

    int root = postorder[post_R];
    int in_root_index = -1;

    cout << root << " "; // 상위 루트부터 순서대로 출력하면된다!

    for (int i = in_L; i <= in_R; i++) {
        if (inorder[i] == root) {
            in_root_index = i;
            break;
        }
    }

    // 남은 왼쪽 노드 갯수를 확인하여 하단 트리들로 재귀
    int left_node = in_root_index - in_L;


    dfs(in_L, in_root_index - 1, post_L, post_L + left_node - 1);
    dfs(in_root_index + 1, in_R, post_L + left_node, post_R - 1);

    return 0;
}



int main()
{
    cin.tie(NULL)->sync_with_stdio(false);

    input();
    dfs(0, N - 1, 0, N - 1);
    return 0;
}

