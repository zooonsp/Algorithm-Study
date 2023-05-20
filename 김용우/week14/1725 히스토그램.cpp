#include <iostream>
#include <algorithm>

int N;  // N: 히스토그램의 가 칸의 수
int height[100'001];    // height: i 칸의 높이
int ans;    // ans: 가장 큰 직사각형의 넓이

int calRectArea(int left, int right){   // left: 시작 칸, right: 끝 칸
    if(left == right) return height[left];  // 시작 칸과 끝 칸이 같다면, 가로 1칸에 left의 높이를 갖는 넓이 반환

    int mid = (left + right) / 2;   // mid: 히스토그램의 중간
    int area = std::max(calRectArea(left, mid), calRectArea(mid + 1, right));   // area: 중간을 기준으로 왼쪽과 오른쪽에서의 최대 넓이

    // 중간에서 부터 양쪽으로 확장
    int h = height[mid];    // h: 가질 수 있는 높이
    int l = mid, r = mid;   // l: 왼쪽 확장 칸, r: 오른쪽 확장 칸
    while(l > left || r < right){   // 왼쪽이나 오른쪽의 범위를 벗어나지 않을 때 까지 반복
        int leftHeight, rightHeight;    // leftHeight: 왼쪽으로 확장하였을 경우 최대 높이, rightHeight: 오른쪽으로 확장하였을 때의 최대 높이

        if(l > left)
            leftHeight = height[l - 1]; // 왼쪽 확장 높이 갱신
        else
            leftHeight = -1;    // 더 이상 확장할 수 없으므로 -1
        
        if(r < right)
            rightHeight = height[r + 1];    // 오른쪽 확장 높이 갱신
        else
            rightHeight = -1;   // 더 이상 확장할 수 없으므로 -1

        if(leftHeight > rightHeight){   // 왼쪽으로 확장하는 것이 더 넓은 너비를 갖는 경우
            h = std::min(h, leftHeight);    // 높이 갱신
            l--;    // 왼쪽 이동 갱신
        }
        else{   // 오른쪽으로 확장하는 것이 더 넓은 너비를 갖는 경우
            h = std::min(h, rightHeight);   // 높이 갱신
            r++;    // 오른쪽 이동 갱신
        }
        area = std::max(area, h * (r - l + 1)); // 가장 큰 직사각형의 넓이 갱신
    }

    return area;
}

void sol(){

    ans = calRectArea(0, N-1);  // 0에서 N-1칸 까지에서 나올 수 있는 가장 큰 직사각형의 넓이

    return;
}

void input(){

    std::cin >> N;  // 칸의 수
    for(int i=0; i<N; i++) std::cin >> height[i];   // 각 칸의 높이

    return;
}

int main(){

    input();

    sol();

    std::cout << ans;

    return 0;
}