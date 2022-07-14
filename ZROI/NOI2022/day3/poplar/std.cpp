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
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 55, M = 2005;

int n, m, Q;
int w[N], v[N];
i64 f[101][N][M];
int sz[N], del[N], fa[N];
int G[N][N];
vint OG[N], T[N];

template<typename T>
inline void maxx(T &a, T b) { a = std::max(a, b); }
void getSz(int u, int fa)
{
	sz[u] = 1;
	for (int v : OG[u])
		if (v != fa && !del[v]) {
			getSz(v, u);
			sz[u] += sz[v];
		}
}
void getRoot(int u, int fa, int tot, int &root, int &minSize)
{
	int maxSon = 0;
	for (int v : OG[u])
		if (v != fa && !del[v]) {
			getRoot(v, u, tot, root, minSize);
			maxSon = std::max(maxSon, sz[v]);
		}
	maxSon = std::max(maxSon, tot - sz[u]);
	if (maxSon < minSize) {
		root = u;
		minSize = maxSon;
	}
}
void buildDT(int u)
{
	del[u] = 1;
	for (int v : OG[u])
		if (!del[v]) {
			getSz(v, u);
			int root, minSize = 0x3f3f3f3f;
			getRoot(v, u, sz[v], root, minSize);
			fa[root] = u;
			T[u].emplace_back(root);
			buildDT(root);
		}
}
void dp(int u, int dep)
{
	for (int s = 0; s < 1 << dep; ++s) {
		std::memset(f[s | 1 << dep], 0xcf, sizeof f[s | 1 << dep]);
		int delt = 1;
		for (int i = fa[u], j = dep - 1; j >= 0; i = fa[i], --j) {
			if (G[u][i] && (s >> j & 1)) --delt;
		}
		for (int i = std::max(0, -delt); i <= n; ++i) {
			int tos = s | 1 << dep, toi = i + delt;
			for (int j = w[u]; j <= m; ++j) {
//				if (f[s][i][j - w[u]] || (j - w[u] == 0 && s == 0 && i == 0)) {
//					maxx(f[tos][toi][j], f[s][i][j - w[u]] + v[u]);
//				}
				maxx(f[tos][toi][j], f[s][i][j - w[u]] + v[u]);
			}
		}
	}
	
	for (int v : T[u])
		dp(v, dep + 1);
	for (int s = 0; s < 1 << dep; ++s) {
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= m; ++j)
				maxx(f[s][i][j], f[s | 1 << dep][i][j]);
	}
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m >> Q;
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		OG[u].emplace_back(v);
		OG[v].emplace_back(u);
		G[u][v] = G[v][u] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		read >> w[i] >> v[i];
	}
	int root = 0, minSize = 0x3f3f3f3f;
	getSz(1, 0);
	getRoot(1, 0, n, root, minSize);
	buildDT(root);
	std::memset(f, 0xcf, sizeof f);
	f[0][0][0] = 0;
	dp(root, 0);
	while (Q--) {
		int t, x; read >> t >> x;
		printf("%lld\n", f[0][t][x] < 0 ? -1ll : f[0][t][x]);
	}
	return 0;
}
