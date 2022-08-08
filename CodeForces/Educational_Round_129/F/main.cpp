#include <vector>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 1e6 + 10, LG = 20;

i32 n;
i32 fa[N][LG];
i32 f[N], g[N], dep[N], dfn[N], idx, c[N], sz[N];
vi32 G[N], T[N], e[N];
i32 stk[N], top;
i32 edgeStk[N], edgeTop;
i64 res;

void initTree(int u)
{
	sz[u] = (c[u] == 0) ? 1 : 0;
	for (int i = 1; i < LG; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	dep[u] = dep[fa[u][0]] + 1;
	dfn[u] = ++idx;
	for (auto v : G[u])
		if (v != fa[u][0]) {
			fa[v][0] = u;
			initTree(v);
			sz[u] += sz[v];
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
i32 getSon(int u, int v)
{
	for (int i = LG - 1; i >= 0; --i)
		if (dep[fa[v][i]] > dep[u]) v = fa[v][i];
	return v;
}
void dp1(int u, int color)
{
	f[u] = 0;
	for (int v : T[u]) {
		dp1(v, color);
		if (c[v] != color) f[u] += f[v];
		else f[u] += sz[v];
	}
}
void dp2(int u, int color)
{
	for (int v : T[u]) {
		if (c[u] == color)
			g[v] = n - sz[getSon(u, v)];
		else {
			g[v] = g[u];
			if (c[v] != color) g[v] += f[u] - f[v];
			else g[v] += f[u] - sz[v];
		}
		dp2(v, color);
	}
}
void calcAns(int u, int color)
{
	for (int v : T[u]) {
		calcAns(v, color);
	}
	if (c[u] == color) {
		res += 1ll * (n - sz[u] - g[u]) * (sz[u] - f[u]);
	}
}
inline void addEdge(int u, int v)
{
	edgeStk[++edgeTop] = u;
	T[u].emplace_back(v);
}
inline void clearEdge(void)
{
	while (edgeTop) {
		T[edgeStk[edgeTop]].clear();
		edgeTop -= 1;
	}
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	read >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		read >> u >> v >> c[i + n];
		e[c[i + n]].emplace_back(i + n);
		G[u].emplace_back(i + n);
		G[v].emplace_back(i + n);
		G[i + n].emplace_back(u);
		G[i + n].emplace_back(v);
	}
	initTree(1);
	for (int i = 1; i <= n; ++i) {
		vi32 node;
		node.emplace_back(1);
		for (auto ed : e[i]) {
			node.emplace_back(ed);
		}
		auto cmp = [](int a, int b) { return dfn[a] < dfn[b]; };
		std::sort(node.begin(), node.end(), cmp);
		node.erase(std::unique(node.begin(), node.end()), node.end());
		top = 0;
		for (auto nd : node) {
			if (top < 2) {
				stk[++top] = nd;
				continue;
			}
			i32 d = LCA(nd, stk[top]);
			if (d == stk[top]) {
				stk[++top] = nd;
				continue;
			}
			while (dep[d] < dep[stk[top]]) {
				if (dep[stk[top - 1]] <= dep[d])
					addEdge(d, stk[top]);
				else {
					addEdge(stk[top - 1], stk[top]);
				}
				top -= 1;
			}
			if (stk[top] != d) stk[++top] = d;
			stk[++top] = nd;
		}
		while (top > 1) {
			addEdge(stk[top - 1], stk[top]);
			top -= 1;
		}
		dp1(1, i);
		dp2(1, i);
		calcAns(1, i);
		clearEdge();
	}
	printf("%lld\n", res);
	return 0;
}
