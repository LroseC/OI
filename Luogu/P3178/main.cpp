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
const int N = 1e5 + 10;

int n, m;
int val[N];
std::vector<int> G[N];
int fa[N], dep[N], son[N], top[N], sz[N];
int idx, L[N], R[N], invL[N];
i64 sum[N << 2], tag[N << 2];

void getFa(int u)
{
	sz[u] = 1;
	son[u] = 0;
	dep[u] = dep[fa[u]] + 1;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			getFa(v);
			if (sz[v] > sz[son[u]])
				son[u] = v;
			sz[u] += sz[v];
		}
}
void initCut(int u, int tp)
{
	L[u] = ++idx;
	invL[idx] = u;
	top[u] = tp;
	if (son[u])
		initCut(son[u], tp);
	for (int v : G[u])
		if (v != fa[u] && v != son[u])
			initCut(v, v);
	R[u] = idx;
}
void addnode(int u, i64 val, int l, int r)
{
	tag[u] += val;
	sum[u] += val * (r - l + 1);
}
void maintain(int u) { sum[u] = sum[u << 1] + sum[u << 1 | 1]; }
void spread(int u, int l, int r)
{
	if (tag[u]) {
		int mid = l + r >> 1;
		addnode(u << 1, tag[u], l, mid);
		addnode(u << 1 | 1, tag[u], mid + 1, r);
		tag[u] = 0;
	}
}
void build(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		sum[u] = val[invL[l]];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void add(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		addnode(u, val, l, r);
		return;
	}
	spread(u, l, r);
	int mid = l + r >> 1;
	if (L <= mid)
		add(L, R, val, u << 1, l, mid);
	if (R > mid)
		add(L, R, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
i64 query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R)
		return sum[u];
	int mid = l + r >> 1;
	spread(u, l, r);
	i64 res = 0;
	if (L <= mid)
		res += query(L, R, u << 1, l, mid);
	if (R > mid)
		res += query(L, R, u << 1 | 1, mid + 1, r);
	return res;
}
i64 queryPath(int u)
{
	i64 res = 0;
	do {
		res += query(L[top[u]], L[u]);
		u = fa[top[u]];
	} while (u);
	return res;
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> val[i];
	for (int i = 1; i < n; ++i) {
		int u, v;
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	getFa(1);
	initCut(1, 1);
	build();
	while (m--) {
		int op; read >> op;
		if (op == 1) {
			int u, val;
			read >> u >> val;
			add(L[u], L[u], val);
		}
		else if (op == 2) {
			int u, val;
			read >> u >> val;
			add(L[u], R[u], val);
		}
		else {
			int u; read >> u;
			printf("%lld\n", queryPath(u));
		}
	}
	return 0;
}
