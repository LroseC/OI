#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>

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

struct Edge
{
	int v, c;
	Edge(void) {}
	Edge(int _v, int _c) { v = _v, c = _c; }
};

int n, m, L, R;
int val[N];
i64 ans = LLONG_MIN;
std::vector<Edge> G[N];

void dfs(int u, int fa, int len, int lastColor, i64 res)
{
	if (L <= len && len <= R)
		ans = std::max(ans, res);
	for (auto t : G[u])
		if (t.v != fa)
			dfs(t.v, u, len + 1, t.c, res + (t.c != lastColor) * val[t.c]); 
}

int main(void)
{
	read >> n >> m >> L >> R;
	for (int i = 1; i <= m; ++i)
		read >> val[i];
	for (int i = 1, u, v, c; i < n; ++i) {
		read >> u >> v >> c;
		G[u].emplace_back(v, c);
		G[v].emplace_back(u, c);
	}
	for (int i = 1; i <= n; ++i)
		dfs(i, 0, 0, -1, 0);
	printf("%lld\n", ans);
	return 0;
}
