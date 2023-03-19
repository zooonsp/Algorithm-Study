## Week 06 (23.03.13 ~ 23.03.19)
| 제목 | 내 접근 | 링크 |
| :---: | :---: | :---: |
| [표 병합](#표-병합) | UnionFind | [문제 링크](https://school.programmers.co.kr/learn/courses/30/lessons/150366) | 
| [안정적인 전압](#안정적인-전압) | Prefix Sum(누적 합) | [문제 링크](https://pro.mincoding.co.kr/enterprise/contest/ssafy_9/275/problem/Hyundai_03) | 
| [연구소3](#연구소3) | DFS + BFS | [문제 링크](https://www.acmicpc.net/problem/17142) | 
| [핀볼 게임](#핀볼-게임) | 구현 | [문제 링크](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo) | 

## 표 병합
- [문제 링크](https://school.programmers.co.kr/learn/courses/30/lessons/150366)
- 내 접근 : UnionFind (결합하고 해제하는 과정이 있어서)
- [해설 링크](https://tech.kakao.com/2023/01/25/2023-kakao-recruitment-round-1/#elementor-toc__heading-anchor-6)

    ![표 병합](https://user-images.githubusercontent.com/75352656/226152691-5f8edb72-ab60-4ef8-928d-ff69eebdd578.png)

### UnionFind
- [항상 디버깅 후 생각 나는 주의 사항](https://sangwoo0727.github.io/algorithm/Algorithm-UnionFind/)

</br>

## 안정적인 전압
- [문제 링크](https://pro.mincoding.co.kr/enterprise/contest/ssafy_9/275/problem/Hyundai_03)
- 내 초기 접근 : 다 누적합 만들면서 새로 계산 -> TLE..
- 새로운 접근 : 만들어 놓은 누적합을 이용하는 아이디어

    ![안정적인 전압](https://user-images.githubusercontent.com/75352656/226152672-4d5593ff-51ff-44ab-a382-705e0713d978.png)


</br>

## 핀볼 게임
- [문제 링크](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRF8s6ezEDFAUo)
- 내 접근 : 요구 조건 만족하도록 구현
- 생긴 문제 : vector로 동적할당을 통해 매번 Map을 만드는 경우 시간 초과 발생 -> 그냥 배열을 사용해서 해결

    ![핀볼 게임](https://user-images.githubusercontent.com/75352656/226152694-f24bc628-6d69-4d84-a2c2-d65921459006.png)

</br>

## 연구소3
- [문제 링크](https://www.acmicpc.net/problem/17142)
- 내 접근 : DFS(모든 조합) + BFS(찾은 조합으로 계산)
- 최소 시간이라 가지치기가 가능

    ![연구소3](https://user-images.githubusercontent.com/75352656/226152688-349d1cec-0849-4823-817c-35d3a02d375b.png)