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
const int N = 3e5 + 10;

int n, m, root;
int w[N], sz[N], son[N], fa[N], dep[N], top[N];
std::vector<int> G[N];
int idx, L[N], R[N], revL[N], depp[N];
bool _isFa[N];
int _Sonp[N];

void initSz(int u, int fath)
{
	sz[u] = 1;
	son[u] = 0;
	fa[u] = fath;
	dep[u] = dep[fath] + 1;
	for (int v : G[u])
		if (v != fath) {
			initSz(v, u);
			sz[u] += sz[v];
			if (sz[v] > sz[son[u]])
				son[u] = v;
		}
}
void initCut(int u, int fa, int tp)
{
	++idx;
	L[u] = idx;
	revL[idx] = u;
	top[u] = tp;
	for (int v : G[u])
		if (v != fa && v != son[u])
			initCut(v, u, v);
	if (son[u])
		initCut(son[u], u, tp);
	R[u] = idx;
}
int LCA(int u, int v)
{
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) std::swap(u, v);
		v = fa[top[v]];
	}
	if (dep[u] > dep[v]) std::swap(u, v);
	return u;
}
void init(int rt)
{
	while (rt) {
		_isFa[top[rt]] = 1;
		depp[top[rt]] = dep[rt];
		_Sonp[fa[top[rt]]] = top[rt];
		rt = fa[top[rt]];
	}
}
void clear(int rt)
{
	while (rt) {
		_isFa[top[rt]] = 0;
		depp[top[rt]] = 0;
		_Sonp[fa[top[rt]]] = 0;
		rt = fa[top[rt]];
	}
}
bool isFa(int u)
{
	return _isFa[top[u]] && dep[u] <= depp[top[u]];
}
int Sonp(int u)
{
	if (_Sonp[u])
		return _Sonp[u];
	return son[u];
}
i64 tag[N << 2], sum[N << 2];
void maintain(int u) { sum[u] = sum[u << 1] + sum[u << 1 | 1]; }
void _add(int u, i64 val, int l, int r)
{
	tag[u] += val;
	sum[u] += 1ll * val * (r - l + 1);
}
void spread(int u, int l, int r)
{
	if (tag[u]) {
		int mid = l + r >> 1;
		_add(u << 1, tag[u], l, mid);
		_add(u << 1 | 1, tag[u], mid + 1, r);
		tag[u] = 0;
	}
}
void build(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		sum[u] = w[revL[l]];
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
		_add(u, val, l, r);
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
	spread(u, l, r);
	i64 res = 0;
	int mid = l + r >> 1;
	if (L <= mid)
		res += query(L, R, u << 1, l, mid);
	if (R > mid)
		res += query(L, R, u << 1 | 1, mid + 1, r);
	return res;
}

signed main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i)
		read >> w[i];
	for (int i = 1; i < n; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	root = 1;
	initSz(1, 0);
	initCut(1, 0, 1);
	build();
	for (int i = 1; i <= m; ++i) {
		int op; read >> op;
		if (op == 1) {
			clear(root);
			read >> root;
			init(root);
		}
		else if (op == 2) {
			int u, v, x;
			read >> u >> v >> x;
			int d = LCA(u, v);
			if (d == root) add(1, n, x);
			else if (!isFa(d))
				add(L[d], R[d], x);
			else {
				int od = d;
				int tmp = LCA(root, u);
				if (dep[tmp] > dep[d]) d = tmp;
				tmp = LCA(root, v);
				if (dep[tmp] > dep[d]) d = tmp;
				tmp = LCA(1, u);
				if (dep[tmp] > dep[d]) d = tmp;
				tmp = LCA(1, v);
				if (dep[tmp] > dep[d]) d = tmp;

				if (d == root) add(1, n, x);
				else {
					add(1, n, x);
					d = Sonp(d);
					add(L[d], R[d], -x);
				}
			}
		}
		else {
			int u; read >> u;
			i64 res = 0;
			if (u == root) res = query(1, n);
			else if (isFa(u)) {
				res += query(1, n);
				u = Sonp(u);
				res -= query(L[u], R[u]);
			}
			else
				res = query(L[u], R[u]);
			printf("%lld\n", res);
		}
	}
	return 0;
}
