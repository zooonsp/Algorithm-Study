#include <unordered_map>
#include <vector>
using namespace std;

const string urlBegin{"<meta property=\"og:url\" content=\""};
const string urlEnd{"\"/>"};
const string linkBegin{"<a href=\""};
const string linkEnd{"\">"};

bool isLowerAlpha(char ch) { return ch >= 'a' && ch <= 'z'; }

void toLower(string &str) {
  for (char &ch : str)
    if (ch >= 'A' && ch <= 'Z')
      ch ^= 0x20;
}

int solution(string word, vector<string> pages) {
  const int N = pages.size();
  toLower(word);

  vector<int> basicScore(N);
  vector<double> linkScore(N);
  vector<string> url(N);
  vector<vector<string>> links(N);
  unordered_map<string, int> url2idx;

  for (int i = 0; i < N; i++) {
    string page = pages[i];

    toLower(page);

    // basic score
    int beginIdx = 0, endIdx = 0;

    while (true) {
      beginIdx = page.find(word, beginIdx);

      if (beginIdx == string::npos)
        break;

      endIdx = beginIdx + word.size();

      if (!isLowerAlpha(page[beginIdx - 1]) && !isLowerAlpha(page[endIdx]))
        basicScore[i]++;

      beginIdx = endIdx;
    }

    // url
    beginIdx = page.find(urlBegin) + urlBegin.size();
    endIdx = page.find(urlEnd, beginIdx);

    url[i] = page.substr(beginIdx, endIdx - beginIdx);
    url2idx[url[i]] = i;

    // links
    beginIdx = endIdx = 0;

    while (true) {
      beginIdx = page.find(linkBegin, beginIdx);

      if (beginIdx == string::npos)
        break;

      beginIdx += linkBegin.size();
      endIdx = page.find(linkEnd, beginIdx);

      links[i].push_back(page.substr(beginIdx, endIdx - beginIdx));

      beginIdx = endIdx;
    }
  }

  // link score
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < links[i].size(); j++) {
      if (url2idx.find(links[i][j]) == url2idx.end())
        continue;

      int from = url2idx[url[i]];
      int to = url2idx[links[i][j]];

      linkScore[to] += (double)basicScore[from] / (double)links[from].size();
    }
  }

  int answer = 0;
  double maxScore = 0;

  for (int i = 0; i < N; i++) {
    double score = basicScore[i] + linkScore[i];

    if (maxScore < score) {
      maxScore = score;
      answer = i;
    }
  }

  return answer;
}
