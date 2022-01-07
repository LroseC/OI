#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

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
} cin;

int n, m;
int a[N];
int _tick;

namespace FHQ
{
	int idx;
	struct node
	{
		int l, r, key, w, sz;
	} tr[N * 30];

	int New(int val)
	{
		int u = ++idx;
		tr[u].sz = 1;
		tr[u].key = val;
		tr[u].w = rand();
		tr[u].l = tr[u].r = 0;
		return u;
	}
	void maintain(int u)
	{
		tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
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
		auto x = split(root, val);
		root = merge(x.first, merge(New(val), x.second));
	}
	void remove(int &root, int val)
	{
		auto x = split(root, val - 1);
		auto y = split(x.second, val);
		y.first = merge(tr[y.first].l, tr[y.first].r);
		root = merge(x.first, merge(y.first, y.second));
	}
	int query(int &root, int val)
	{
		int u = root;
		int res = 0;
		while (u) {
			if (tr[u].key < val) {
				res += tr[tr[u].l].sz + 1;
				u = tr[u].r;
			}
			else
				u = tr[u].l;
		}
		return res;
	}
	int GetPre(int &root, int val)
	{
		int u = root;
		int res = -INT_MAX;
		while (u) {
			if (tr[u].key >= val)
				u = tr[u].l;
			else {
				res = max(res, tr[u].key);
				u = tr[u].r;
			}
		}
		return res;
	}
	int GetNex(int &root, int val)
	{
		int u = root;
		int res = INT_MAX;
		while (u) {
			if (tr[u].key <= val)
				u = tr[u].r;
			else {
				res = min(res, tr[u].key);
				u = tr[u].l;
			}
		}
		return res;
	}
};

int tr[N << 3];

void build(int u = 1, int l = 1, int r = n)
{
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
int queryNum(int L, int R, int k)
{
	int l = 0, r = 1e8;
	while (l < r) {
		int mid = l + r >> 1;
		if (queryRank(L, R, mid + 1) < k) l = mid + 1;
		else r = mid;
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
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	build();
	for (_tick = 1; _tick <= m; ++_tick) {
		int op; cin >> op;
		int l, r, pos, k, val;
//		printf("tick = %d, op = %d\n", _tick, op);
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
