#include <cstdio>
#include <climits>
#include <iostream>

using namespace std;

const int N = 5e4 + 10;

int n, m;
int a[N];

void build(int u = 1, int l = 1, int r = n)
{
	FHQ::insert(tr[u], INT_MAX);
	FHQ::insert(tr[u], -INT_MAX);
	for (int i = l; i <= r; ++i)
		FHQ::insert(tr[u], a[i]);

	if (l == r) return;

	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
}
int queryRank(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) return FHQ::query(tr[u], val);
	int mid = l + r >> 1;
	int res = 0;
	if (L <= mid)
		res += queryRank(L, R, val, u << 1, l, mid);
	if (R > mid)
		res += queryRank(L, R, val, u << 1 | 1, mid + 1, r);
	return res;
}
void queryNum(int L, int R, int k)
{
	int l = 0, r = 1e8;
	while (l < r) {
		if (queryRank(L, R, mid) < k - 1) l = mid + 1;
		r = mid;
	}
	return l;
}
void change(int pos, int val, int u = 1, int l = 1, int r = n)
{
	FHQ::insert(tr[u], val);
	FHQ::remove(tr[u], a[pos]);
	if (l == r) return;
	int mid = l + r >> 1;
	if (pos <= mid) change(pos, val, u << 1, l, mid);
	else change(pos, val, u << 1 | 1, mid + 1, r);
}
int queryPre(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) return FHQ::GetPre(tr[u], val);
	int mid = l + r >> 1;
	int res = -INT_MAX;
	if (L <= mid) res = max(res, queryPre(L, R, val, u << 1, l, mid));
	if (R > mid) res = max(res, queryPre(L, R, val, u << 1 | 1, mid + 1, r));
	return res;
}
int queryNex(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) return FHQ::GetNex(tr[u], val);
	int mid = l + r >> 1;
	int res = INT_MAX;
	if (L <= mid) res = min(res, queryNex(L, R, val, u << 1, l ,mid));
	if (R > mid) res = min(res, queryNex(L, R, val, u << 1 | 1, mid + 1, r));
	return res;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	build();
	for (int i = 1; i <= m; ++i) {
		int op; cin >> op;
		int l, r, pos, k, val;
		switch (op) {
			case 1:
				cin >> l >> r >> val;
				printf("%d\n", queryRank(l, r, val) + 1);
				break;
			case 2:
				cin >> l >> r >> k;
				printf("%d\n", queryNum(l, r, k));
				break;
			case 3:
				cin >> pos >> val;
				change(pos, val);
				a[pos] = val;
				break;
			case 4:
				cin >> l >> r >> val;
				printf("%d\n", queryPre(l, r, val));
				break;
			case 5:
				cin >> l >> r >> val;
				printf("%d\n", queryNex(l, r, val));
				break;
		}
	}
	return 0;
}
