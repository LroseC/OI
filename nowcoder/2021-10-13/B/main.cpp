#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e6 + 10, mod = 1e9 + 7;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

int n;
int b[N];
int fa[N];
int sz[N];
int tsz[N];
LL ans = 0;
int val[N];
bool del[N];
vector<int> G[N];

/*
 * 暴力思路: dfs() 求解
 * 做 n 遍 dfs, 每次 dfs 求解以当前节点为最大 val 的所有方案加和
 */

void dfs(int u, int fa, int root, int maxval, int dis)
{
	maxval = max(maxval, val[u]);
	if (u != root) {
		ans = ((ans + maxval - dis) % mod + mod) % mod;
	}
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u, root, maxval, dis + 1);
	}
}

inline bool cmp(int a, int b)
{
	return val[a] < val[b];
}

void Get_tsz(int u, int fa)
{
	tsz[u] = 1;
	for (int v : G[u]) {
		if (v == fa) continue;
		Get_tsz(v, u);
		ans = (ans - 1ll * tsz[v] * (n - tsz[v]) % mod + mod) % mod;
		tsz[u] += tsz[v];
	}
}
inline int find(int x)
{
	if (fa[x] != x) return find(fa[x]);
	return x;
}
inline void merge(int x, int y)
{
	int u = find(x), v = find(y);
	if (sz[u] > sz[v]) swap(u, v);
	fa[u] = v;
	sz[v] += sz[u];
}
inline int getsz(int x)
{
	return sz[find(x)];
}
inline void Work(void)
{
	for (int i = 1; i <= n; ++i) {
		sz[i] = 1;
		b[i] = fa[i] = i;
	}
	sort(b + 1, b + 1 + n, cmp);
	for (int i = 1; i <= n; ++i) {
		int u = b[i];
		int tot = 0;
		for (int v : G[u]) {
			if (!del[v]) continue;
			ans = (ans + 1ll * tot * getsz(v) % mod * val[u] % mod) % mod;
			ans = (ans + 1ll * getsz(v) * val[u] % mod) % mod;
			tot += getsz(v);
			merge(u, v);
		}
		del[u] = 1;
	}
	Get_tsz(1, -1);
	printf("%lld\n", ((ans + mod) % mod) * 2ll % mod);
}

int main(void)
{
	n = read();
	for (int i = 1; i <= n; ++i) val[i] = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	Work();
	/*
	if (n <= 1000) {
		for (int i = 1; i <= n; ++i) {
			dfs(i, -1, i, val[i], 0);
			del[i] = 1;
		}
		printf("%lld\n", ans);
	}
	else Work();
	*/
	return 0;
}
