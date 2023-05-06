#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct MatchingScore {
    long double base;
    long double link;
};

string get_content_url(string &str) {
    const size_t PREFIX_SIZE_1 = 5UL;
    const size_t PREFIX_SIZE_2 = 8UL;
    size_t left = 0UL;
    size_t mid = 1UL;
    size_t right = 0UL;
    while(right < mid) {
        left = str.find("<meta", left) + PREFIX_SIZE_1;
        right = str.find('>', left);
        mid = str.find("https://", left) + PREFIX_SIZE_2;
        if(right < mid) {continue;}
        right = str.find('"', mid);
    }
    return str.substr(mid, right - mid);
}

void get_link(string &str, vector<string> &links) {
    const size_t PREFIX_SIZE = 17UL;
    size_t start = 0UL;
    size_t end = 0UL;
    while((start = str.find("<a href=\"https://", end)) != string::npos) {
        start += PREFIX_SIZE;
        end = str.find('"', start);
        links.push_back(str.substr(start, end - start));
    }
}

string filter_alphabet(string &str, string prefix, string suffix) {
    string result;
    result.reserve(str.size() + prefix.size() + suffix.size());
    result += prefix;
    int str_size = str.size();
    for(int it = 0; it < str_size; ++it) {
        char ch = str[it] | 0x20;
        if('a' <= ch && ch <= 'z') {result += ch;}
        else {result += ' ';}
    }
    result += suffix;
    return result;
}

int find_word(string &word, string &str) {
    size_t word_size = word.size() - 1UL;
    int word_count = 0;
    size_t index = 0UL;
    while((index = str.find(word, index)) != string::npos) {
        index += word_size;
        ++word_count;
    }
    return word_count;
}

int solution(string word, vector<string> pages) {
    int pages_size = pages.size();
    vector<MatchingScore> scores = vector<MatchingScore>(pages_size);
    unordered_map<string,int> um;
    word = filter_alphabet(word, " ", " ");
    for(int it = 0; it < pages_size; ++it) {
        um[get_content_url(pages[it])] = it;
        string filtered = filter_alphabet(pages[it], " ", " ");
        scores[it].base = find_word(word, filtered);
    }
    for(int it = 0; it < pages_size; ++it) {
        vector<string> links;
        get_link(pages[it], links);
        int links_size = links.size();
        long double link_score = 0.0L;
        if(links_size) {link_score = scores[it].base / (long double)links_size;}
        for(string &link : links) {
            if(um.find(link) == um.end()) {continue;}
            int id = um[link];
            scores[id].link += link_score;
        }
    }
    int answer = 0;
    int it = 0;
    long double max_score = 0.0L;
    for(MatchingScore &score : scores) {
        long double now_score = score.base + score.link;
        if(max_score < now_score) {
            answer = it;
            max_score = now_score + 0.00001L;
        }
        ++it;
    }

    return answer;
}