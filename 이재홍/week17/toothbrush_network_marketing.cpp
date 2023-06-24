#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    vector<int> downline;
    int tier;
    vector<int> fee;
    Node(): downline(), tier(0), fee() {}
    void set_tier(int tier_value) {
        tier = tier_value;
        fee = vector<int>(tier + 1, 0);
    }
    void add_profit(int profit) {
        for(int it = tier; 0 <= it; --it) {
            fee[it] += profit - (profit / 10);
            profit /= 10; 
        }
    }
};

struct Tree {
    int size;
    vector<Node> nodes;
    Tree(int size): size(size), nodes(vector<Node>(size, Node())) {}
    Node &operator[](int index) {return nodes[index];}
};

void dfs(Tree &tree, int id, vector<int> &result) {
    vector<int> &downline = tree[id].downline;
    for(int recruit: downline) {
        dfs(tree, recruit, result);
        for(int it = 0; it <= tree[id].tier; ++it) {
            tree[id].fee[it] += tree[recruit].fee[it];
        }
    }
    result[id] = tree[id].fee[tree[id].tier];
}

void dfs_root(Tree &tree, int id, vector<int> &result) {
    vector<int> &downline = tree[id].downline;
    for(int recruit: downline) {
        dfs(tree, recruit, result);
        for(int it = 0; it <= tree[id].tier; ++it) {
            tree[id].fee[it] += tree[recruit].fee[it];
        }
    }
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    unordered_map<string, int> um;
    int id_it = 0;
    for(string &name: enroll) {um.insert({name, id_it++});}
    um.insert({"-", id_it++});
    Tree tree{id_it};
    tree[um["-"]].set_tier(0);
    for(int it = 0; it < referral.size(); ++it) {
        tree[um[referral[it]]].downline.push_back(um[enroll[it]]);
        tree[um[enroll[it]]].set_tier(tree[um[referral[it]]].tier + 1);
    }
    const int toothbrush_value = 100;
    for(int it = 0; it < seller.size(); ++it) {tree[um[seller[it]]].add_profit(amount[it] * toothbrush_value);}
    vector<int> answer = vector<int>(enroll.size(), 0);
    dfs_root(tree, um["-"], answer);
    return answer;
}