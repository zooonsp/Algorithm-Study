## Week22 (23.07.24 ~ 23.08.06)
| 제목 | 내 접근 | 링크 |
| :---: | :---: | :---: |
| [새로운 게임](#새로운-게임) | 구현, 시뮬레이션 | [문제 링크](https://www.acmicpc.net/problem/17780) |
| [기둥과 보 설치](#기둥과-보-설치) | 구현 | [문제 링크](https://school.programmers.co.kr/learn/courses/30/lessons/60061) |
| [축사 배정](#축사-배정) | Network Flow | [문제 링크](https://www.acmicpc.net/problem/2188) |

<br>

## 새로운 게임
- [문제 링크](https://www.acmicpc.net/problem/17780)
- 문제 유형 : 구현, 시뮬레이션

<br>

## 기둥과 보 설치
- [문제 링크](https://school.programmers.co.kr/learn/courses/30/lessons/60061)
- 문제 유형 : 구현.
- 고려해야 할 사항들은 전부 고려했었는데.. 다른 데서 문제가 생겼음!!
- [해설 링크](https://tech.kakao.com/2019/10/02/kakao-blind-recruitment-2020-round1/)
  - 문제 5번.
```cpp
// 설치 => 삭제 => 설치하면 2번 들어가네.. ㅋㅋ ㅠㅠㅠㅠㅠㅠㅠ
for (vector<int>& frame : build_frame) {
		int x, y, a, b;
		x = frame[0], y = frame[1], a = frame[2], b = frame[3];
		if (b == 0) continue; // 삭제는 스킵
		if (Map[x][y][a]) {
			answer.push_back({ x,y,a });
		}
	}

	sort(begin(answer), end(answer), [](vector<int>& first, vector<int>& second) {
		// x좌표 기준으로 오름차순 정렬하며, x좌표가 같을 경우 y좌표 기준으로 오름차순 정렬
		// x, y좌표가 모두 같은 경우 기둥이 보보다 앞에 오면 됩니다.
		if (first[0] == second[0] && first[1] == second[1]) {
			return first[2] < second[2];
		}
		else if (first[0] == second[0]) {
			return first[1] < second[1];
		}
		return first[0] < second[0];
	});
```

<br>

## 축사 배정
- [문제 링크](https://www.acmicpc.net/problem/2188)
- 문제 유형 : Network Flow
