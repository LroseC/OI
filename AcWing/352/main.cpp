#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

struct FSIO
{
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} io;

const int N = 1e5 + 10, M = 20;

int ans;
int n, m;
int cnt[N];
int dep[N];
int fa[N][M];
vector<int> G[N];

void GetFa(int u, int fath, int depth)
{
	dep[u] = depth;
	for (int k = 1; k < M; ++k)
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
	for (int v : G[u]) {
		if (v == fath) continue;
		fa[v][0] = u;
		GetFa(v, u, depth + 1);
	}
}
int LCA(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	for (int k = M - 1; k >= 0; --k) {
		if (fa[u][k] && dep[fa[u][k]] >= dep[v])
			u = fa[u][k];
	}
	for (int k = M - 1; k >= 0; --k)
		if (fa[u][k] && fa[u][k] != fa[v][k]) {
			u = fa[u][k];
			v = fa[v][k];
		}
	return u == v ? u : fa[u][0];
}
void dfs(int u, int fa)
{
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
		cnt[u] += cnt[v];
	}
}

int main(void)
{
	io >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v; io >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	GetFa(1, 0, 1);
	for (int i = 1; i <= m; ++i) {
		int u, v; io >> u >> v;
		++cnt[u]; ++cnt[v];
		cnt[LCA(u, v)] -= 2;
	}
	dfs(1, -1);
	for (int u = 2; u <= n; ++u) {
		if (cnt[u] == 0) ans += m;
		if (cnt[u] == 1) ans += 1;
	}
	printf("%d\n", ans);
	return 0;
}