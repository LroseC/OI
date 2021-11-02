#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

struct FastStreamInput
{
	using FSI = FastStreamInput;
	template<typename T>
	FSI& operator >> (T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} cin;

const int N = 2e5 + 10, M = 17;

namespace UnionFind
{
	int fa[N];
	void init(int n)
	{
		for (int i = 1; i <= n; ++i)
			fa[i] = i;
	}
	int find(int x)
	{
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
}

int n, m;
int sz[N];
int val[N];
int fa[N][M];
vector<int> G[N];

void dfs(int u)
{
	for (int i = 1; i < M; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	if (!G[u].size()) sz[u] = 1;
	for (int v : G[u]) {
		fa[v][0] = u;
		dfs(v);
		sz[u] += sz[v];
	}
}
int check(int u, int v, int w)
{
	for (int k = M - 1; k >= 0; --k) {
		if (fa[u][k] && val[fa[u][k]] <= w)
			u = fa[u][k];
		if (fa[v][k] && val[fa[v][k]] <= w)
			v = fa[v][k];
	}
	if (u == v) return sz[v];
	else return sz[u] + sz[v];
}

int main(void)
{
	cin >> n >> m;
	UnionFind::init(n);
	int cnt = 0;
	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		u = UnionFind::find(u); v = UnionFind::find(v);
		if (cnt == n - 1) continue;
		if (u == v) continue;
		++cnt;
		val[++n] = i;
		UnionFind::fa[n] = n;
		UnionFind::fa[u] = UnionFind::fa[v] = n;
		G[n].emplace_back(u);
		G[n].emplace_back(v);
	}
	dfs(n);
	int q; cin >> q;
	while (q--) {
		int x, y, z;
		cin >> x >> y >> z;
		int l = 0, r = m, mid;
		while (l < r) {
			mid = l + r >> 1;
			if (check(x, y, mid) >= z) r = mid;
			else l = mid + 1;
		}
		printf("%d\n", l);
	}
	return 0;
}