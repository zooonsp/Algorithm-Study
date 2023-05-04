// 기본 점수 = 검색어 등장 횟수 (대소문자 무시)
// 외부 링크 수 = 다른 외부 페이지로 연결된 링크 수 (outorder 개수)
// 링크 점수 = 해당 웹 페이지로 링크가 걸린 다른 웹페이지의 기본 점수 / 외부 링크 수 총합 (inorder 계산)
// 한 웹페이지의 매칭 점수 = 기본 점수 + 링크 점수

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <iterator>

using namespace std;

struct page {
	double basic, link;
};

int solution(string word, vector<string> pages) {
	int wlen = (int)word.length(), n = (int)pages.size();

	//regex::icase -> 대소문자 구별 X
	// (https:\/\/\S+) : capture 그룹
	string strPageName(R"(<meta\s+[^>]*?property\s*=\s*['"]og:url['"][^>]*?\s+content\s*=\s*['"](https:\/\/\S+)['"][^>]*>)");
	regex rePname(strPageName, regex::icase);
	
	// (https?:\/\/\S+) : capture 그룹
	string strHRef(R"(<a\s+[^>]*?href\s*=\s*['"](https?:\/\/\S+)['"][^>]*>)");
	regex reHRef(strHRef, regex::icase);

	string strWord(R"([^a-z]()" + word + R"([^a-z])+)");
	regex    reWord(strWord, regex::icase);
	// string target = "(?![:alpha:])Blind(?![:alpha:])";
	// regex reWord(target, regex_constants::icase);
	smatch matchResult; // 검색 결과 저장

	map<string, int> mp; //주소 : 인덱스
	page pg[20] = { 0 };

	// auto e = sregex_iterator();
	sregex_iterator e;
	for (int i = 0; i < n; ++i) {
		regex_search(pages[i], matchResult, rePname);
		mp[matchResult[1]] = i; // 캡쳐 결과 or matchResult[1].str()

		// 왜 이거는 안 되는 거지..
		// Blind_Blind@Blind_Blind
		// pg[i].basic = distance(sregex_iterator(begin(pages[i]), end(pages[i]), reWord), e);
		sregex_iterator s = sregex_iterator(begin(pages[i]), end(pages[i]), reWord);
		pg[i].basic = 0;
		while (s != e) {
			pg[i].basic += (s->str().length() - 1) / (wlen + 1);
			++s;
		}
	}

	for (int i = 0; i < n; ++i) {
		auto s = sregex_iterator(pages[i].begin(), pages[i].end(), reHRef); //link
		int dv = (int)distance(s, e); // 연결된 링크된 개수
		while (s != e) {
			if (mp.find((*s)[1].str()) != mp.end()) { // 링크된 웹사이트가 기록되어 있으면
				pg[mp[(*s)[1].str()]].link += pg[i].basic / dv; // (O)
				// pg[mp[(s++)->str()]].link += pg[i].basic / dv; (X) (한 칸 더 가는 게 아님)
			}
			++s;
		}
	}

	double mx = pg[0].basic + pg[0].link; //최댓값 찾기
	int mx_idx = 0;
	for (int i = 1; i < n; ++i) {
		if (pg[i].basic + pg[i].link > mx) {
			mx = pg[i].basic + pg[i].link;
			mx_idx = i;
		}
	}

	return mx_idx;
}