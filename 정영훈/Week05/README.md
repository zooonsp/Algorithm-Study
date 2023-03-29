## Week 05 (23.03.06 ~ 23.03.12)
| 제목 | 내 접근 | 링크 |
| :---: | :---: | :---: |
| [코딩 테스트 공부](#코딩-테스트-공부) | DP | [문제 링크](https://school.programmers.co.kr/learn/courses/30/lessons/118668) |
| [프로세서 연결하기](#프로세서-연결하기) | 완전 탐색(DFS) | [문제 링크](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV4suNtaXFEDFAUf)
| [머리 맞대기](#머리-맞대기) | Parametric Search | [문제 링크](https://pro.mincoding.co.kr/problem-step/7/level/108/detail/M4_04)
| [구간 나누기2](#구간-나누기-2) | Parametric Search | [문제 링크](https://www.acmicpc.net/problem/13397)


## 코딩 테스트 공부
- [문제 링크](https://school.programmers.co.kr/learn/courses/30/lessons/118668)
- 내 접근 : DP
- [해설 링크](https://tech.kakao.com/2022/07/13/2022-coding-test-summer-internship/)

    ![스터디 (20)(5)](https://user-images.githubusercontent.com/75352656/224534097-c3fddb15-3ab1-41f9-8b70-0b0b270d361a.png)
    ![스터디 (21)(4)](https://user-images.githubusercontent.com/75352656/224534103-ba3aafa9-6ea0-4094-9466-0e79744dfe25.png)

### DP(TopDown, BottomUp)
![image](https://user-images.githubusercontent.com/75352656/224555816-651726cd-4b92-46ab-8652-56247ec932df.png)
- TopDown 구현은 -> Profornann

### Dijkstra
- Dijkstra 구현 -> h78749891



## 프로세서 연결하기
- [문제 링크](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV4suNtaXFEDFAUf)
- 내 접근 : 완전 탐색(DFS)
    ![스터디 (17)(8)](https://user-images.githubusercontent.com/75352656/224534085-ebbbbb09-4beb-484f-bb16-65ed24d1fe19.png)
    - 단순히 시간 복잡도를 계산하면 TC * 5^cores로 계산할 수 있음.
    - 5^12 = 244140625, TC * 5^cores = 14,648,437,500이라는 엄청난 수가 나옴.
    - 그렇다면 이 문제가 어떻게 완전 탐색으로 시간 내에 풀리는가? -> Branch And Bound
    - 이론 상으로 계산한 모든 경우에 대한 확인을 다 하지 않는 경우가 생기기 때문임!
    

## 머리 맞대기
- [문제 링크](https://pro.mincoding.co.kr/problem-step/7/level/108/detail/M4_04)
- 내 접근 : Parametric Search

    ![스터디 (18)(7)](https://user-images.githubusercontent.com/75352656/224534093-311a6821-82aa-42a0-af03-75091fadec07.png)

## 구간 나누기 2
- [문제 링크](https://www.acmicpc.net/problem/13397)
- 내 접근 : Parametric Search
    ![스터디 (19)(6)](https://user-images.githubusercontent.com/75352656/224534095-d8301133-639f-4b63-b788-6073e92b31ee.png)
