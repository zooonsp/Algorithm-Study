# Week 07 (23.03.20 ~ 23.03.26)

## 전화번호 목록

### 접근 방법

- 한 번호가 다른 번호의 접두어인지 확인 → 문자열 저장 및 탐색 → 트라이(Trie)

### 구현 내용

- `Node` 구조체
  - `bool isEnd` : 전화번호의 끝인가?
  - `Node *child[10]` : child node를 가리킬 포인터 배열(0~9)
  - 생성자를 이용한 멤버 변수 초기화
- `Trie` 클래스
  - `Node head` : Trie의 최상단 Node
  - `bool insert(string str)`
    - `ptr` : Node를 가리킬 포인터. head를 가리키도록 초기화
    - 전화번호(str)를 처음부터 끝까지 확인하며
      - num에 해당하는 child가 없다면 생성
      - 이미 해당 전화번호로 끝난 경우가 있다면 false 반환
      - `ptr`이 child node를 가리키도록 변경
    - 전화번호의 끝 표시(`isEnd`)
    - true 반환
  - `bool find(string str)`
    - `ptr` : Node를 가리킬 포인터. head를 가리키도록 초기화
    - 전화번호(str)를 처음부터 끝까지 확인하며
      - num에 해당하는 child가 없다면 false 반환
      - `ptr`이 child node를 가리키도록 변경
    - 전화번호의 끝인가?(`isEnd`)를 반환
- `main`
  - 전화번호를 입력받는다.
  - 전화번호를 오름차순으로 정렬
  - `Trie`에 insert 하면서 접두어가 있는지 확인. 접두어가 있다면 일관성 있는 목록이 아니다.

## 줄기세포배양

### 접근 방법

- Priority Queue를 이용한 시뮬레이션

### 구현 내용

- `Node` 구조체
  - x, y : 줄기세포의 좌표
  - vitality : 생명력
  - time : 번식하는 시간
  - PQ에서 작은 시간 우선, 높은 생명력 우선
- `cnt` : K시간 이후에 살아있는 번식을 마친 줄기세포 수
- 초기 상태 크기에 맞춰 MAP 중앙에 위치시킬 수 있는 Offset 계산
- MAP 중앙(Offset만큼 떨어진 위치)에 초기 상태 입력
- 줄기세포라면 PQ에 push
  - 번식하는 시간은 생명력 + 1
- simulation
  - 1시간 ~ K시간 반복
    - `while(true)`
      - 줄기세포가 없으면 break
      - 현재 시간에 번식하는 줄기세포가 없으면 break
      - now : 지금 번식하는 줄기세포
      - 현재 줄기세포가 K시간 이후에 살아있다면 cnt 증가
      - 4방향으로 번식
        - 이미 줄기세포가 존재하는 경우 번식 X
        - 다음 줄기세포가 번식하는 시간은 현재 시간(k) + 생명력 + 1
- 정답 : PQ에 남아있는 줄기세포 수 + K시간 이후 살아있는 번식을 마친 줄기세포 수

## 스타트 택시

### 접근 방법

- Flood Fill을 이용한 시뮬레이션

### 구현 내용

- `MAP[][]`
  - -1 : 벽
  - 0 : 빈 공간
  - 1이상 : 손님
- `clientDest[n]` : n번 손님의 목적지 좌표
- `MAP` 주변 울타리 치기(-1)
- `MAP` 정보를 입력받으며 입력이 1인 경우 -1로 변경
- 손님의 시작 위치는 `MAP`에 표시, 손님의 목적지 좌표는 `clientDest`에 저장
- M명의 손님을 태우는 simulation 진행
  - `clients` : 가장 가까운 손님의 좌표를 담을 vector
  - taxi의 위치에서 시작
  - queue가 빌 때까지 반복
    - 단계별 Flood Fill
      - 손님인 경우 clients에 push
    - 손님이 있다면 break
  - 갈 수 있는 곳을 다 확인했는데 손님이 없으면 false 반환
  - `clients` 정렬(작은 행 번호 우선, 작은 열 번호 우선)
  - taxi가 손님의 위치로 이동
  - `clientId` : 손님의 ID
  - `dist` : 손님까지의 최단 거리
  - `ndest` : 현재 손님의 목적지 좌표
  - 손님의 위치까지 가는데 연료가 부족한 경우 false 반환
  - 연료 소모
  - 손님을 태웠으므로 해당 위치의 `MAP`을 빈 공간으로 만들기
  - `visited`, `queue` 초기화
  - taxi의 위치에서 시작
  - Flood Fill
    - 목적지에 도달하면 break
  - `dist` : 목적지까지의 최단 거리
  - 연료가 부족하거나 목적지까지 갈 수 없는 경우 false 반환
  - taxi가 목적지까지 이동
  - 연료 충전
  - true 반환
- M명의 손님 태우기가 불가능한 경우 정답은 -1

## 자물쇠와 열쇠

### 접근 방법

- key를 회전시켜며 key와 lock을 위치시킬 수 있는 모든 경우를 확인

### 구현 내용

- `void rotateCW(vector<vector<int>> &v)` : 2차원 vector를 시계 방향으로 회전
- M : key의 size
- N : lock의 size
- dir → 0 ~ 4 (key를 4번 회전)
  - sy → 0 ~ M+N (key의 시작 y좌표)
    - sx → 0 ~ M+N (key의 시작 x좌표)
      - board → lock의 상하좌우로 M 만큼의 여유 공간
      - key를 board에 위치시키기
      - flag : key로 lock을 열 수 있는가?
      - lock을 확인하며
        - key와 lock이 둘 다 0이거나 둘 다 1인 경우 열 수 없다. → flag = false
      - 만약 열 수 있으면 true 반환
  - key 회전
- 모든 경우를 확인했는데 열 수 없었으니 false 반환

