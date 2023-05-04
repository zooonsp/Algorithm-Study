#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// 각 웹피이지별 정보 ( 기본점수, 링크 점수, 매칭 점수, 외부 링크 벡터 )
struct Info
{
    int base_score;
    double link_score;
    double match_score;
    vector<string> link_vec;
};

vector<Info> web;
map<string, int> web_index;

// 대문자로 변환 하기
int capital_func(string& str)
{
    for (auto& c : str)
    {
        if (c >= 'a' && c <= 'z')
            c = c - 'a' + 'A';
    }
    return 0;
}

// 해당 페이지의 웹url 찾기
const string url_tok = "<META PROPERTY=\"OG:URL\" CONTENT=\"HTTPS://";
string url_func(const string& str)
{
    string ret = "";

    int index = str.find(url_tok);
    index += url_tok.length();
    
    // " 여기 까지만 찾자
    while (str[index] != '\"')
    {
        ret += str[index];
        index++;
    }

    return ret;
}

int word_cnt(string& str, string & word)
{
    int cnt = 0;
    string parse = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || 
            (str[i] >= 'A' && str[i] <= 'Z')))
        {
            if (parse == word)
                cnt++;
            parse = "";
        }
        else parse += str[i];
    }
    return cnt;
}

const string link_tok = "<A HREF=\"HTTPS://";
vector<string> link_func(string& str)
{
    vector<string> ret;
    string parse;
    int index = str.find(link_tok);
    while (index != str.npos)
    {
        parse = "";
        index += link_tok.length();

        // " 여기 까지만 찾자
        while (str[index] != '\"')
        {
            parse += str[index];
            index++;
        }
    
        ret.push_back(parse);
        str = str.substr(index);
        index = str.find(link_tok);
    }
    return ret;
}


int solution(string word, vector<string> pages) {
    int answer = 0;
    int index_cnt = 0;
    double max_score = 0;

    capital_func(word);
    for (int i = 0; i < pages.size(); i++)
    {
        capital_func(pages[i]);
        int base_score = word_cnt(pages[i], word);
        string url = url_func(pages[i]);
        web_index.insert({ url , index_cnt });
        index_cnt++;
        vector<string> link_temp = link_func(pages[i]);
        web.push_back({ base_score, 0.0, 0.0, link_temp });
    }

    for (int i = 0; i < web.size(); i++)
    {
        vector<string> &v = web[i].link_vec;
        for (int j = 0; j < v.size(); j++)
        {
            string str = v[j];
            if (web_index.find(str) == web_index.end()) continue;

            int index = web_index[str];
            web[index].link_score += ((double)web[i].base_score / (double)v.size());
        }
    }
    for (int i = 0; i < web.size(); i++)
    {
        web[i].match_score = (double)web[i].base_score + (double)web[i].link_score;

        if (max_score < web[i].match_score)
        {
            max_score = web[i].match_score;
            answer = i;
        }
    }


    return answer;
}



int main()
{
    cout << solution("blind", { "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>"
        });

    return 0;
}