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
const int N = 2e5 + 10, LG = 20, mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct Edge
{
	int u, v, x, y;

	Edge(int _u, int _v, int _x, int _y) { u = _u, v = _v, x = _x, y = _y; }
};

int n;
int dep[N], fa[N][LG];
int L[N], R[N], idx;
int sum[N << 2], tag[N << 2];
std::vector<int> G[N];
std::vector<Edge> edge;

void getFa(int u)
{
	dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];

	for (int v : G[u])
		if (v != fa[u][0]) {
			fa[v][0] = u;
			getFa(v);
		}
}
void initDfn(int u)
{
	L[u] = ++idx;
	for (int v : G[u])
		if (v != fa[u][0]) initDfn(v);
	R[u] = idx;
}
void mul(int u, int val)
{
	tag[u] = 1ll * tag[u] * val % mod;
	sum[u] = 1ll * sum[u] * val % mod;
}
void maintain(int u) { sum[u] = Mod(sum[u << 1] + sum[u << 1 | 1]); }
void spread(int u, int l, int r)
{
	if (tag[u] != 1) {
		mul(u << 1, tag[u]);
		mul(u << 1 | 1, tag[u]);
		tag[u] = 1;
	}
}
void build(int u = 1, int l = 1, int r = n)
{
	tag[u] = 1;
	if (l == r) {
		sum[u] = 1;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void add(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L > R) return;
	if (L <= l && r <= R) {
		mul(u, val);
		return;
	}
	spread(u, l, r);
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, val, u << 1, l, mid);
	if (R > mid) add(L, R, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int query(int pos, int u = 1, int l = 1, int r = n)
{
	if (l == r)
		return sum[u];
	spread(u, l, r);
	int mid = l + r >> 1;
	if (pos <= mid)
		return query(pos, u << 1, l, mid);
	else
		return query(pos, u << 1 | 1, mid + 1, r);
}

void clear(void)
{
	idx = 0;
	edge.clear();
	for (int i = 1; i <= n; ++i) {
		G[i].clear();
		dep[i] = 0;
		for (int j = 0; j < LG; ++j)
			fa[i][j] = 0;
	}
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		read >> n;
		for (int i = 1; i < n; ++i) {
			int u, v, x, y;
			read >> u >> v >> x >> y;
			int d = std::__gcd(x, y);
			x /= d, y /= d;
			edge.emplace_back(u, v, x, y);
		}
		std::vector<int> w(n + 1);
		for (int i = 1; i <= n; ++i)
			w[i] = 1;
		for (auto t : edge)
		{
			int u = t.u, v = t.v, x = t.x, y = t.y;
			i64 d = std::__gcd(1ll * w[u] * y, 1ll * w[v] * x);
			int ty = 1ll * w[u] * y / d % mod;
			int tx = 1ll * w[v] * x / d % mod;
			w[u] = 1ll * w[u] * tx % mod;
			w[v] = 1ll * w[v] * ty % mod;
			printf("u = %d, v = %d, wu = %d, wv = %d, x = %d, y = %d\n", u, v, w[u], w[v], x, y);
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			ans = Mod(ans + w[i]);
		printf("%lld\n", ans);

		clear();
	}
	return 0;
}
