#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
using ll = long long;

int t, n;

bool checkValid() {
    unordered_map<ll,int> um; // 1: number, 2: sub-number
    bool res = true;
    int i;
    for(i = 0; i < n; ++i) {
        string str;
        cin >> str;
        str = "1" + str;
        ll input = stoll(str);
        // check if this number is included by others
        if(um[input] == 2) {res = false; break;}
        um[input] = 1;
        input /= 10;
        // check if other number includes this
        while(input) {
            if(um[input] == 1) {res = false; break;}
            if(um[input] == 2) {break;}
            um[input] = 2;
            input /= 10;
        }
        // stop processing if list is not valid
        if(!res) {break;}
    }
    // empty input buffer
    for(++i; i < n; ++i) {
        ll input;
        cin >> input;
    }
    return res;
}

int main() {
    // initiate fast io
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> t;
    for(int tc = 1; tc <= t; ++tc) {
        cin >> n;
        if(checkValid()) {cout << "YES\n";}
        else {cout << "NO\n";}
    }
    return 0;
}