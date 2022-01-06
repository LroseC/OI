#include <cstdio>
#include <climits>
#include <iostream>

using namespace std;

const int N = 5e4 + 10;

int n, m;
int a[N];

namespace FHQ
{
	int idx;
	struct node
	{
		int l, r, key, w, cnt, sz;
	} tr[N << 6];

	void print(int u)
	{
		if (tr[u].l) print(tr[u].l);
		for (int i = 1; i <= tr[u].cnt; ++i)
			printf("%d ", tr[u].key);
		if (tr[u].r) print(tr[u].r);
	}
	int New(int val)
	{
		int u = ++idx;
		tr[u].w = rand();
		tr[u].l = tr[u].r = 0;
		tr[u].key = val;
		tr[u].cnt = tr[u].sz = 1;
		return u;
	}
	void maintain(int u)
	{
		tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + tr[u].cnt;
	}
	pair<int, int> split(int u, int key)
	{
		if (!u) return make_pair(0, 0);
		if (tr[u].key <= key) {
			auto t = split(tr[u].r, key);
			tr[u].r = t.first;
			maintain(u);
			return make_pair(u, t.second);
		}
		else {
			auto t = split(tr[u].l, key);
			tr[u].l = t.second;
			maintain(u);
			return make_pair(t.first, u);
		}
	}
	int merge(int x, int y)
	{
		if (!x || !y) return x + y;
		if (tr[x].w < tr[y].w) {
			tr[x].r = merge(tr[x].r, y);
			maintain(x);
			return x;
		}
		else {
			tr[y].l = merge(x, tr[y].l);
			maintain(y);
			return y;
		}
	}
	void insert(int &root, int val)
	{
		auto x = split(root, val - 1);
		auto y = split(x.second, val);
		if (y.first) ++tr[y.first].cnt;
		else y.first = New(val);
		root = merge(x.first, merge(y.first, y.second));
	}
	void remove(int &root, int val)
	{
		auto x = split(root, val - 1);
		auto y = split(x.second, val);
		--tr[y.first].cnt;
		if (tr[y.first].cnt)
			root = merge(x.first, merge(y.first, y.second));
		else
			root = merge(x.first, y.second);
	}
	int query(int &root, int val)
	{
		auto t = split(root, val - 1);
		int res = tr[t.first].sz;
		root = merge(t.first, t.second);
		return res;
	}
	int GetPre(int &root, int val)
	{
		auto t = split(root, val - 1);
		int u = t.first;
		while (tr[u].r) u = tr[u].r;
		root = merge(t.first, t.second);
		return tr[u].key;
	}
	int GetNex(int &root, int val)
	{
		auto t = split(root, val);
		int u = t.second;
		while (tr[u].l) u = tr[u].l;
		root = merge(t.first, t.second);
		return tr[u].key;
	}
};

int tr[N << 2];

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
	if (L <= l && r <= R) return FHQ::query(tr[u], val) - 1;
	int mid = l + r >> 1;
	int res = 0;
	if (L <= mid)
		res += queryRank(L, R, val, u << 1, l, mid);
	if (R > mid)
		res += queryRank(L, R, val, u << 1 | 1, mid + 1, r);
	return res;
}
int queryNum(int L, int R, int k)
{
	int l = 0, r = 1e8;
	while (l < r) {
		int mid = l + r >> 1;
		if (queryRank(L, R, mid + 1) < k) l = mid + 1;
		r = mid;
	}
	r = 1e8;
	while (l < r) {
		int mid = l + r >> 1;
		if (queryRank(L, R, mid) + 1 == k) l = mid;
		else r = mid - 1;
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
