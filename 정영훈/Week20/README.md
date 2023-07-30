## Week20 (23.07.10 ~ 23.07.16)
| 제목 | 내 접근 | 링크 |
| :---: | :---: | :---: |
| [Geometry (기하 - 벡터의 활용)](#geometry-기하---벡터의-활용) | Geometry (기하 - 벡터의 활용) | [CCW](https://www.acmicpc.net/problem/11758), [다각형의 면적](https://www.acmicpc.net/problem/2166) | 
| [최단 거리](#최단-거리를-찾는-알고리즘dijkstra-floyd-warshall-bellman-ford) | 최단 거리 찾기 | [개코전쟁](https://www.acmicpc.net/problem/2325), [오민식의 고민](https://www.acmicpc.net/problem/1219), [Ignition](https://www.acmicpc.net/problem/13141) |
| [블록 이동하기](#블록-이동하기) | 구현 | [블록 이동하기](https://school.programmers.co.kr/learn/courses/30/lessons/60063)

<br>

## Geometry (기하 - 벡터의 활용)
[개념 공부용 링크](https://m.blog.naver.com/kks227/220794097589)

**문제 링크**
1. [CCW](https://www.acmicpc.net/problem/11758)
2. [다각형의 면적](https://www.acmicpc.net/problem/2166)

<br>

## 최단 거리를 찾는 알고리즘(Dijkstra, Bellman-Ford, Floyd-Warshall)

### Dijkstra
[개코전쟁](https://www.acmicpc.net/problem/2325)

### Bellman-Ford
[오민식의 고민](https://www.acmicpc.net/problem/1219)

### Floyd-Warshall
[Ignition](https://www.acmicpc.net/problem/13141)

<br>

## 블록 이동하기

- [해설 링크](https://tech.kakao.com/2019/10/02/kakao-blind-recruitment-2020-round1/#elementor-toc__heading-anchor-38)
- 내 접근 : 구현
- 구현 과정에서 빠뜨린 부분이 있어서 제대로 정답이 나오지 않았음..!!! (적어놓고 구성하자!)
```cpp
// 이거 두 줄?.. 빼먹어서 ㅇ으어러어렁러어어ㅓ
if (board[nx][ny] == 1) continue;
if (board[otherNx][otherNy] == 1) continue;
```