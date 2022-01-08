#include <cstdio>
#include <iostream>

using namespace std;

using LL = long long;
using PIL = pair<int, LL>;
const int N = 5e4 + 10, mod = 1e9 + 7;
inline int lowbit(int x) { return x & -x; }

PIL operator+(PIL a, PIL b)
{
	return make_pair(a.first + b.first, a.second + b.second);
}

int n, m;
int pos[N], page[N];
int Pre[N], Nex[N];

namespace FHQ
{
	struct node
	{
		int l, r, w;
		int key, val, cnt, sz;
		LL sum;
	} tr[N << 5];
	int idx;

	void maintain(int u)
	{
		tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
		tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum + 1ll * tr[u].val;
	}
	int New(int key, int val)
	{
		int u = ++idx;
		tr[u].key = key;
		tr[u].w = rand();
		tr[u].l = tr[u].r = 0;
		tr[u].cnt = tr[u].sz = 1;
		tr[u].val = tr[u].sum = val;
		return u;
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
	void insert(int &root, int key, int val)
	{
		auto x = split(root, key - 1);
		auto y = split(x.second, key);
		if (y.first) {
			++tr[y.first].cnt;
			maintain(y.first);
		}
		else y.first = New(key, val);
		root = merge(x.first, merge(y.first, y.second));
	}
	void remove(int &root, int key, int val)
	{
		auto x = split(root, key - 1);
		auto y = split(x.second, key);
		--tr[y.first].cnt;
		if (tr[y.first].cnt)
			maintain(y.first);
		else y.first = 0;
		root = merge(x.first, merge(y.first, y.second));
	}
	PIL queryBigger(int &root, int key)
	{
		PIL res = make_pair(0, 0ll);
		int u = root;
		while (u) {
			if (tr[u].key >= key) {
				res.first += tr[tr[u].r].sz + 1;
				res.second += tr[tr[u].r].sum + tr[u].val;
				u = tr[u].l;
			}
			else u = tr[u].r;
		}
		return res;
	}
	PIL querySmaller(int &root, int key)
	{
		PIL res = make_pair(0, 0ll);
		int u = root;
		while (u) {
			if (tr[u].key <= key) {
				res.first += tr[tr[u].l].sz + 1;
				res.second += tr[tr[u].l].sum + tr[u].val;
				u = tr[u].r;
			}
			else u = tr[u].l;
		}
		return res;
	}
}

void addPre(int k, int val)
{
	for (int i = k; i <= n; i += lowbit(i)) {
		if (val == 1)
			FHQ::insert(Pre[i], pos[k], page[k]);
		if (val == -1)
			FHQ::remove(Pre[i], pos[k], page[k]);
	}
}
void addNex(int k, int val)
{
	for (int i = k; i; i -= lowbit(i)) {
		if (val == 1)
			FHQ::insert(Nex[i], pos[k], page[k]);
		if (val == -1)
			FHQ::remove(Nex[i], pos[k], page[k]);
	}
}
PIL queryPre(int k, int pos)
{
	PIL res = make_pair(0, 0ll);
	for (int i = k; i; i -= lowbit(i))
		res = (res + FHQ::queryBigger(Pre[i], pos));
	return res;
}
PIL queryNex(int k, int pos)
{
	PIL res = make_pair(0, 0ll);
	for (int i = k; i <= n; i += lowbit(i))
		res = (res + FHQ::querySmaller(Nex[i], pos));
	return res;
}
void add(int i, int val)
{
	addPre(i, val);
	addNex(i, val);
}
LL query(int i)
{
	LL res = 0;
	auto qPre = queryPre(i - 1, pos[i]);
	auto qNex = queryNex(i + 1, pos[i]);
	res += 1ll * qPre.first * page[i] + qPre.second;
	res += 1ll * qNex.first * page[i] + qNex.second;
	return res;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	LL ans = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> pos[i] >> page[i];
		add(i, 1);
		ans = (ans + query(i));
	}

	for (int i = 1; i <= m; ++i) {
		int x, y;
		cin >> x >> y;
		auto t = make_pair(pos[x], page[x]);
		ans -= query(x);
		add(x, -1);
		pos[x] = pos[y];
		page[x] = page[y];
		add(x, 1);
		ans += query(x);

		ans -= query(y);
		add(y, -1);
		pos[y] = t.first;
		page[y] = t.second;
		add(y, 1);
		ans += query(y);
		printf("%lld\n", ans % mod);
	}
	return 0;
}
