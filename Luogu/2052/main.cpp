#include <vector>
#include <cctype>
#include <cstdio>
#include <assert.h>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e6 + 10;
inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

struct Edge
{
	int v, w;
};

int n;
LL ans;
int sz[N];
vector<Edge> G[N];

void dfs(int u, int fa)
{
	sz[u] = 1;
	for (auto t : G[u]) {
		int v = t.v, w = t.w;
		if (v == fa) continue;
		dfs(v, u);
		ans += 1ll * abs(n - sz[v] - sz[v]) * w;
		sz[u] += sz[v];
	}
}

int main(void)
{
	n = read();
	assert(n <= 1e6);
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read(), w = read();
		G[u].emplace_back(Edge({v, w}));
		G[v].emplace_back(Edge({u, w}));
	}
	dfs(1, -1);
	printf("%lld\n", ans);
	return 0;
}