//
// build with g++ -O3 -std=c++20
// takes 9 millis for AOC2023, problem 5, part 2
//
#include <bits/stdc++.h>
using namespace std;

using u64=uint64_t;
vector<u64> seeds;
using SEGMENT=pair<u64, u64>;

struct Mapping {
    u64 source_low {0};
    u64 source_high {0};
    u64 target_low {0};    
};

auto cmp = [] (const Mapping& m1, const Mapping& m2)  {
    if (m1.source_low < m2.source_low) return true;
    return false;
};

using myset=set<Mapping, decltype(cmp)>;
myset S2S, S2F, F2W, W2L, L2T, T2H, H2L;

ostream& operator<<(ostream& o, const vector<u64>& v) {
    for(auto elm :v ) {
        o << elm << " ";
    }
    return o;
}

ostream& operator<<(ostream& o, const vector<SEGMENT>& v) {
    for(auto elm :v ) {
        o << "[" << elm.first << "," << elm.second << ") ";
    }
    return o;
}

ostream& operator<<(ostream& o, const myset& m) {
    for(auto elm :m ) {
        o << "[" << elm.source_low << "," << elm.source_high << ")=>" <<  elm.target_low << "  ";
    }
    return o;
}

void process_map(ifstream& ifs, myset& M) {
    string line;
    while (getline(ifs, line)) {
        if (line == "") break;
        vector<u64> v;
        istringstream iss(line);
        string tmp;
        while(getline(iss, tmp, ' ')) {
            v.push_back(stol(tmp));
        }
        if (true) if (false) cout <<  "Mapping: " <<  v[1] << " " << v[1] + v[2] << " " << v[0] << endl;
        Mapping m {v[1], v[1]+v[2], v[0]};
        M.insert(m);
    }
    vector<Mapping> tmp;
    auto iter = M.begin();
    ++iter;
    for(;iter != M.end(); ++ iter ) {
        auto iter2 {iter};
        --iter2;
        auto& prev = *iter2;
        tmp.push_back(Mapping {prev.source_high, iter->source_low, prev.source_high});
    }
    iter = M.end();
    --iter;
    tmp.push_back(Mapping{(*iter).source_high, 0xFFFFFFFFFFFFFFFF, (*iter).source_high});
    if (M.begin()->source_low) {
        tmp.push_back(Mapping{0, M.begin()->source_low, 0});
    }
    for(auto& t : tmp) M.insert(t);
}

u64 get(u64 x, const myset& v) {
    auto iter = v.lower_bound(Mapping{x,0,0});
    if (iter != v.begin()) --iter;
    for(;iter != v.end(); ++iter) {
        auto& m = *iter;
        if (x >= m.source_low and x < m.source_high) {
            return m.target_low + x - m.source_low;
        }
    }
    return x;
}

void process_s2s(ifstream& ifs) {  process_map(ifs, S2S); }
void process_s2f(ifstream& ifs) {  process_map(ifs, S2F); }
void process_f2w(ifstream& ifs) {  process_map(ifs, F2W); }
void process_w2l(ifstream& ifs) {  process_map(ifs, W2L); }
void process_l2t(ifstream& ifs) {  process_map(ifs, L2T); }
void process_t2h(ifstream& ifs) {  process_map(ifs, T2H); }
void process_h2l(ifstream& ifs) {  process_map(ifs, H2L); }

void overlap(SEGMENT int1, SEGMENT int2, vector<SEGMENT>& v ) {
    if (int1.second <= int2.first) return;
    if (int2.second <= int1.first) return;
    if (int2.first >= int1.first) {
        if (int1.second >= int2.second) {
            v.push_back(int2);
        } else {
            v.push_back({int2.first, int1.second});
        }
    } else { overlap(int2, int1, v); }
}

vector<SEGMENT> project(vector<SEGMENT>& intervals, myset& M) {
    vector<SEGMENT> v;
    for (auto& interval : intervals) {
        auto low = get(interval.first, M);
        auto high = get(interval.second-1, M) + 1;
        v. push_back({low, high});
    }
    return v;
}

vector<SEGMENT> overlap(vector<SEGMENT>& intervals, myset& M) {
    vector<SEGMENT> v;
    for (auto& interval : intervals) {
        for (auto& mapping : M) {
            SEGMENT mapping_interval{mapping.source_low, mapping.source_high};
            overlap(interval, mapping_interval, v);
        }
    }
    return project(v, M);
}

int main(int argc, char** argv) {
    string f {argv[1]};
    ifstream ifs{f};
    string line;
    while(getline(ifs, line)) {
        if (line == "") continue;
        if (line.starts_with("seeds:")) {
            istringstream iss(line);
            string tmp;
            getline(iss, tmp, ' ');
            while(getline(iss, tmp, ' ')) {
                seeds.push_back(stol(tmp));
            }
        }

        if (line.starts_with("seed-to-soil"))        { process_s2s(ifs); }
        if (line.starts_with("soil-to-fertilizer"))  { process_s2f(ifs); }
        if (line.starts_with("fertilizer-to-water")) { process_f2w(ifs); }
        if (line.starts_with("water"))               { process_w2l(ifs); }
        if (line.starts_with("light"))               { process_l2t(ifs); }
        if (line.starts_with("temperature"))         { process_t2h(ifs); }
        if (line.starts_with("humidity"))            { process_h2l(ifs); }
    }

    vector<SEGMENT> seed_intervals;
    for(int i=0;i<seeds.size()/2;++i) {
        u64 low = seeds[i*2];
        u64 high = low + seeds[i*2+1];
        seed_intervals.push_back({low,high});
    }

    vector<SEGMENT> tmp = overlap(seed_intervals, S2S);
    tmp = overlap(tmp, S2F);
    tmp = overlap(tmp, F2W);
    tmp = overlap(tmp, W2L);
    tmp = overlap(tmp, L2T);
    tmp = overlap(tmp, T2H);    
    tmp = overlap(tmp, H2L);

    u64 minloc = 0xFFFFFFFFFFFFFFFF;
    for(auto interval : tmp) {
        minloc = min(minloc, interval.first);
    }
    cout <<  "minloc: " << minloc << endl;
    return 0;
}
