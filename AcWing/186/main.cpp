#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 60;

struct PII
{
    int cnt, a, d;
    bool operator<(const PII &b) const
    {
        return cnt > b.cnt;
    }
};

int n;
int bus[N];
vector<PII> route;

bool check(int, int);
bool dfs(int, int ,int ,int);

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int tmp;
        scanf("%d", &tmp);
        ++bus[tmp];
    }

    for (int i = 0; i < 60; ++i)
        for (int j = i + 1; i + j < 60; ++j)
            if (check(i, j)) route.push_back({(59 - i) / j + 1, i, j});

    sort(route.begin(), route.end());

    int dep = 0;
    while (!dfs(dep, 0, 0, 0)) ++dep;

    printf("%d\n", dep);
    return 0;
}
bool check(int a, int d)
{
    for (int tmp = a; tmp < 60; tmp += d)
        if (!bus[tmp]) return 0;
    return 1;
}
bool dfs(int lim, int dep, int sum, int st)
{
    if (dep == lim) return sum == n;
    if (route[st].cnt * (lim - dep) + sum < n) return 0;

    for (int i = st; i < route.size(); ++i) {
        PII r = route[i];
        if (!check(r.a, r.d)) continue;
        for (int i = r.a; i < 60; i += r.d) --bus[i];
        if (dfs(lim, dep + 1, sum + r.cnt, i)) return 1;
        for (int i = r.a; i < 60; i += r.d) ++bus[i];
    }

    return 0;
}
