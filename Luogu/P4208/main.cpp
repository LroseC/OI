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

void add(int u, int v)
{
	++ma[u][u];
	--ma[u][v];
}

int m_tree(void)
{
}

int main(void)
{
	read >> n >> m;
	for (int i = 1, u, v, w; i <= m; ++i) {
		read >> u >> v >> w;
		edge.emplace_back(u, v, w);
	}
	std::sort(edge.begin(), edge.end());
	for (auto e : edge)
		if (find(e.u) != find(e.v)) {
			int u = find(e.u);
			int v = find(e.v);
			fa[u] = v;
			MST.emplace_back(e);
		}
	int res = 1;
	for (int i = 0; i < n - 1; ++i)
		if (i == 0 || MST[i].w != MST[i - 1].w) {
			auto now = MST[i];
			for (int i = 1; i <= n; ++i)
				fa[i] = i;
			for (auto e : MST)
				if (e.w != now.w)
					fa[find(e.u)] = find(e.v);
			int sccCnt = 0;
			for (int i = 1; i <= n; ++i)
				if (i == fa[i]) {
					id[i] = sccCnt;
					scc[sccCnt++] = i;
				}
			std::memset(ma, 0, sizeof ma);
			for (auto e : edge)
				if (e.w == now.w) {
					int u = find(e.u);
					int v = find(e.v);
					if (u != v) {
						add(id[u], id[v]);
						add(id[v], id[u]);
					}
				}
			res = 1ll * res * m_tree(sccCnt) % mod;
		}
	printf("%d\n", res);
	return 0;
}
