#include <iostream>

struct Idx{
    int start, end; // start: 분할 시작점, end: 분할 끝점
};

int n;  // n: 정점의 개수
int inorder[100'001];   // inorder[i]: 이진 트리를 중위 순회 하였을 때 i 번째 정점 번호
int inorderIdx[100'001];    // inorderIdx[i]: i 번호를 갖는 정점의 중위 순위에서의 순서 
int postorder[100'001]; // postorder[i]: 이진 트리를 후위 순회 하였을 때 i 번째 정점 번호

void preorder(Idx inIdx, Idx postIdx){  // inIdx: 중위 순회 시작과 끝, postIdx: 후위 순회 시작과 끝

    if(inIdx.start > inIdx.end || postIdx.start > postIdx.end) return;  // 더 이상 트리를 분할 할 수 없는 경우 return

    int rootIdx = inorderIdx[postorder[postIdx.end]];   // rootIdx: 중위 순회에서의 루트의 순서 -> 후위 순회의 가장 마지막 수는 분할 된 트리의 루트
    int leftSize = rootIdx - inIdx.start;   // leftSize: 중위 순회에서 루트를 기준으로 왼쪽에 존재하는 정점의 수
    int rightSize = inIdx.end - rootIdx;    // rightSize: 중위 순회에서 루트를 기준으로 오른쪽에 존재하는 정점의 수

    std::cout << inorder[rootIdx] << ' ';   // 루트 출력

    preorder({inIdx.start, rootIdx - 1}, {postIdx.start, postIdx.start + leftSize - 1});    // 트리의 왼쪽 분할
    preorder({rootIdx + 1, inIdx.end}, {postIdx.start + leftSize, postIdx.end - 1});    // 트리의 오른쪽 분할

    return;
}

void sol(){

    preorder({0, n-1}, {0, n-1});

    return;
}

void input(){

    std::cin >> n;

    for(int i=0; i<n; i++){ // 중위 순회 입력
        std::cin >> inorder[i];
        inorderIdx[inorder[i]] = i;
    }
    for(int i=0; i<n; i++) std::cin >> postorder[i];    // 후위 순회 입력

    return;
}

int main(){

    input();
    sol();

    return 0;
}