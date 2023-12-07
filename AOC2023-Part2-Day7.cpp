#include <bits/stdc++.h>
using namespace std;

int get_rank_noj(std::string s) {
    int M[128] = {0};
    for(auto c : s) {if (c!='J') M[c]++;}

    int M2[6] = {0};
    for(int i='2';i<='T';++i) { M2[M[i]] ++; }

    if (M2[5] > 0) return 6;
    if (M2[4] > 0) return 5;
    if (M2[3] > 0 and M2[2]>0) return 4;
    if (M2[3]>0) return 3;
    if (M2[2]>1) return 2;
    if (M2[2]>0) return 1;
    return 0;
}

int countj(std::string& s) {
    int count = 0;
    for(int i=0;i<s.size();++i) {if (s[i]=='J') ++count;}
    return count;
}

int get_rank(std::string s) {
    auto tmprank = get_rank_noj(s);
    switch(countj(s)) {
        case 5:
        case 4:
            return 6;
        case 3:
            return tmprank==1?6:5;
        case 2:
            if (tmprank == 3) return 6;
            if (tmprank == 1) return 5;
            return 3;
        case 1:
            if (tmprank==5) return 6;
            if (tmprank==3) return 5;
            if (tmprank==2) return 4;
            if (tmprank==1) return 3;
            return 1;
        case 0:
            return tmprank;
    }
    return 0;
}

int get_value(char c) {
    static unordered_map<char,int> values = {
        {'A',14},
        {'K',13},        
        {'Q',12},
        {'T',10},
        {'9',9},
        {'8',8},
        {'7',7},
        {'6',6},
        {'5',5},
        {'4',4},                                                                       
        {'3',3},
        {'2',2},
        {'J',0}        
    };
    return values[c];
}

struct Compare {
    bool operator() (const pair<string,int>& h1, const pair<string,int>& h2 ) const {
        auto& s1 = h1.first;
        auto& s2 = h2.first;
        if (get_rank(s1) < get_rank(s2)) return true;
        if (get_rank(s1) > get_rank(s2)) return false;
        for(int i=0;i<s1.size();++i) {
            if (get_value(s1[i]) < get_value(s2[i])) return true;
            if (get_value(s1[i]) > get_value(s2[i])) return false;            
        }        
        return true;
    }
};

int main(int argc, char** argv)
{
    string f {argv[1]};
    ifstream ifs {f};
    string tmp;
    vector<pair<string,int>> hands;
    while (ifs>>tmp) {
        string tmp1;        
        ifs>>tmp1;
        hands.push_back({tmp, stoi(tmp1)});
    }
    sort(hands.begin(), hands.end(), Compare());
    auto total = 0L;
    for(int i=0;i<hands.size();++i) { total += (i+1) * hands[i].second; }
    cout << "Total: " << total << endl;

}
