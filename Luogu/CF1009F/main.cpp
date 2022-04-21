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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 1e6 + 10;

int n;
int *f[N];
int g[N];
int *now = g;
int maxDep[N], son[N], ans[N];
std::vector<int> G[N];

void initCut(int u, int fa)
{
	for (int v : G[u])
		if (v != fa) {
			initCut(v, u);
			if (maxDep[v] > maxDep[son[u]])
				son[u] = v;
		}
	maxDep[u] = maxDep[son[u]] + 1;
}
void dfs(int u, int fa)
{
	f[u] = ++now;
	f[u][0] = 1;
	if (son[u]) {
		dfs(son[u], u);
		ans[u] = ans[son[u]] + 1;
	}
	for (int v : G[u])
		if (v != fa && v != son[u]) {
			dfs(v, u);
			for (int i = 0; i < maxDep[v]; ++i) {
				f[u][i + 1] += f[v][i];
				if (f[u][i + 1] > f[u][ans[u]])
					ans[u] = i + 1;
				if (f[u][i + 1] ==  f[u][ans[u]] && i + 1 < ans[u])
					ans[u] = i + 1;
			}
		}
	if (f[u][0] >= f[u][ans[u]])
		ans[u] = 0;
}

int main(void)
{
	read >> n;
	for (int i = 1, u, v; i < n; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	initCut(1, 1);
	dfs(1, 1);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
