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
template<typename T>
T maxx(T &a, T b) { return a = std::max(a, b); }

int n, m, Q;
int sz[N], son[N], w[N], v[N];
i64 f[64][N][M], tmpf[64][N][M];
vint G[N];

void getSon(int u, int fa)
{
	sz[u] = 1;
	for (int v : G[u])
		if (v != fa) {
			getSon(v, u);
			if (sz[v] > sz[son[u]])
				son[u] = v;
			sz[u] += sz[v];
		}
}
void dp(int u, int fa, int top)
{
	for (int i = 0; i < 1 << top + 1; ++i)
		for (int j = 0; j <= n; ++j)
			for (int k = 0; k <= m; ++k) tmpf[i][j][k] = 0xcfcfcfcfcfcfcfcf;
	int fatop = top - (u != son[fa]);
	int o = (1 << top) - 1;
	for (int i = 0; i < 1 << fatop + 1; ++i) {
		int delt;
		if (i == 0) delt = 1;
		else delt = (i >> fatop & 1) ? 0 : 1;
		for (int j = 0; j <= n; ++j)
			for (int k = 0; k <= m; ++k) {
				maxx(tmpf[i & o][j][k], f[i][j][k]);
				if (j >= delt && k >= w[u]) {
					maxx(tmpf[i | (1 << top)][j][k], f[i][j - delt][k - w[u]] + v[u]);
				}
			}
	}
	for (int i = 0; i < 1 << top + 1; ++i)
		for (int j = 0; j <= n; ++j)
			for (int k = 0; k <= m; ++k) f[i][j][k] = tmpf[i][j][k];
	for (int v : G[u])
		if (v != fa && v != son[u]) dp(v, u, top + 1);
	if (son[u])
		dp(son[u], u, top);
	else {
		for (int i = 0; i < 1 << top; ++i)
			for (int j = 0; j <= n; ++j)
				for (int k = 0; k <= m; ++k)
					maxx(f[i][j][k], f[i | 1 << top][j][k]);
	}
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m >> Q;
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i) {
		read >> w[i] >> v[i];
	}
	getSon(1, 0);
	std::memset(f, 0xcf, sizeof f);
	f[0][0][0] = 0;
	dp(1, 0, 0);
	while (Q--) {
		int t, x; read >> t >> x;
		printf("%lld\n", std::max(-1ll, f[0][t][x]));
	}
	return 0;
}
/*
	一个点是否被选的状态需要保存到其子节点全部被考虑过为止.
	考虑 dsu on tree, 先遍历轻儿子, 再遍历重儿子, 需要保存状态的节点在 log2(n) 级别, 状压即可, 状态数 O(n).
	常数似乎远大于点分治做法, 不知道为啥.
	Update: 然而并不是, 常数比我自己写的点分治小, 常数大是某些人的问题.
*/
