#include <cstdio>

using namespace std;

int n;
int pr[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int sum, minx;

void dfs(int dep, int last, int num, int ans)
{
    if (dep > 10) return;
    if (ans > sum || (ans == sum && num < minx))
    {
        sum = ans;
        minx = num;
    }

    for (int i = 1; i <= last; ++i) {
        if (1ll * num * pr[dep] > n) break;
        num *= pr[dep];
        dfs(dep + 1, i, num, ans * (i + 1));
    }
}

int main()
{
    scanf("%d", &n);
    dfs(0, 30, 1, 1);

    printf("%d\n", minx);

    return 0;
}
