#include <cstdio>
#include <iostream>

using namespace std;

const int N = 2e5 + 10;
using LL = long long;

int m, idx;
int root[N];

struct node
{
	int l, r, val, w, sz, rev;
	LL sum;
} tr[N << 7];

int New(int val)
{
	++idx; tr[idx].sz = 1;
	tr[idx].w = rand();
	tr[idx].l = tr[idx].r = 0;
	tr[idx].val = tr[idx].sum = val;
	return idx;
}
int clone(int pre)
{
	++idx; tr[idx] = tr[pre];
	return idx;
}
int rev(int u)
{
	u = clone(u);
	swap(tr[u].l, tr[u].r);
	tr[u].rev ^= 1;
	return u;
}
void maintain(int u)
{
	tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
	tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum + tr[u].val;
}
void spread(int u)
{
	if (tr[u].rev) {
		if (tr[u].l) tr[u].l = rev(tr[u].l);
		if (tr[u].r) tr[u].r = rev(tr[u].r);
		tr[u].rev = 0;
	}
}
pair<int, int> split(int u, int k)
{
	if (!u) return make_pair(0, 0);
	u = clone(u);
	spread(u);
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
	if (tr[x].w > tr[y].w) {
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
int insert(int u, int k, int val)
{
	auto t = split(u, k);
	return merge(t.first, merge(New(val), t.second));
}
int remove(int u, int k)
{
	auto x = split(u, k - 1);
	auto y = split(x.second, 1);
	return merge(x.first, y.second);
}
int reverse(int u, int l, int r)
{
	auto x = split(u, l - 1);
	auto y = split(x.second, r - l + 1);
	y.first = rev(y.first);
	return merge(x.first, merge(y.first, y.second));
}
int query(int u, int l, int r, LL &ans)
{
	auto x = split(u, l - 1);
	auto y = split(x.second, r - l + 1);
	ans = tr[y.first].sum;
	return merge(x.first, merge(y.first, y.second));
}

signed main(void)
{
	ios::sync_with_stdio(0);
	cin >> m;
	LL lastans = 0;
	for (int i = 1; i <= m; ++i) {
		LL version, opt, p, x, l, r;
		cin >> version >> opt;
		switch (opt) {
			case 1:
				cin >> p >> x;
				p ^= lastans, x ^= lastans;
				root[i] = insert(root[version], p, x); // p -> key, x -> val;
				break;
			case 2:
				cin >> p;
				p ^= lastans;
				root[i] = remove(root[version], p);
				break;
			case 3:
				cin >> l >> r;
				l ^= lastans, r ^= lastans;
				root[i] = reverse(root[version], l, r);
				break;
			case 4:
				cin >> l >> r;
				l ^= lastans, r ^= lastans;
				root[i] = query(root[version], l, r, lastans);
				printf("%lld\n", lastans);
				break;
		}
	}
	return 0;
}
