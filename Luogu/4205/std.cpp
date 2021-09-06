#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int N = 32000;

int m = 55 + 12;
char blk[12][4][5] = {
    {
        "**",
        "* ",
    },
    {
        "****",
        "    ",
        "    ",
        "    ",
    },
    {
        "***",
        "*  ",
        "   ",
    },
    {
        "**",
        "**",
    },
    {
        "*  ",
        "*  ",
        "***",
    },
    {
        "****",
        " *  ",
        "    ",
        "    ",
    },
    {
        "***",
        "* *",
        "   ",
    },
    {
        "***",
        "** ",
        "   ",
    },
    {
        "*** ",
        "  **",
        "    ",
        "    ",
    },
    {
        " * ",
        "***",
        " * ",
    },
    {
        "*  ",
        "** ",
        " **",
    },
    {
        "****",
        "*   ",
        "    ",
        "    "
    }
};
int u[N], d[N], l[N], r[N], s[N], row[N], col[N], idx;
int ans[N], top;
int id[10][10];
vector<vector<vector<int>>> sol;
char chr[N];
set<vector<vector<int>>> S;
char g[20][20];

void init()
{
    for (int i = 0; i <= m; i ++ )
    {
        l[i] = i - 1, r[i] = i + 1;
        u[i] = d[i] = i;
    }
    l[0] = m, r[m] = 0;
    idx = m + 1;
}

void rev1(char str[4][5])  // 水平翻转
{
    int len = strlen(str[0]);
    for (int i = 0, j = len - 1; i < j; i ++, j -- )
        for (int k = 0; k < len; k ++ )
            swap(str[i][k], str[j][k]);
}

void rev2(char str[4][5])  // 沿对角线翻转
{
    int len = strlen(str[0]);
    for (int i = 0; i < len; i ++ )
        for (int j = 0; j < i; j ++ )
            swap(str[i][j], str[j][i]);
}

vector<vector<int>> get(char str[4][5], int a, int b)
{
    vector<vector<int>> res;
    for (int i = 0; i < 4; i ++ )
        for (int j = 0; j < 4; j ++ )
            if (str[i][j] == '*')
                res.push_back({i + a, j + b});
    return res;
}

bool check(char str[4][5], int c, int a, int b)
{
    auto A = get(str, a, b);
    vector<vector<int>> B;
    for (int i = 0; i < 10; i ++ )
        for (int j = 0; j <= i; j ++ )
            if (g[i][j] == c + 'A')
                B.push_back({i, j});
    if (B.size())
    {
        sort(A.begin(), A.end()), sort(B.begin(), B.end());
        return A == B;
    }

    for (auto& p: A)
    {
        int x = p[0], y = p[1];
        if (x < 0 || x >= 10 || y < 0 || y >= 10)
            return false;
        if (g[x][y] != '.') return false;
    }
    return true;
}

void add(int& hh, int& tt, int x, int y)
{
    row[idx] = x, col[idx] = y, s[y] ++ ;
    u[idx] = y, d[idx] = d[y];
    u[d[idx]] = idx, d[u[idx]] = idx;
    r[idx] = tt, l[idx] = hh;
    l[r[idx]] = idx; r[l[idx]] = idx;
    tt = idx ++ ;
}

void remove(int p)
{
    r[l[p]] = r[p], l[r[p]] = l[p];
    for (int i = d[p]; i != p; i = d[i])
        for (int j = r[i]; j != i; j = r[j])
        {
            s[col[j]] -- ;
            u[d[j]] = u[j], d[u[j]] = d[j];
        }
}

void resume(int p)
{
    for (int i = u[p]; i != p; i = u[i])
        for (int j = l[i]; j != i; j = l[j])
        {
            u[d[j]] = j, d[u[j]] = j;
            s[col[j]] ++ ;
        }
    r[l[p]] = p, l[r[p]] = p;
}

bool dfs()
{
    if (!r[0]) return true;
    int p = r[0];
    for (int i = r[0]; i; i = r[i])
        if (s[i] < s[p])
            p = i;
    remove(p);
    for (int i = d[p]; i != p; i = d[i])
    {
        ans[ ++ top] = row[i];
        for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
        if (dfs()) return true;
        for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
        top -- ;
    }
    resume(p);
    return false;
}

int main()
{
    for (int i = 0, k = 1; i < 10; i ++ )
        for (int j = 0; j <= i; j ++, k ++ )
            id[i][j] = k;

    for (int i = 0; i < 10; i ++ ) scanf("%s", g[i]);
    init();

    for (int i = 0; i < 12; i ++ )
        for (int u = 0; u < 2; u ++ )  // 翻转
        {
            for (int j = 0; j < 4; j ++ )  // 旋转
            {
                for (int a = -10; a < 10; a ++ )  // 平移
                    for (int b = -10; b < 10; b ++ )
                    {
                        if (check(blk[i], i, a, b))
                        {
                            auto t = get(blk[i], a, b);
                            if (S.count(t)) continue;
                            int hh = idx, tt = idx;
                            for (auto& p: t)
                            {
                                int x = p[0], y = p[1];
                                add(hh, tt, sol.size(), id[x][y]);
                            }
                            add(hh, tt, sol.size(), 56 + i);
                            chr[sol.size()] = 'A' + i;
                            sol.push_back(t);
                            S.insert(t);
                        }
                    }
                rev1(blk[i]);
                rev2(blk[i]);
            }
            rev1(blk[i]);
        }

    if (dfs())
    {
        for (int i = 1; i <= top; i ++ )
        {
            auto& points = sol[ans[i]];
            char z = chr[ans[i]];
            for (auto& p: points)
            {
                int x = p[0], y = p[1];
                g[x][y] = z;
            }
        }
        for (int i = 0; i < 10; i ++ ) puts(g[i]);
    }
    else puts("No solution");

    return 0;
}