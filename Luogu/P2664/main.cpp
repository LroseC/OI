#include <vector>
#include <cctype>
#include <cstdio>

struct FSI
{
    template<typename T>
    FSI& operator>>(T &res)
    {
        res = 0; T f = 1; char ch = getchar();
        while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
        while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
        res = res * f; return *this;
    }
} read;

using i64 = long long;
const int N = 1e5 + 10;

int n;
int c[N], sz[N];
std::vector<int> G[N];
bool appear[N], del[N];
i64 color[N], colorSum;
i64 ans[N];

void getRoot(int u, int fa, int &root, int &minSize, int allNode)
{
    sz[u] = 1;
    int maxTree = 0;
    for (int v : G[u])
        if (!del[v] && v != fa) {
            getRoot(v, u, root, minSize, allNode);
            maxTree = std::max(maxTree, sz[v]);
            sz[u] += sz[v];
        }
    maxTree = std::max(maxTree, allNode - sz[u]);
    if (maxTree < minSize) {
        root = u;
        minSize = maxTree;
    }
}
void getSz(int u, int fa, int f)
{
    sz[u] = 1;
    bool flag = 0;
    if (!appear[c[u]]) {
        flag = 1;
        appear[c[u]] = 1;
    }
    for (int v : G[u])
        if (!del[v] && v != fa) {
            getSz(v, u, f);
            sz[u] += sz[v];
        }
    if (flag) {
        color[c[u]] += sz[u] * f;
        colorSum += sz[u] * f;
        appear[c[u]] = 0;
    }
}
void getAns(int u, int fa, int cnt, int Size)
{
    bool flag = 0;
    if (!appear[c[u]]) {
        ++cnt;
        appear[c[u]] = 1;
        colorSum -= color[c[u]];
        flag = 1;
    }
    for (int v : G[u])
        if (!del[v] && v != fa)
            getAns(v, u, cnt, Size);
    ans[u] += colorSum + cnt * Size;
    if (flag) {
        appear[c[u]] = 0;
        colorSum += color[c[u]];
    }
}
void calc(int u)
{
	getSz(u, u, 1);
	appear[c[u]] = 1;
    for (int v : G[u])
        if (!del[v]) {
            getSz(v, u, -1);
			colorSum -= sz[v];
			color[c[u]] -= sz[v];
            getAns(v, u, 0, sz[u] - sz[v]);
			color[c[u]] += sz[v];
			colorSum += sz[v];
            getSz(v, u, 1);
        }
    ans[u] += colorSum - color[c[u]] + sz[u];
	appear[c[u]] = 0;
	getSz(u, u, -1);
}
void dfs(int u)
{
    del[u] = 1;
    calc(u);
    for (int v : G[u])
        if (!del[v]) {
            int root, minSize = 0x3f3f3f3f;
            getRoot(v, u, root, minSize, sz[v]);
			dfs(root);
        }
}

int main(void)
{
    read >> n;
    for (int i = 1; i <= n; ++i)
        read >> c[i];
    for (int i = 1; i < n; ++i) {
        int u, v; read >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    int root = 0, minSize = 0x3f3f3f3f;
    getRoot(1, 0, root, minSize, n);
    dfs(root);
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}
