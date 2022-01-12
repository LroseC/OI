#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 3e5 + 10, mod = 998244353;

int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}

int n, m;
int fa[N], w[N], p[N], P[N];
int ch[N][2];
int nums[N];
int root[N];

namespace SegmentTree
{
	struct node
	{
		int l, r, val, tag;
	} tr[N << 6];
	int idx;

	int New(void)
	{
		int u = ++idx;
		tr[u].l = tr[u].r = 0;
		tr[u].val = 0;
		tr[u].tag = 1;
		return u;
	}
	void mul(int u, int val)
	{
		if (!u) return;
		tr[u].val = 1ll * tr[u].val * val % mod;
		tr[u].tag = 1ll * tr[u].tag * val % mod;
	}
	void spread(int u)
	{
		if (tr[u].tag == 1) return;
		if (tr[u].l)
			mul(tr[u].l, tr[u].tag);
		if (tr[u].r)
			mul(tr[u].r, tr[u].tag);
		tr[u].tag = 1;
	}
	void maintain(int u)
	{
		tr[u].val = (tr[tr[u].l].val + tr[tr[u].r].val) % mod;
	}
	void add(int pos, int &u, int l, int r)
	{
		if (!u) u = New();
		if (l == r) {
			tr[u].val = 1;
			return;
		}
		spread(u);
		int mid = l + r >> 1;
		if (pos <= mid) add(pos, tr[u].l, l, mid);
		else add(pos, tr[u].r, mid + 1, r);
		maintain(u);
	}
	int merge(int id, int u0, int u1, int mul0, int mul1, int l, int r)
	{
		if (!u0 && !u1) return 0;
		if (!u0) {
			mul(u1, mul1);
			return u1;
		}
		if (!u1) {
			mul(u0, mul0);
			return u0;
		}
		spread(u0);
		spread(u1);
		int suml0 = tr[tr[u0].l].val;
		int sumr0 = tr[tr[u0].r].val;
		int suml1 = tr[tr[u1].l].val;
		int sumr1 = tr[tr[u1].r].val;
		int mid = l + r >> 1;
		tr[u0].l = merge(id, tr[u0].l, tr[u1].l, (mul0 + 1ll * sumr1 * (1 - p[id] + mod)) % mod, (mul1 + 1ll * sumr0 * (1 - p[id] + mod)) % mod, l, mid);
		tr[u0].r = merge(id, tr[u0].r, tr[u1].r, (mul0 + 1ll * suml1 * p[id]) % mod, (mul1 + 1ll * suml0 * p[id]) % mod, mid + 1, r);
		maintain(u0);
		return u0;
	}
	void get_ans(int u, int l, int r)
	{
		if (!u) return;
		if (l == r) {
			P[l] = tr[u].val;
			return;
		}
		spread(u);
		int mid = l + r >> 1;
		get_ans(tr[u].l, l, mid);
		get_ans(tr[u].r, mid + 1, r);
	}
}

void dfs(int u)
{
	if (!ch[u][0]) {
		SegmentTree::add(w[u], root[u], 1, m);
		return;
	}
	else if (!ch[u][1]) {
		dfs(ch[u][0]);
		root[u] = root[ch[u][0]];
		return;
	}
	else {
		dfs(ch[u][0]);
		dfs(ch[u][1]);
		root[u] = SegmentTree::merge(u, root[ch[u][0]], root[ch[u][1]], 0, 0, 1, m);
		return;
	}
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> fa[i];
		if (ch[fa[i]][0])
			ch[fa[i]][1] = i;
		else ch[fa[i]][0] = i;
	}
	for (int i = 1; i <= n; ++i) {
		if (!ch[i][0]) {
			cin >> w[i];
			nums[++m] = w[i];
		}
		else {
			cin >> p[i];
			p[i] = 1ll * p[i] * qpow(10000, mod - 2) % mod;
		}
	}
	sort(nums + 1, nums + 1 + m);
	for (int i = 1; i <= n; ++i)
		if (!ch[i][0])
			w[i] = lower_bound(nums + 1, nums + 1 + m, w[i]) - nums;

	dfs(1);
	SegmentTree::get_ans(root[1], 1, m);
	int res = 0;
	for (int i = 1; i <= m; ++i) {
		int tmp = 1ll * P[i] * P[i] % mod;
		res = (res + (1ll * i * nums[i] % mod * tmp % mod)) % mod;
	}
	printf("%d\n", res);
	return 0;
}
/*
   思路: 设 P[u][i] 表示节点 u 权值为 i 的概率.
   P[u][i] = SUM(u -> v) P[v][i] * ( SUM(P[(without v)][j <= i]) * p[u] + SUM(P[(without v)][j >= i] * (1 - p[u])) )
*/
