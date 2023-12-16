#include <bits/stdc++.h>
using namespace std;

using Point = pair<int, int>;
enum Direction
{
    North = 0x1000,
    East = 0x0100,
    West = 0x0010,
    South = 0x0000

};
using State = pair<Point, Direction>; 
set<State> visited;

void account(queue<State> &q, State state, const vector<string> &v)
{
    auto nextrow = state.first.first;
    if (nextrow < 0)
        return;
    if (nextrow >= v.size())
        return;

    auto nextcol = state.first.second;
    if (nextcol < 0)
        return;
    if (nextcol >= v[0].size())
        return;

    auto nextdir = state.second;
    if (visited.find({{nextrow, nextcol}, nextdir}) == visited.end())
    {
        visited.insert({{nextrow, nextcol}, nextdir});
        q.push({{nextrow, nextcol}, nextdir});
    }
}

int process(const vector<string> &v, State start)
{
    visited.clear();
    queue<State> q;
    q.push({start});
    visited.insert({{0, 0}, East});
    while (not q.empty())
    {
        auto curr = q.front();
        q.pop();
        // do step
        auto row = curr.first.first;
        auto col = curr.first.second;
        auto dir = curr.second;
        auto nextrow = row;
        auto nextcol = col;
        auto nextdir = dir;
        switch (v[row][col])
        {
        case '.':
            switch (dir)
            {
            case North:
                nextrow = row - 1;
                break;
            case East:
                nextcol = col + 1;
                break;
            case West:
                nextcol = col - 1;
                break;
            case South:
                nextrow = row + 1;
                break;
            }
            account(q, {{nextrow, nextcol}, nextdir}, v);
            break;
        case '-':
            switch (dir)
            {
            case North:
            case South:
                nextcol = col - 1;
                nextdir = West;
                account(q, {{nextrow, nextcol}, nextdir}, v);
                nextcol = col + 1;
                nextdir = East;
                break;
            case East:
                nextcol = col + 1;
                break;
            case West:
                nextcol = col - 1;
                break;
            }
            account(q, {{nextrow, nextcol}, nextdir}, v);
            break;
        case '|':
            switch (dir)
            {
            case North:
                nextrow = row - 1;
                break;
            case East:
            case West:
                nextrow = row - 1;
                nextdir = North;
                account(q, {{nextrow, nextcol}, nextdir}, v);

                nextrow = row + 1;
                nextdir = South;
                break;
            case South:
                nextrow = row + 1;
                break;
            }
            account(q, {{nextrow, nextcol}, nextdir}, v);
            break;
        case '\\':
            switch (dir)
            {
            case North:
                nextcol = col - 1;
                nextdir = West;
                break;
            case East:
                nextrow = row + 1;
                nextdir = South;
                break;
            case West:
                nextrow = row - 1;
                nextdir = North;
                break;
            case South:
                nextcol = col + 1;
                nextdir = East;
                break;
            }
            account(q, {{nextrow, nextcol}, nextdir}, v);
            break;
        case '/':
            switch (dir)
            {
            case North:
                nextcol = col + 1;
                nextdir = East;
                break;
            case East:
                nextrow = row - 1;
                nextdir = North;
                break;
            case West:
                nextrow = row + 1;
                nextdir = South;
                break;
            case South:
                nextcol = col - 1;
                nextdir = West;
                break;
            }
            account(q, {{nextrow, nextcol}, nextdir}, v);
            break;
        }
    }
    set<Point> S;
    for (auto elm : visited)
    {
        S.insert({elm.first.first, elm.first.second});
    }
    return S.size();
}

int main(int argc, char **argv)
{
    string name{"input.txt"};
    if (argc > 1)
        name = argv[1];
    string tmp{""};
    ifstream ifs{name};
    long row{0};
    vector<string> v;
    while (ifs >> tmp)
    {
        v.push_back(tmp);
        cout << tmp << endl;
    }
    int maxrc = 0;
    // row = 0
    for (int col = 0; col < v[0].size(); ++col)
    {
        int rc = process(v, {{0, col}, South});
        maxrc = max(maxrc, rc);
    }

    // row = v.size() -1
    for (int col = 0; col < v[0].size(); ++col)
    {
        int rc = process(v, {{v.size() - 1, col}, North});
        maxrc = max(maxrc, rc);
    }

    // col ==0
    for (int row = 0; row < v.size(); ++row)
    {
        int rc = process(v, {{row, 0}, East});
        maxrc = max(maxrc, rc);
    }

    // col = v[0].size() -1
    for (int row = 0; row < v.size(); ++row)
    {
        int rc = process(v, {{row, v[0].size() - 1}, West});
        maxrc = max(maxrc, rc);
    }

    cout << "Answer: " << maxrc << endl;
}
