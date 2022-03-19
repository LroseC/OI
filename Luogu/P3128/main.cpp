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

const int N = 5e4 + 10, LG = 20;

int n, m, ans;
std::vector<int> G[N];
int dep[N], w[N], fa[N][LG];

void getFa(int u)
{
	dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : G[u])
		if (v != fa[u][0]) {
			fa[v][0] = u;
			getFa(v);
		}
}
int LCA(int u, int v)
{
	if (dep[u] < dep[v])
		std::swap(u, v);
	for (int i = LG - 1; i >= 0; --i)
		if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if (u == v) return u;
	for (int i = LG - 1; i >= 0; --i)
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}
void calc(int u)
{
	for (int v : G[u])
		if (v != fa[u][0]) {
			calc(v);
			w[u] += w[v];
		}
	ans = std::max(ans, w[u]);
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	getFa(1);
	for (int i = 1; i <= m; ++i) {
		int u, v; read >> u >> v;
		++w[u], ++w[v];
		int d = LCA(u, v);
		--w[d];
		--w[fa[d][0]];
	}
	calc(1);
	printf("%d\n", ans);
	return 0;
}
