#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
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

const int N = 1e5 + 10;

int n, m, root;
int idx, L[N], R[N], revL[N];
int val[N], dep[N], fa[N], son[N], sz[N], top[N];
std::vector<int> G[N];
int tr[N << 2];
bool tag[N << 2];

void getFa(int u)
{
	sz[u] = 1;
	son[u] = 0;
	dep[u] = dep[fa[u]] + 1;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			getFa(v);
			sz[u] += sz[v];
			if (sz[v] > sz[son[u]])
				son[u] = v;
		}
}
void initCut(int u, int tp)
{
	L[u] = ++idx;
	revL[idx] = u;
	top[u] = tp;
	if (son[u])
		initCut(son[u], tp);
	for (int v : G[u])
		if (v != fa[u] && v != son[u])
			initCut(v, v);
	R[u] = idx;
}
int LCA(int u, int v)
{
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			std::swap(u, v);
		u = fa[top[u]];
	}
	if (dep[u] > dep[v])
		std::swap(u, v);
	return u;
}
int getSon(int u)
{
	int v = root;
	while (top[u] != top[v]) {
		if (fa[top[v]] == u)
			return top[v];
		v = fa[top[v]];
	}
	return son[u];
}
void give(int u, int val)
{
	tag[u] = 1;
	tr[u] = val;
}
void maintain(int u) { tr[u] = std::min(tr[u << 1], tr[u << 1 | 1]); }
void spread(int u)
{
	if (tag[u]) {
		give(u << 1, tr[u]);
		give(u << 1 | 1, tr[u]);
		tag[u] = 0;
	}
}
void build(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u] = val[revL[l]];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void change(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L > R) return;
	if (L <= l && r <= R) {
		give(u, val);
		return;
	}
	spread(u);
	int mid = l + r >> 1;
	if (L <= mid) change(L, R, val, u << 1, l, mid);
	if (R > mid) change(L, R, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L > R) return INT_MAX;
	if (L <= l && r <= R)
		return tr[u];
	spread(u);
	int mid = l + r >> 1;
	int res = INT_MAX;
	if (L <= mid)
		res = std::min(res, query(L, R, u << 1, l, mid));
	if (R > mid)
		res = std::min(res, query(L, R, u << 1 | 1, mid + 1, r));
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
		read >> val[i];
	getFa(1);
	initCut(1, 1);
	build();
	read >> root;
	for (int i = 1; i <= m; ++i) {
		int op; read >> op;
		if (op == 1) {
			read >> root;
		}
		else if (op == 2) {
			int u, v, x;
			read >> u >> v >> x;
			while (top[u] != top[v]) {
				if (dep[top[u]] < dep[top[v]])
					std::swap(u, v);
				change(L[top[u]], L[u], x);
				u = fa[top[u]];
			}
			if (L[u] > L[v])
				std::swap(u, v);
			change(L[u], L[v], x);
		}
		else {
			int u; read >> u;
			if (u == root) {
				printf("%d\n", tr[1]);
			}
			else if (LCA(u, root) == u) {
				int v = getSon(u);
				printf("%d\n", std::min(query(1, L[v] - 1), query(R[v] + 1, n)));
			}
			else {
				printf("%d\n", query(L[u], R[u]));
			}
		}
	}
	return 0;
}
