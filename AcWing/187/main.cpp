#include <cstdio>

using namespace std;

const int N = 60;

int n, a[N];
int up[N], down[N];

bool dfs(int lim, int dep, int u, int d);

int main()
{
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        int dep = 0;
        while (!dfs(dep, 0, 0, 0)) ++dep;
        printf("%d\n", dep);
    }
    return 0;
}
bool dfs(int lim, int dep, int u, int d)
{
    if (u + d > lim) return 0;
    if (n == dep) return 1;

    bool flag = 1;
    for (int i = 0; i < u; ++i)
        if (up[i] < a[dep]) {
            flag = 0;
            int t = up[i];
            up[i] = a[dep];
            if (dfs(lim, dep + 1, u, d)) return 1;
            up[i] = t;
            break;
        }
    if (flag) {
        up[u] = a[dep];
        if (dfs(lim, dep + 1, u + 1, d)) return 1;
        up[u] = 0;
    }

    flag = 1;
    for (int i = 0; i < d; ++i)
        if (down[i] > a[dep]) {
            flag = 0;
            int t = down[i];
            down[i] = a[dep];
            if (dfs(lim, dep + 1, u, d)) return 1;
            down[i] = t;
            break;
        }
    if (flag) {
        down[d] = a[dep];
        if (dfs(lim, dep + 1, u, d + 1)) return 1;
        down[d] = 0;
    }
    return 0;
}
