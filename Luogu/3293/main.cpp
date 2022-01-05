#include <cstdio>
#include <assert.h>
#include <iostream>

using namespace std;

const int N = 5e5 + 10;

int n, m;
int A[N];

namespace SGT
{
	int idx;
	struct node
	{
		int l, r, sum;
	} tr[N * 20];
	int root[N];
	int insert(int k, int pre, int l = 0, int r = 1e5 - 1)
	{
		int u = ++idx;
		tr[u] = tr[pre];
		if (l == r) {
			++tr[u].sum;
			return u;
		}
		int mid = l + r >> 1;
		if (k <= mid) tr[u].l = insert(k, tr[u].l, l, mid);
		else tr[u].r = insert(k, tr[u].r, mid + 1, r);
		tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum;
		return u;
	}
	int query(int u1, int u2, int L, int R, int l = 0, int r = 1e5 - 1)
	{
		if (L <= l && r <= R) {
			return tr[u2].sum - tr[u1].sum;
		}
		int mid = l + r >> 1;
		int res = 0;
		if (L <= mid) res += query(tr[u1].l, tr[u2].l, L, R, l, mid);
		if (R > mid) res += query(tr[u1].r, tr[u2].r, L, R, mid + 1, r);
		return res;
	}
}

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> A[i];
		SGT::root[i] = SGT::insert(A[i], SGT::root[i - 1]);
	}
	for (int i = 1; i <= m; ++i) {
		int B, X, l, r; cin >> B >> X >> l >> r;
		int res = 0;
		for (int k = 17; k >= 0; --k) {
			if (B >> k & 1) {
				if (SGT::query(SGT::root[l - 1], SGT::root[r], max(0, res - X), min(99999, res - X + (1 << k) - 1))) {
				}
				else
					res |= 1 << k;
			}
			else {
				if (SGT::query(SGT::root[l - 1], SGT::root[r], max(0, res - X + (1 << k)), min(99999, res - X + (1 << k + 1) - 1)))
					res |= 1 << k;
			}
		}
		printf("%d\n", res ^ B);
	}
	return 0;
}
