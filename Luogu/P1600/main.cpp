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

const int N = 3e5 + 10, LG = 20;

int n, m;
std::vector<int> G[N];
std::vector<int> downlineDec[N], downlineAdd[N];
std::vector<int> upLineDec[N], upLineAdd[N];
int downLineCnt[N << 1], upLineCnt[N << 1];
int ans[N], w[N];
int fa[N][LG], dep[N];

void calc(int u)
{
	int res1 = upLineCnt[w[u] + dep[u]];
	int res2 = downLineCnt[w[u] - dep[u] + N];
	for (int v : G[u])
		if (v != fa[u][0]) calc(v);
	for (auto t : upLineAdd[u])
		++upLineCnt[t];
	for (auto t : upLineDec[u])
		--upLineCnt[t];
	ans[u] += upLineCnt[w[u] + dep[u]] - res1;
	for (auto t : downlineAdd[u])
		++downLineCnt[t + N];
	for (auto t : downlineDec[u])
		--downLineCnt[t + N];
	ans[u] += downLineCnt[w[u] - dep[u] + N] - res2;
}
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

int main(void)
{
	read >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		read >> w[i];
	getFa(1);
	for (int i = 1; i <= m; ++i) {
		int u, v; read >> u >> v;
		int d = LCA(u, v);
		upLineAdd[u].emplace_back(dep[u]);
		upLineDec[d].emplace_back(dep[u]);
		downlineAdd[v].emplace_back(dep[u] - dep[d] * 2);
		downlineDec[fa[d][0]].emplace_back(dep[u] - dep[d] * 2);
	}
	calc(1);
	for (int i = 1; i <= n; ++i)
		printf("%d ", ans[i]);
	puts("");
	return 0;
}
