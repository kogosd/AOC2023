/*
real    0m0.830s
user    0m0.827s
sys     0m0.003s
*/

#include <bits/stdc++.h>
using namespace std;

string instr;
unordered_map<string, pair<string,string>> M;

string transition(const string& curr, int count) {
        char c = instr[count%instr.size()];
        return c=='L'? M[curr].first : M[curr].second;
}

int main(int argc, char** argv) {
    ifstream ifs(argv[1]);
    string tmp;
    ifs>>instr;
    while(ifs>>tmp) {
        auto src =  tmp;
        ifs >> tmp; assert(tmp == "=");
        ifs >> tmp; tmp = tmp.substr(1,3);
        auto d1 = tmp;
        ifs >> tmp; tmp = tmp.substr(0,3);
        auto d2 = tmp;
        M[src] = {d1,d2};
    }
    vector<string> anodes, znodes;
    for(auto elm : M) {
        if (elm.first[2]      == 'A') { anodes.push_back(elm.first); }
        else if (elm.first[2] == 'Z') { znodes.push_back(elm.first); }
    }
    vector<int> v;
    for (auto anode : anodes ) {
        for (auto znode : znodes) {
            int count = 0;
            auto tmp = anode;
            while (tmp != znode and count < 100'000) {tmp = transition(tmp, count++);}
            if (count < 100'000) { v.push_back(count); }
        }        
    }

    uint64_t result = 1;
    for(auto elm : v) { result = lcm(result, elm);  }
    cout << "Result: " << result << endl;
    return 0;

}
