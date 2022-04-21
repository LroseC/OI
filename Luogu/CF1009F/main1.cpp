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

int n, res;
int ans[N], dep[N];
int sz[N], son[N], cnt[N];
std::vector<int> G[N];

void init(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	for (int v : G[u])
		if (v != fa) {
			init(v, u);
			if (sz[v] > sz[son[u]])
				son[u] = v;
		}
}
void getCnt(int u, int fa, int sign)
{
	cnt[dep[u]] += sign;
	if (cnt[dep[u]] > cnt[res])
		res = dep[u];
	if (cnt[dep[u]] == cnt[res] && dep[u] < res)
		res = dep[u];
	for (int v : G[u])
		if (v != fa) getCnt(v, u, sign);
}
void dfs(int u, int fa)
{
	for (int v : G[u])
		if (v != fa && v != son[u]) {
			dfs(v, u);
			res = 0;
			getCnt(v, u, -1);
		}
	if (son[u])
		dfs(son[u], u);
	for (int v : G[u])
		if (v != fa && v != son[u])
			getCnt(v, u, 1);
	++cnt[dep[u]];
	if (cnt[dep[u]] >= cnt[res])
		res = dep[u];
	ans[u] = res;
}

int main(void)
{
	read >> n;
	for (int i = 1, u, v; i < n; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	init(1, 0);
	dfs(1, 0);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", ans[i] - dep[i]);
	return 0;
}
