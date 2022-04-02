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

using i64 = long long;
const int N = 3e5 + 10;

struct Edge
{
	int v, w;

	Edge(void) {}
	Edge(int _v, int _w) { v = _v, w = _w; }
};

int n, K;
i64 ans, f[N];
std::vector<Edge> G[N];

void dp(int u, int fa)
{
	for (auto t : G[u])
		if (t.v != fa) {
			int v = t.v;
			dp(v, u);
			ans = std::max(ans, f[u] + f[v] + t.w);
			f[u] = std::max(f[u], f[v] + t.w);
		}
}

int main(void)
{
//	freopen("lct.in", "r", stdin);
//	freopen("lct.out", "w", stdout);
	read >> n >> K;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		read >> u >> v >> w;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}
	dp(1, 0);
	printf("%d\n", ans);
	return 0;
}
