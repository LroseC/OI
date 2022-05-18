#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

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
const int N = 2e5 + 10;

int n, m, Q, idx, idCnt;
int stk[N], stkTop;
int dis[N], sz[N], fa[N], son[N], id[N], top[N], dep[N];
int dfn[N], low[N], dfnCnt;
std::vector<int> oG[N], G[N];

void clear(void)
{
	for (int i = 1; i <= n; ++i)
		oG[i].clear();
	for (int i = 1; i <= idx; ++i)
		G[i].clear();
	std::memset(sz, 0, sizeof sz);
	std::memset(fa, 0, sizeof fa);
	std::memset(id, 0, sizeof id);
	std::memset(dis, 0, sizeof dis);
	std::memset(dfn, 0, sizeof dfn);
	std::memset(low, 0, sizeof low);
	std::memset(son, 0, sizeof son);
	std::memset(top, 0, sizeof top);
	std::memset(dep, 0, sizeof dep);
	stkTop = idx = idCnt = dfnCnt = 0;
}
void tarjan(int u)
{
	dfn[u] = low[u] = ++dfnCnt;
	stk[++stkTop] = u;
	for (int v : oG[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
			if (low[v] == dfn[u]) {
				int square = ++idx;
				do {
					G[idx].emplace_back(stk[stkTop]);
					G[stk[stkTop]].emplace_back(idx);
					--stkTop;
				} while(stk[stkTop + 1] != v);
				G[idx].emplace_back(u);
				G[u].emplace_back(idx);
			}
		}
		else low[u] = std::min(low[u], dfn[v]);
	}
}

void getSon(int u)
{
	sz[u] = 1;
	dis[u] = dis[fa[u]] + (u <= n);
	dep[u] = dep[fa[u]] + 1;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			getSon(v);
			sz[u] += sz[v];
			if (sz[v] > sz[son[u]])
				son[u] = v;
		}
}
void initCut(int u, int tp)
{
	id[u] = ++idCnt;
	top[u] = tp;
	if (son[u])
		initCut(son[u], tp);
	for (int v : G[u])
		if (v != fa[u] && v != son[u])
			initCut(v, v);
}
int LCA(int u, int v)
{
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			std::swap(u, v);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v])
		std::swap(u, v);
	return v;
}

void solve(void)
{
	read >> n >> m;
	for (int i = 1, u, v; i <= m; ++i) {
		read >> u >> v;
		oG[u].emplace_back(v);
		oG[v].emplace_back(u);
	}
	idx = n;
	stkTop = 0;
	tarjan(1);
	getSon(1);
	initCut(1, 1);
	read >> Q;
	for (int i = 1, sz; i <= Q; ++i) {
		read >> sz;
		std::vector<int> city(sz);
		for (int j = 0; j < sz; ++j)
			read >> city[j];
		auto cmp = [](int a, int b)
		{ return id[a] < id[b]; };
		std::sort(city.begin(), city.end(), cmp);
		int top = 0;
		stk[++top] = 1;
		int res = 0;
		for (auto u : city) {
			int d = LCA(stk[top], u);
			if (d != stk[top]) {
				while (id[d] < id[stk[top - 1]]) {
					res += dis[stk[top]] - dis[stk[top - 1]];
					--top;
				}
				res += dis[stk[top]] - dis[d];
				--top;
				if (d != stk[top])
					stk[++top] = d;
			}
			stk[++top] = u;
		}
		res += dis[stk[top]];
		printf("%d\n", res - sz);
	}
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		solve();
		clear();
	}
	return 0;
}
