#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 5e5 + 10;
const int Mod = 998244353;

struct Edge
{
	int v, id;
};

int ans;
int n, m;
int fa[N];
int lenth[N];
int edgecnt[N];
vector<Edge> G[N];

int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

void dfs(int u, int fa)
{
	for (auto t : G[u]) {
		int v = t.v, id = t.id;
		if (v == fa) continue;
		dfs(v, u);
		if (edgecnt[v]) {
			edgecnt[u] ^= 1;
			ans = (ans + lenth[t.id]) % Mod;
		}
	}
}

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) fa[i] = i;
	lenth[0] = 1;
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		edgecnt[u] ^= 1;
		edgecnt[v] ^= 1;
		if (find(u) != find(v)) {
			fa[find(u)] = find(v);
			G[u].emplace_back(Edge({v, i}));
			G[v].emplace_back(Edge({u, i}));
		}
		lenth[i] = (lenth[i - 1] << 1) % Mod;
		ans = (ans + lenth[i]) % Mod;
	}
	dfs(1, -1);
	printf("%d\n", ans);
	return 0;
}