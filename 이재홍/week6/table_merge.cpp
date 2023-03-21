#include <string>
#include <vector>
#define NMAX 51
using namespace std;

struct RC {
    int r;
    int c;
    bool operator==(const RC &rc) const {return r == rc.r && c == rc.c;}
    bool operator!=(const RC &rc) const {return r != rc.r || c != rc.c;}
};

struct TableFrom {
    int end;
    RC next;
};

string table_value[NMAX][NMAX];
RC table_to[NMAX][NMAX];
TableFrom table_from[NMAX][NMAX];

void init_table() {
    // initialize table_value
    for(int i = 1; i < NMAX; ++i) {
        for(int j = 1; j < NMAX; ++j) {
            table_value[i][j].clear();
        }
    }
    // initialize table_to
    for(int i = 1; i < NMAX; ++i) {
        for(int j = 1; j < NMAX; ++j) {
            table_to[i][j] = {i, j};
        }
    }
    // initialize table_from
    for(int i = 1; i < NMAX; ++i) {
        for(int j = 1; j < NMAX; ++j) {
            table_from[i][j] = {1, };
        }
    }
}

RC find(const RC &rc) {
    if(rc != table_to[rc.r][rc.c]) {return table_to[rc.r][rc.c] = find(table_to[rc.r][rc.c]);}
    return rc;
}

void update(const int &r, const int &c, const string &value) {
    // go to representative cell of merged cells
    RC cell = find({r, c});
    // write new value
    table_value[cell.r][cell.c] = value;
    return;
}

void update(const string &value1, const string &value2) {
    // use visited
    int visited[NMAX][NMAX] = {0, };
    // backtracking
    for(int r = 1; r < NMAX; ++r) {
        for(int c = 1; c < NMAX; ++c) {
            RC cell = find({r, c});
            // pruning
            if(visited[cell.r][cell.c]) {continue;}
            if(table_value[cell.r][cell.c].compare(value1)) {visited[cell.r][cell.c] = 1; continue;}
            // process
            visited[cell.r][cell.c] = 1;
            table_value[cell.r][cell.c] = value2;
        }
    }
    return;
}

void merge(const int &r1, const int &c1, const int &r2, const int &c2) {
    RC cell1 = find({r1, c1});
    RC cell2 = find({r2, c2});
    if(cell1 == cell2) {return;} // same set
    string v1 = table_value[cell1.r][cell1.c];
    string v2 = table_value[cell2.r][cell2.c];
    if(!v1.empty() && v2.empty()) {
        table_to[cell2.r][cell2.c] = cell1; // direct cell2 to cell1
        RC it = cell1;
        while(!table_from[it.r][it.c].end) {it = table_from[it.r][it.c].next;} // connect from list
        table_from[it.r][it.c].end = 0;
        table_from[it.r][it.c].next = cell2;
    }
    else if(v1.empty() && !v2.empty()) {
        table_to[cell1.r][cell1.c] = cell2; // direct cell1 to cell2
        RC it = cell2;
        while(!table_from[it.r][it.c].end) {it = table_from[it.r][it.c].next;} // connect from list
        table_from[it.r][it.c].end = 0;
        table_from[it.r][it.c].next = cell1;
    }
    else {
        table_value[cell2.r][cell2.c].clear(); // delete cell2 value
        table_to[cell2.r][cell2.c] = cell1; // direct cell2 to cell1
        RC it = cell1;
        while(!table_from[it.r][it.c].end) {it = table_from[it.r][it.c].next;} // connect from list
        table_from[it.r][it.c].end = 0;
        table_from[it.r][it.c].next = cell2;
    }
    // no situation with both values being empty
    return;
}

void unmerge(const int &r, const int &c) {
    RC cell = find({r, c});
    if(cell.r != r || cell.c != c) {
        // move value from cell to {r, c}
        table_value[r][c] = table_value[cell.r][cell.c];
        table_value[cell.r][cell.c].clear();
    }
    // unmerge all elements in table_from
    while(!table_from[cell.r][cell.c].end) {
        table_from[cell.r][cell.c].end = 1; // disconnect table_from list
        cell = table_from[cell.r][cell.c].next; // move to next cell
        table_to[cell.r][cell.c] = cell; // point table_to to itself
    }
    return;
}

void print(const int &r, const int &c, vector<string> &answer) {
    RC cell = find({r, c});
    if(table_value[cell.r][cell.c].empty()) {
        answer.push_back("EMPTY");
    }
    else {
        answer.push_back(table_value[cell.r][cell.c]);
    }
    return;
}

string string_extract(const string &str, const int &start, const int &end) {
    string ret_str = str.substr(start, end - start);
    return ret_str;
}

int integer_extract(const string &str, const int &start, const int &end) {
    int ret_int = 0;
    for(int i = start; i < end; ++i) {ret_int *= 10; ret_int += str[i] - '0';}
    return ret_int;
}

int find_split(const string &str, const int &start) {
    int ret_idx = start + 1;
    int str_len = str.size();
    while(str[ret_idx] != ' ' && ret_idx < str_len) {++ret_idx;}
    return ret_idx;
}

vector<string> solution(vector<string> commands) {
    vector<string> answer;
    init_table();
    // read command
    int commands_len = commands.size();
    for(int cmd_it = 0; cmd_it < commands_len; ++cmd_it) {
        if(commands[cmd_it][1] == 'P') { // UPDATE
            int idx_s = 7;
            int idx_e = find_split(commands[cmd_it], idx_s);
            idx_s = idx_e + 1;
            idx_e = find_split(commands[cmd_it], idx_s);
            if(idx_e != commands[cmd_it].size()) { // UPDATE r c value
                int r, c;
                string value;
                int idx_s = 7;
                int idx_e = find_split(commands[cmd_it], idx_s);
                r = integer_extract(commands[cmd_it], idx_s, idx_e);
                idx_s = idx_e + 1;
                idx_e = find_split(commands[cmd_it], idx_s);
                c = integer_extract(commands[cmd_it], idx_s, idx_e);
                idx_s = idx_e + 1;
                idx_e = find_split(commands[cmd_it], idx_s);
                value = string_extract(commands[cmd_it], idx_s, idx_e);
                update(r, c, value);
            }
            else { // UPDATE value1 value2
                string value1, value2;
                int idx_s = 7;
                int idx_e = find_split(commands[cmd_it], idx_s);
                value1 = string_extract(commands[cmd_it], idx_s, idx_e);
                idx_s = idx_e + 1;
                idx_e = find_split(commands[cmd_it], idx_s);
                value2 = string_extract(commands[cmd_it], idx_s, idx_e);
                update(value1, value2);
            }
        }
        else if(commands[cmd_it][1] == 'E') { // MERGE
            int r1, c1, r2, c2;
            int idx_s = 6;
            int idx_e = find_split(commands[cmd_it], idx_s);
            r1 = integer_extract(commands[cmd_it], idx_s, idx_e);
            idx_s = idx_e + 1;
            idx_e = find_split(commands[cmd_it], idx_s);
            c1 = integer_extract(commands[cmd_it], idx_s, idx_e);
            idx_s = idx_e + 1;
            idx_e = find_split(commands[cmd_it], idx_s);
            r2 = integer_extract(commands[cmd_it], idx_s, idx_e);
            idx_s = idx_e + 1;
            idx_e = find_split(commands[cmd_it], idx_s);
            c2 = integer_extract(commands[cmd_it], idx_s, idx_e);
            merge(r1, c1, r2, c2);
        }
        else if(commands[cmd_it][1] == 'N') { // UNMERGE
            int r, c;
            int idx_s = 8;
            int idx_e = find_split(commands[cmd_it], idx_s);
            r = integer_extract(commands[cmd_it], idx_s, idx_e);
            idx_s = idx_e + 1;
            idx_e = find_split(commands[cmd_it], idx_s);
            c = integer_extract(commands[cmd_it], idx_s, idx_e);
            unmerge(r, c);
        }
        else if(commands[cmd_it][1] == 'R') { // PRINT
            int r, c;
            int idx_s = 6;
            int idx_e = find_split(commands[cmd_it], idx_s);
            r = integer_extract(commands[cmd_it], idx_s, idx_e);
            idx_s = idx_e + 1;
            idx_e = find_split(commands[cmd_it], idx_s);
            c = integer_extract(commands[cmd_it], idx_s, idx_e);
            print(r, c, answer);
        }
    }
    return answer;
}