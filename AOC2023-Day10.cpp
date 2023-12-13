#include <bits/stdc++.h>
using namespace std;

using ROW = vector<char>;
using FIELD = vector<ROW>;
using VALUE = vector<vector<int>>;
using POINT = pair<int, int>;

set<POINT> path;
FIELD field;
VALUE value;
queue<POINT> Q;
int rowcount = 0;
int colcount = 0;
// ANSI color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

ostream &operator<<(ostream &o, const VALUE &v)
{
    for (auto &row : v)
    {
        for (auto &elm : row) { o << setw(3) << elm << " "; }
        o << endl;
    }
    return o;
}

ostream &operator<<(ostream &o, const FIELD &v)
{
    for (int i = 0; i < rowcount; ++i)
    {
        auto &row = v[i];
        for (int j = 0; j < colcount; ++j)
        {
            auto elm = row[j];
            string str;
            switch (elm)
            {
            case 'F':
                str.assign("\u250c");
                break;
            case '7':
                str.assign("\u2510");
                break;
            case 'L':
                str.assign("\u2514");
                break;
            case 'J':
                str.assign("\u2518");
                break;
            default:
                str += elm;
                break;
            }
            o << setw(1);
            if (path.find({i, j}) != path.end())
            {
                o << RED;
            }
            o << str;
            o << RESET;
        }
        o << endl;
    }
    return o;
}

bool valid(int xx, int yy)
{
    if (xx < 0)
        return false;
    if (xx >= rowcount)
        return false;
    if (yy < 0)
        return false;
    if (yy >= colcount)
        return false;
    return true;
}

bool connected(int xx, int yy, int x, int y)
{
    // check if connected
    auto us = field[x][y];
    auto f = field[xx][yy];

    if (xx == x + 1)
    {
        switch (us)
        {
        case 'F': case '7': case '|': case 'S':
            if (f == '|' or f == 'J' or f == 'L')
                return true;
            else  return false;
        default:  return false;
        }
    }

    if (xx == x - 1)
    {
        switch (us)
        {
        case 'L':  case 'J':  case '|':  case 'S':
            if (f == '|' or f == '7' or f == 'F')
                return true;
            else   return false;
        default:   return false;
        }
    }

    if (yy == y - 1)
    {
        switch (us)
        {
        case '7': case 'J': case '-': case 'S':
            if (f == '-' or f == 'F' or f == 'L')
                return true;
            else   return false;
        default:   return false;
        }
    }

    if (yy == y + 1)
    {
        switch (us)
        {
        case 'F':  case 'L':   case '-':   case 'S':
            if (f == '-' or f == '7' or f == 'J')
                return true;
            else    return false;
        default:    return false;
        }
    }
    return false;
}

vector<POINT> get_neighbors(int x, int y, int next_val)
{
    vector<POINT> v;
    if (valid(x, y - 1))
    {
        if (value[x][y - 1] == next_val)
            v.push_back({x, y - 1});
    }
    if (valid(x, y + 1))
    {
        if (value[x][y + 1] == next_val)
            v.push_back({x, y + 1});
    }

    if (valid(x - 1, y))
    {
        if (value[x - 1][y] == next_val)
            v.push_back({x - 1, y});
    }
    if (valid(x + 1, y))
    {
        if (value[x + 1][y] == next_val)
            v.push_back({x + 1, y});
    }
    return v;
}

bool find_path(set<POINT> &path, int x, int y, int start_val, int vmax, bool forward, int indent = 0)
{
    int next_val;
    if (start_val == vmax)
    {
        next_val = vmax - 1;
        forward = false;
    }
    else
    {
        next_val = forward ? ++start_val : --start_val;
    }
    if (next_val == 0 and forward == false)
        return true;
    vector<POINT> neighbors = std::move(get_neighbors(x, y, next_val));
    for (auto [xx, yy] : neighbors)
    {
        if (find(path.begin(), path.end(), make_pair(xx, yy)) != path.end())
            continue;

        path.insert({xx, yy});
        bool b = find_path(path, xx, yy, next_val, vmax, forward, indent + 1);
        if (b == false)  { path.erase({xx, yy}); }
        else { return true; }
    }
    return false;
}

int main(int argc, char **argv)
{
    string filename = "input.txt";
    if (argc > 1)  filename = argv[1];
    ifstream ifs(filename);
    string tmp;
    int x, y;
    int startx, starty;
    while (ifs >> tmp)
    {
        ROW row;
        vector<int> v;
        colcount = 0;
        for (auto c : tmp)
        {
            row.push_back(c);
            if (c == 'S')
            {
                v.push_back(0);
                Q.push({rowcount, colcount});
                startx = rowcount;
                starty = colcount;
            }
            else { v.push_back(-1); }
            ++colcount;
        }
        value.push_back(v);
        field.push_back(row);
        ++rowcount;
    }

    int vmax{0};
    int xmax{0};
    int ymax{0};
    while (not Q.empty())
    {
        if (false)
            cout << "In Q: " << Q.size() << endl;
        auto top = Q.front();
        Q.pop();
        auto x = top.first;
        auto y = top.second;
        vector<POINT> neighbors = {{x, y - 1}, {x, y + 1}, {x - 1, y}, {x + 1, y}};
        for (auto [xx, yy] : neighbors)
        {
            if (valid(xx, yy) == false)
                continue;
            if (value[xx][yy] > 0)
                continue;
            if (not connected(xx, yy, x, y))
                continue;

            value[xx][yy] = value[x][y] + 1;
            if (value[xx][yy] > vmax)
            {
                vmax = max(vmax, value[xx][yy]);
                xmax = xx;
                ymax = yy;
            }
            Q.push({xx, yy});
        }
    }
    cout << "vmax: " << vmax << ", x=" << xmax << ", y=" << ymax << endl;

    path.insert({startx, starty});
    find_path(path, startx, starty, 0, vmax, true, 0);
    vector<vector<char>> F(
        rowcount,
        vector<char>(colcount, '*'));
    for (auto elm : path)
    {
        F[elm.first][elm.second] = field[elm.first][elm.second];
    }
    F[startx][starty] = '|';
    cout << "Path len is: " << path.size() << endl;

    int surrcount{0};
    for (auto r = 0; r < rowcount; ++r)
    {
        bool inside{false};
        char possible{'\0'};
        for (auto c = 0; c < colcount; ++c)
        {
            auto val = F[r][c];
            if (val == '*')
            {
                if (inside)
                {
                    ++surrcount;
                    F[r][c] = '=';
                }
                continue;
            }
            if (val == '|')
            {
                inside = !inside;
                continue;
                possible = '\0';
            }

            if (val == '7')
            {
                if (possible == 'L')
                {
                    inside = !inside;
                    possible = '\0';
                    continue;
                }
                else if (possible == 'F')
                {
                    possible = '\0';
                    continue;
                }
            }

            if (val == 'F')
            {
                possible = 'F';
                continue;
            }

            if (val == 'L')
            {
                possible = 'L';
                continue;
            }

            if (val == 'J')
            {
                if (possible == 'F')
                {
                    inside = !inside;
                    possible = '\0';
                    continue;
                }
                else if (possible == 'L')
                {
                    possible = '\0';
                    continue;
                }
            }
        }
    }
    cout << F << endl;
    cout << "surrcount: " << surrcount << endl;
    return 0;
}
