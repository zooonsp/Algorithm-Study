## Week 11 (23.04.17 ~ 23.04.23)
| 제목 | 내 접근 | 링크 |
| :---: | :---: | :---: |
| [크루스칼의 공](#크루스칼의-공) | - | [문제 링크](https://www.acmicpc.net/problem/1396) |
| [광고 삽입](#광고-삽입) | - | [문제 링크](https://school.programmers.co.kr/learn/courses/30/lessons/72414) |
| [치즈](#치즈) | BFS, 구현 | [문제 링크](https://www.acmicpc.net/problem/2636) |


## 크루스칼의 공
- [문제 링크](https://www.acmicpc.net/problem/1396)
- 접근 못 함.
- Parallel Binary Search
- [참고 링크](https://rebro.kr/153)
- 다른 풀이(MST + UnionFind + LCA) [링크](https://blog.naver.com/jinhan814/222146989211)

## 광고 삽입
- [문제 링크](https://school.programmers.co.kr/learn/courses/30/lessons/72414)
- [해설 링크](https://tech.kakao.com/2021/01/25/2021-kakao-recruitment-round-1/)
- 그냥 시작점만 다 확인하면 될 거 같은 느낌? => X..
- 구간에 있는 사람 개수 세서 누적 합.
  - 미흡했던 점 => 아이디어 구상 후 4시간 더 걸림..
    - 구간합에서 같은 구간에 여러 값이 있을 수 있다는 점을 놓침 -> while문 이용
    - time ~ endTimeInt 재생 시 시청자 수가 timeTable[endTimeInt] - timeTable[time - 1]가 아니었음.
      - TC 1에서 695초 ~ 1550초로 계산해서 사람 수를 계산하는 경우에 3번 로그가 포함되어 버림. (마지막 구간을 포함하면 안 됨)
      - time이 답이기 위해서는 timeTable[endTimeInt - 1] - timeTable[time - 1]로 계산했어야 함.

- 구간 합 계산하는 다른 방법 : sliding window도 있다..

## 치즈
- [문제 링크](https://www.acmicpc.net/problem/2636)
- 내 접근 : BFS, 구현

