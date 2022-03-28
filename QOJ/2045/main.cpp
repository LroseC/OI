#include <vector>
#include <cctype>
#include <cstdio>
#include <utility>

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

const int N = 2e5 + 10, mod = 1e9 + 7;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct PIII
{
	int a, b, c;

	PIII(void) {}
	PIII(int _a, int _b, int _c) { a = _a, b = _b, c = _c; }
	PIII operator+(const PIII &other) const
	{
		return PIII(Mod(a + other.a), Mod(b + other.b), Mod(c + other.c));
	}
};

int n, m;
int w[N], inW[N];
std::vector<int> G[N];
int sz[N], fa[N], dep[N];
int idx, L[N], R[N], invL[N];
int sum[N << 2], sqsum[N << 2], insum[N << 2];

void getFa(int u)
{
	sz[u] = 0;
	L[u] = ++idx;
	invL[idx] = u;
	dep[u] = dep[fa[u]] + 1;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			getFa(v);
			inW[u] = (inW[u] + 1ll * sz[u] * sz[v]) % mod;
			sz[u] += sz[v];
		}
	++sz[u];
	R[u] = idx;
}
void maintain(int u)
{
	sum[u] = Mod(sum[u << 1] + sum[u << 1 | 1]);
	sqsum[u] = Mod(sqsum[u << 1] + sqsum[u << 1 | 1]);
	insum[u] = Mod(insum[u << 1] + insum[u << 1 | 1]);
}
void build(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		sum[u] = 1ll * w[invL[l]] * sz[invL[l]] % mod;
		sqsum[u] = 1ll * sum[u] * sz[invL[l]] % mod;
		insum[u] = 1ll * w[invL[l]] * inW[invL[l]] % mod;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void update(int pos, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		sum[u] = 1ll * w[invL[l]] * sz[invL[l]] % mod;
		sqsum[u] = 1ll * sum[u] * sz[invL[l]] % mod;
		insum[u] = 1ll * w[invL[l]] * inW[invL[l]] % mod;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
		update(pos, u << 1, l, mid);
	else
		update(pos, u << 1 | 1, mid + 1, r);
	maintain(u);
}
PIII query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R)
		return PIII(sum[u], sqsum[u], insum[u]);
	int mid = l + r >> 1;
	PIII res(0, 0, 0);
	if (L <= mid)
		res = res + query(L, R, u << 1, l, mid);
	if (R > mid)
		res = res + query(L, R, u << 1 | 1, mid + 1, r);
	return res;
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		w[i] = 1;
	getFa(1);
	build();
	for (int i = 1; i <= m; ++i) {
		int op; read >> op;
		if (op == 1) {
			int u, x;
			read >> u >> x;
			w[u] = (w[u] + x) % mod;
			update(L[u]);
		}
		else {
			int u; read >> u;
			auto tmp = query(L[u], R[u]);
			printf("%d\n", (((sz[u] + 1ll) * tmp.a % mod - tmp.b + mod) % mod + tmp.c) % mod);
		}
	}
	return 0;
}
