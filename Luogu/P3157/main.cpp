#include <cstdio>
#include <iostream>

using namespace std;

using LL = long long;
const int N = 1e5 + 10;
inline int lowbit(int x) { return x & -x; }

namespace FHQ
{
	struct node
	{
		int l, r, w;
		int key, sz;
	} tr[N << 6];
	int idx;

	int New(int key)
	{
		int u = ++idx;
		tr[u].sz = 1;
		tr[u].key = key;
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
	void insert(int &root, int key)
	{
		auto t = split(root, key - 1);
		root = merge(t.first, merge(New(key), t.second));
	}
	void remove(int &root, int key)
	{
		auto x = split(root, key - 1);
		auto y = split(x.second, key);
		y.first = merge(tr[y.first].l, tr[y.first].r);
		root = merge(x.first, merge(y.first, y.second));
	}
	int queryBigger(int &root, int key)
	{
		int res = 0;
		int u = root;
		while (u) {
			if (tr[u].key >= key) {
				res += tr[tr[u].r].sz + 1;
				u = tr[u].l;
			}
			else u = tr[u].r;
		}
		return res;
	}
	int querySmaller(int &root, int key)
	{
		int res = 0;
		int u = root;
		while (u) {
			if (tr[u].key <= key) {
				res += tr[tr[u].l].sz + 1;
				u = tr[u].r;
			}
			else u = tr[u].l;
		}
		return res;
	}
};

int n, m;
int a[N], pos[N];
LL ans;
int Pre[N], Nex[N];

void addPre(int k, int val)
{
	for (int i = k; i < N; i += lowbit(i))
		FHQ::insert(Pre[i], val);
}
void addNex(int k, int val)
{
	for (int i = k; i; i -= lowbit(i))
		FHQ::insert(Nex[i], val);
}
void delPre(int k, int val)
{
	for (int i = k; i < N; i += lowbit(i))
		FHQ::remove(Pre[i], val);
}
void delNex(int k, int val)
{
	for (int i = k; i; i -= lowbit(i))
		FHQ::remove(Nex[i], val);
}
LL queryPre(int k, int val)
{
	LL res = 0;
	for (int i = k; i; i -= lowbit(i))
		res += FHQ::queryBigger(Pre[i], val);
	return res;
}
LL queryNex(int k, int val)
{
	LL res = 0;
	for (int i = k; i < N; i += lowbit(i))
		res += FHQ::querySmaller(Nex[i], val);
	return res;
}
void add(int k, int val)
{
	addPre(k, val);
	addNex(k, val);
}
void del(int k, int val)
{
	delPre(k, val);
	delNex(k, val);
}
int query(int k)
{
	return queryPre(k - 1, a[k]) + queryNex(k + 1, a[k]);
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		pos[a[i]] = i;
		add(i, a[i]);
		ans += query(i);
	}
	for (int i = 1; i <= m; ++i) {
		printf("%lld\n", ans);
		int k;
		cin >> k;
		ans -= query(pos[k]);
		del(pos[k], k);
	}
	return 0;
}
