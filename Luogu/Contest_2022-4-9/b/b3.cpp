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
int sz[N];
int f[N][10010];
std::vector<int> G[N];

void dp(int u, int fa)
{
	sz[u] = a[u];
	for (int v : G[u])
		if (v != fa) {
			dp(v, u);
			sz[u] += sz[v];
			for (int i = m; i >= 0; --i)
				for (int j = 0; j <= i; ++j)
					f[u][i] = std::max(f[u][i], f[u][i - j] + f[v][j]);
		}
	for (int i = m; i >= a[u]; --i)
		f[u][i] = f[u][i - a[u]] + b[u];
	for (int i = 1; i <= m; ++i)
		ans = std::max(ans, f[u][i]);
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
	dp(1, 0);
	printf("%d\n", ans);
	return 0;
}
