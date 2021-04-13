#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 61;

int n, m;
bool st[N];
vector<int> square[N];

bool check(vector<int> &sq)
{
    for (auto x : sq)
        if (st[x])
            return false;
    return true;
}

int f()
{
    static bool state[N];
    memcpy(state, st, sizeof st);

    int res = 0;
    for (int i = 0; i < m; i ++ )
    {
        auto &sq = square[i];
        if (check(sq))
        {
            res ++ ;
            for (auto x : sq) st[x] = true;
        }
    }

    memcpy(st, state, sizeof st);

    return res;
}

bool dfs(int depth)
{
    if (f() > depth) return false;

    for (int i = 0; i < m; i ++ )
    {
        auto &sq = square[i];
        if (check(sq))
        {
            for (auto x : sq)
            {
                st[x] = true;
                if (dfs(depth - 1)) return true;
                st[x] = false;
            }
            return false;
        }
    }

    return true;
}

main()
{
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        scanf("%d", &n);

        m = 0;
        for (int i = 1; i <= n; i ++ )
            for (int a = 1; a + i - 1 <= n; a ++ )
                for (int b = 1; b + i - 1 <= n; b ++ )
                {
                    square[m].clear();
                    for (int j = 0; j < i; j ++ )
                    {
                        int d = 2 * n + 1;
                        square[m].push_back((a - 1) * d + b + j);
                        square[m].push_back((a - 1 + i) * d + b + j);
                        square[m].push_back(n + 1 + (a - 1) * d + b - 1 + j * d);
                        square[m].push_back(n + 1 + (a - 1) * d + b - 1 + j * d + i);
                    }
                    m ++ ;
                }
		cout << endl;
		cout << m << endl;

        memset(st, 0, sizeof st);
        int k;
        scanf("%d", &k);
        for (int i = 0, t; i < k; i ++ )
        {
            scanf("%d", &t);
            st[t] = true;
        }

        int depth = 0;
        while (!dfs(depth)) depth ++ ;

        printf("%d\n", depth);
    }

    return 0;
}
