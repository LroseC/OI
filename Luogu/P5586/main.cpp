#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 3e5 + 10, mod = 1e9 + 7;

int n, m, idx;
int cnt, tmp[N], root;

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

struct node
{
	int l, r, val, sz, sum;
	int	add, chg; bool rev;
} tr[(int)4e6 + 10];

int New(int val)
{
	int u = ++idx;
	tr[u].sz = 1;
	tr[u].chg = mod;
	tr[u].l = tr[u].r = 0;
	tr[u].val = tr[u].sum = val;
	tr[u].add = tr[u].rev = 0;
	return u;
}
int clone(int pre)
{
	++idx; tr[idx] = tr[pre];
	return idx;
}
void rev(int &u)
{
	u = clone(u);
	tr[u].rev ^= 1;
	swap(tr[u].l, tr[u].r);
}
void chg(int &u, int val)
{
	u = clone(u);
	tr[u].add = 0;
	tr[u].val = tr[u].chg = val;
	tr[u].sum = 1ll * val * tr[u].sz % mod;
}
void add(int &u, int val)
{
	u = clone(u);
	tr[u].add = (tr[u].add + val) % mod;
	tr[u].val = (tr[u].val + val) % mod;
	tr[u].sum = (tr[u].sum + 1ll * val * tr[u].sz % mod) % mod;
}
void maintain(int u)
{
	tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
	tr[u].sum = (0ll + tr[tr[u].l].sum + tr[tr[u].r].sum + tr[u].val) % mod;
}
void spread(int u)
{
	if (tr[u].chg != mod) {
		if (tr[u].l) chg(tr[u].l, tr[u].chg);
		if (tr[u].r) chg(tr[u].r, tr[u].chg);
		tr[u].chg = mod;
	}
	if (tr[u].add) {
		if (tr[u].l) add(tr[u].l, tr[u].add);
		if (tr[u].r) add(tr[u].r, tr[u].add);
		tr[u].add = 0;
	}
	if (tr[u].rev) {
		if (tr[u].l) rev(tr[u].l);
		if (tr[u].r) rev(tr[u].r);
		tr[u].rev = 0;
	}
}
pair<int, int> split(int u, int k)
{
	if (!u) return make_pair(0, 0);
	spread(u);
	u = clone(u);
	if (tr[tr[u].l].sz >= k) {
		auto t = split(tr[u].l, k);
		tr[u].l = t.second;
		maintain(u);
		return make_pair(t.first, u);
	}
	else {
		auto t = split(tr[u].r, k - tr[tr[u].l].sz - 1);
		tr[u].r = t.first;
		maintain(u);
		return make_pair(u, t.second);
	}
}
int merge(int x, int y)
{
	if (!x || !y) return x + y;
	if (rand() % (tr[x].sz + tr[y].sz) < tr[x].sz) { //merge y -> x;
		spread(x);
		x = clone(x);
		tr[x].r = merge(tr[x].r, y);
		maintain(x);
		return x;
	}
	else {
		spread(y);
		y = clone(y);
		tr[y].l = merge(x, tr[y].l);
		maintain(y);
		return y;
	}
}
void build(int &u, int l, int r)
{
	if (l > r) return;
	int mid = l + r >> 1;
	u = New(tmp[mid]);
	build(tr[u].l, l, mid - 1);
	build(tr[u].r, mid + 1, r);
	maintain(u);
}
void query(int l, int r, int &ans)
{
	auto x = split(root, l - 1);
	auto y = split(x.second, r - l + 1);
	ans = tr[y.first].sum;
	root = merge(x.first, merge(y.first, y.second));
}
void change(int l, int r, int val)
{
	auto x = split(root, l - 1);
	auto y = split(x.second, r - l + 1);
	chg(y.first, val);
	root = merge(x.first, merge(y.first, y.second));
}
void add(int l, int r, int val)
{
	auto x = split(root, l - 1);
	auto y = split(x.second, r - l + 1);
	add(y.first, val);
	root = merge(x.first, merge(y.first, y.second));
}
void reverse(int l, int r)
{
	auto x = split(root, l - 1);
	auto y = split(x.second, r - l + 1);
	rev(y.first);
	root = merge(x.first, merge(y.first, y.second));
}
void copy(int l1, int r1, int l2, int r2)
{
	bool flag = 0;
	if (l1 > l2) {
		swap(l1, l2);
		swap(r1, r2);
		flag = 1;
	}
	auto a = split(root, l1 - 1);
	auto b = split(a.second, r1 - l1 + 1);
	auto c = split(b.second, l2 - r1 - 1);
	auto d = split(c.second, r2 - l2 + 1);
	if (!flag) d.first = clone(b.first);
	else b.first = clone(d.first);
	root = merge(a.first, merge(b.first, merge(c.first, merge(d.first, d.second))));
}
void swap(int l1, int r1, int l2, int r2)
{
	if (l1 > l2) {
		swap(l1, l2);
		swap(r1, r2);
	}
	auto a = split(root, l1 - 1);
	auto b = split(a.second, r1 - l1 + 1);
	auto c = split(b.second, l2 - r1 - 1);
	auto d = split(c.second, r2 - l2 + 1);
	swap(b.first, d.first);
	root = merge(a.first, merge(b.first, merge(c.first, merge(d.first, d.second))));
}

void dfs(int u)
{
	spread(u);
	if (tr[u].l) dfs(tr[u].l);
	tmp[++cnt] = tr[u].val;
	if (tr[u].r) dfs(tr[u].r);
}

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> tmp[i];
	build(root, 1, n);
	int lastans = 0;
	for (int i = 1; i <= m; ++i) {
		int op; cin >> op;
		int l, r, l1, r1, l2, r2, val;
		switch (op) {
			case 1:
				cin >> l >> r;
				l ^= lastans, r ^= lastans;
				query(l, r, lastans);
				printf("%d\n", lastans);
				break;
			case 2:
				cin >> l >> r >> val;
				l ^= lastans, r ^= lastans, val ^= lastans;
				change(l, r, val);
				break;
			case 3:
				cin >> l >> r >> val;
				l ^= lastans, r ^= lastans, val ^= lastans;
				add(l, r, val);
				break;
			case 4:
				cin >> l1 >> r1 >> l2 >> r2;
				l1 ^= lastans, r1 ^= lastans, l2 ^= lastans, r2 ^= lastans;
				copy(l1, r1, l2, r2);
				break;
			case 5:
				cin >> l1 >> r1 >> l2 >> r2;
				l1 ^= lastans, r1 ^= lastans, l2 ^= lastans, r2 ^= lastans;
				swap(l1, r1, l2, r2);
				break;
			case 6:
				cin >> l >> r;
				l ^= lastans, r ^= lastans;
				reverse(l, r);
				break;
		}
		if (idx > 3200000) {
			cnt = 0;
			dfs(root);
			idx = 0;
			build(root, 1, n);
		}
	}
	cnt = 0;
	dfs(root);
	for (int i = 1; i <= n; ++i) printf("%d ", tmp[i]);
	puts("");
	return 0;
}
