#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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

using i64 = long long;
const int N = 1010;

int n, m, ans;
int a[N], b[N];
int sz[N], id[N], invid[N], idx;
int f[N][10010];
std::vector<int> G[N];

void getSz(int u, int fa)
{
	sz[u] = 1;
	for (int v : G[u])
		if (v != fa) {
			getSz(v, u);
			sz[u] += sz[v];
		}
	id[u] = ++idx;
	invid[idx] = u;
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> a[i] >> b[i];
	for (int i = 1; i < n; ++i) {
		int u, v;
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	getSz(1, 0);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			f[i][j] = f[i - sz[invid[i]]][j];
			if (j - a[invid[i]] >= 0)
				f[i][j] = std::max(f[i][j], f[i - 1][j - a[invid[i]]] + b[invid[i]]);
			ans = std::max(ans, f[i][j]);
		}
	printf("%d\n", ans);
	return 0;
}
