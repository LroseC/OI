#include <cmath>
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
const int N = 1010, mod = 31011;

struct Edge
{
	int u, v, w;

	Edge(void) {}
	Edge(int _u, int _v, int _w) { u = _u, v = _v, w = _w; }
	bool operator<(const Edge &other) const
	{ return w < other.w; }
};

int n, m;
int f[N], fa[N];
int ma[N][N];
int scc[N], id[N], sccCnt;
std::vector<Edge> edge, MST;

int find(int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }
void add(int u, int v)
{
	++ma[u][u];
	--ma[u][v];
}

int m_tree(int n)
{
	int res = 1;
	--n;
	for (int i = 0; i < n; ++i) {
		int t = i;
		for (int j = i + 1; j < n; ++j)
			if (abs(ma[j][i]) > abs(ma[t][i])) t = j;
		if (i != t) res *= -1;
		for (int j = 0; j < n; ++j)
			std::swap(ma[i][j], ma[t][j]);
		for (int j = i + 1; j < n; ++j)
			while (ma[j][i]) {
				int tmp = ma[i][i] / ma[j][i];
				for (int k = 0; k < n; ++k)
					ma[i][k] = (ma[i][k] - 1ll * tmp * ma[j][k]) % mod;
				res *= -1;
				for (int k = 0; k < n; ++k)
					std::swap(ma[i][k], ma[j][k]);
			}
	}
	for (int i = 0; i < n; ++i)
		res = 1ll * res * ma[i][i] % mod;
	return (res + mod) % mod;
}

int main(void)
{
	read >> n >> m;
	for (int i = 1, u, v, w; i <= m; ++i) {
		read >> u >> v >> w;
		edge.emplace_back(u, v, w);
	}
	std::sort(edge.begin(), edge.end());
	for (int i = 1; i <= n; ++i) fa[i] = i;
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
