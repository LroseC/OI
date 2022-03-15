#include <cctype>
#include <cstdio>
#include <iostream>

using namespace std;

using LL = long long;
const int N = 5e4 + 10, LOG = 16;
inline int lowbit(int x) { return x & -x; }

int n, m;

namespace SegmentTree
{
	struct node
	{
		int l, r, tag, left, right, len;
		LL sum;
	} tr[N << 8];
	int idx;

	int New(int l, int r)
	{
		int u = ++idx;
		tr[u].left = l;
		tr[u].right = r;
		tr[u].len = r - l + 1;
		tr[u].l = tr[u].r = tr[u].tag = tr[u].sum = 0;
		return u;
	}
	void maintain(int u)
	{
		tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum;
	}
	void spread(int u)
	{
		if (tr[u].tag) {
			int l = tr[u].left, r = tr[u].right;
			int mid = l + r >> 1;
			if (tr[u].len != 1) {
				if (!tr[u].l)
					tr[u].l = New(l, mid);
				if (!tr[u].r)
					tr[u].r = New(mid + 1, r);
				tr[tr[u].l].tag += tr[u].tag;
				tr[tr[u].l].sum += 1ll * tr[u].tag * tr[tr[u].l].len;
				tr[tr[u].r].tag += tr[u].tag;
				tr[tr[u].r].sum += 1ll * tr[u].tag * tr[tr[u].r].len;
			}
			tr[u].tag = 0;
		}
	}
	void add(int &u, int L, int R, int l = 1, int r = n)
	{
		if (!u)
			u = New(l, r);
		if (L <= l && r <= R) {
			++tr[u].tag;
			tr[u].sum += tr[u].len;
			return;
		}
		spread(u);
		int mid = l + r >> 1;
		if (L <= mid)
			add(tr[u].l, L, R, l, mid);
		if (R > mid)
			add(tr[u].r, L, R, mid + 1, r);
		maintain(u);
	}
	LL query(int u, int L, int R, int l = 1, int r = n)
	{
		if (!u) return 0;
		if (L <= l && r <= R)
			return tr[u].sum;
		spread(u);
		int mid = l + r >> 1;
		LL res = 0;
		if (L <= mid)
			res += query(tr[u].l, L, R, l, mid);
		if (R > mid)
			res += query(tr[u].r, L, R, mid + 1, r);
		maintain(u);
		return res;
	}
}

int tr[N];

void add(int k, int l, int r)
{
	for (int i = k; i <= n; i += lowbit(i))
		SegmentTree::add(tr[i], l, r);
}
int query(LL kth, int l, int r)
{
	int i = 0; LL res = 0;
	for (int k = 1 << 20; k; k >>= 1) {
		if (i + k > n) continue;
		LL tmp = SegmentTree::query(tr[i + k], l, r);
		if (tmp + res < kth) {
			res += tmp;
			i += k;
		}
	}
	return i + 1;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int op, l, r; LL c;
		cin >> op >> l >> r >> c;
		if (op == 1) {
			c = n - c + 1;
			add(c, l, r);
		}
		else
			printf("%d\n", n - query(c, l, r) + 1);
	}
	return 0;
}
/*
   思路: 树套树, 外层值域树状数组，内层序列线段树.
   每次查询的时候在树状数组上倍增.
*/
