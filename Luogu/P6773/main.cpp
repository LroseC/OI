#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 5e5 + 10, mod = 998244353;

int n, m;
int dep[N];
int root[N];
vector<int> G[N], Lim[N];

namespace SegmentTree
{
	struct node
	{
		int l, r, sum, tag;
	} tr[N << 8];
	int idx;

	int New(void)
	{
		int u = ++idx;
		tr[u].tag = 1;
		tr[u].l = tr[u].r = tr[u].sum = 0;
		return u;
	}
	void mul(int u, int val)
	{
		tr[u].sum = 1ll * tr[u].sum * val % mod;
		tr[u].tag = 1ll * tr[u].tag * val % mod;
	}
	void spread(int u)
	{
		if (tr[u].tag != 1) {
			mul(tr[u].l, tr[u].tag);
			mul(tr[u].r, tr[u].tag);
			tr[u].tag = 1;
		}
	}
	void maintain(int u)
	{
		tr[u].sum = (tr[tr[u].l].sum + tr[tr[u].r].sum) % mod;
	}
	void add(int pos, int &u, int l = 0, int r = n)
	{
		if (!u) u = New();
		if (l == r) {
			tr[u].sum = 1;
			return;
		}
		spread(u);
		int mid = l + r >> 1;
		if (pos <= mid) add(pos, tr[u].l, l, mid);
		else add(pos, tr[u].r, mid + 1, r);
		maintain(u);
	}
	int query(int u, int L, int R, int l = 0, int r = n)
	{
		if (L <= l && r <= R)
			return tr[u].sum;
		spread(u);
		int mid = l + r >> 1;
		int res = 0;
		if (L <= mid) res = (res + query(tr[u].l, L, R, l, mid)) % mod;
		if (R > mid) res = (res + query(tr[u].r, L, R, mid + 1, r)) % mod;
		return res;
	}
	int merge(int u, int v, int &su, int &sv, int l = 0, int r = n)
	{
		/*
			g[a][b] = sum(f[a][0 - b]);
			g0: g[u][i - 1];
			g1: g[v][dep[u]];
			g2: g[v][i];
			su = g[u][i - 1];
			sv = g[v][dep[u]] + g[v][i];
		*/
		if (!u && !v) return 0;
		if (!u) {
			sv = (sv + tr[v].sum) % mod;
			mul(v, su);
			return v;
		}
		if (!v) {
			su = (su + tr[u].sum) % mod;
			mul(u, sv);
			return u;
		}
		if (l == r) {
			int sx = tr[u].sum, sy = tr[v].sum;
			sv = (sv + sy) % mod;
			tr[u].sum = (1ll * tr[u].sum * sv + 1ll * tr[v].sum * su) % mod;
			su = (su + sx) % mod;
			return u;
		}
		spread(u); spread(v);
		int mid = l + r >> 1;
		tr[u].l = merge(tr[u].l, tr[v].l, su, sv, l, mid);
		tr[u].r = merge(tr[u].r, tr[v].r, su, sv, mid + 1, r);
		maintain(u);
		return u;
	}
}

void dfs(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	int res = 0;
	for (int v : Lim[u])
		res = max(res, dep[v]);
	SegmentTree::add(res, root[u]);
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
		int g0 = 0, g2 = SegmentTree::query(root[v], 0, dep[u]);
		root[u] = SegmentTree::merge(root[u], root[v], g0, g2); //not finished.
	}
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;// u -> root
		Lim[v].emplace_back(u);
	}
	dfs(1, 0);
	printf("%d\n", SegmentTree::query(root[1], 0, 0));
	return 0;
}
