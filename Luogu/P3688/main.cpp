#include <cstdio>
#include <iostream>

using namespace std;

using LL = long long;
const int N = 1e5 + 10, mod = 998244353;

int n, m;
int A[N];

int merge(int a, int b)
{
	LL res = 1ll * a * b % mod;
	res = (res + (1ll - a) * (1ll - b) % mod) % mod;
	return (res + mod) % mod;
}

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

namespace SegmentTree
{
	struct node
	{
		int l, r, val;
	} tr[N << 10];
	int idx;

	void add(int L, int R, int val, int &u, int l = 0, int r = n)
	{
		if (L > R) return;
		if (!u) {
			u = ++idx;
			tr[u].val = 1;
		}
		if (L <= l && r <= R) {
			tr[u].val = merge(tr[u].val, val);
			return;
		}
		int mid = l + r >> 1;
		if (L <= mid) add(L, R, val, tr[u].l, l, mid);
		if (R > mid) add(L, R, val, tr[u].r, mid + 1, r);
	}
	int query(int pos, int u = 1, int l = 0, int r = n)
	{
		if (!u) return 1;
		if (l == r) return tr[u].val;
		int mid = l + r >> 1;
		if (pos <= mid) return merge(tr[u].val, query(pos, tr[u].l, l, mid));
		else return merge(tr[u].val, query(pos, tr[u].r, mid + 1, r));
	}
}

int tr[N << 2];

void addMatrix(int L, int R, int yl, int yr, int val, int u = 1, int l = 0, int r = n)
{
	if (L > R) return;
	if (L <= l && r <= R) {
		SegmentTree::add(yl, yr, val, tr[u]);
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) addMatrix(L, R, yl, yr, val, u << 1, l, mid);
	if (R > mid) addMatrix(L, R, yl, yr, val, u << 1 | 1, mid + 1, r);
}
int query(int x, int y, int u = 1, int l = 0, int r = n)
{
	if (l == r)
		return SegmentTree::query(y, tr[u]);
	int mid = l + r >> 1;
	if (x <= mid) return merge(SegmentTree::query(y, tr[u]), query(x, y, u << 1, l, mid));
	else return merge(SegmentTree::query(y, tr[u]), query(x, y, u << 1 | 1, mid + 1, r));
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int tick = 1; tick <= m; ++tick) {
		int op;
		cin >> op;
		if (op == 1) {
			int L, R;
			cin >> L >> R;
			int tmp = qpow(R - L + 1, mod - 2);
			if (L > 1) {
				addMatrix(1, L - 1, L, R, (1ll - tmp + mod) % mod);
				addMatrix(0, 0, 0, L - 1, 0);
			}
			if (R < n) {
				addMatrix(L, R, R + 1, n, (1ll - tmp + mod) % mod);
				addMatrix(0, 0, R + 1, n, 0);
			}
			addMatrix(L, R, L, R, (1 - 2ll * tmp % mod + mod) % mod);
			addMatrix(0, 0, L, R, tmp);
		}
		else {
			int l, r;
			cin >> l >> r;
			printf("%d\n", query(l - 1, r));
		}
	}
	return 0;
}
