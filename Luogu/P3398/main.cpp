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
const int N = 1e5 + 10, LG = 20;

int n, m;
std::vector<int> G[N];
int dep[N], fa[N][LG];

void initLCA(int u)
{
	dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : G[u])
		if (v != fa[u][0]) {
			fa[v][0] = u;
			initLCA(v);
		}
}
std::pair<int, int> LCA(int u, int v)
{
	int res = dep[u] + dep[v];
	if (dep[u] < dep[v])
		std::swap(u, v);
	for (int k = LG - 1; k >= 0; --k)
		if (dep[fa[u][k]] >= dep[v])
			u = fa[u][k];
	if (u == v)
		return std::make_pair(u, res - 2 * dep[u]);
	for (int k = LG - 1; k >= 0; --k)
		if (fa[u][k] != fa[v][k]) {
			u = fa[u][k];
			v = fa[v][k];
		}
	return std::make_pair(fa[u][0], res - 2 * dep[fa[u][0]]);
}

int main(void)
{
	read >> n >> m;
	for (int i = 1, u, v; i < n; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	initLCA(1);
	while (m--) {
		int a, b, c, d;
		read >> a >> b >> c >> d;
		auto lca1 = LCA(a, b), lca2 = LCA(c, d);
		bool flag1 = LCA(lca2.first, a).second + LCA(lca2.first, b).second == lca1.second;
		bool flag2 = LCA(lca1.first, c).second + LCA(lca1.first, d).second == lca2.second;
		puts(flag1 || flag2 ? "Y" : "N");
	}
	return 0;
}
