#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;
inline int lowbit(int x) { return x & -x; }

struct DIII
{
	int id;
	int a, b, c;
	bool operator<(const DIII &other) const
	{
		if (a != other.a) return a < other.a;
		if (b != other.b) return b < other.b;
		return c < other.c;
	}
};

int n, k;
DIII q[N];
int ans[N];

namespace FHQ
{
	struct node
	{
		int l, r, w;
		int key, sz, cnt;
	} tr[N << 5];
	int idx;

	void maintain(int u)
	{
		tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + tr[u].cnt;
	}
	int New(int key)
	{
		int u = ++idx;
		tr[u].key = key;
		tr[u].w = rand();
		tr[u].l = tr[u].r = 0;
		tr[u].sz = tr[u].cnt = 1;
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
	void insert(int &root, int key)
	{
		auto x = split(root, key - 1);
		auto y = split(x.second, key);
		if (y.first) {
			++tr[y.first].cnt;
			maintain(y.first);
		}
		else y.first = New(key);
		root = merge(x.first, merge(y.first, y.second));
	}
	int query(int &root, int key)
	{
		int u = root;
		int res = 0;
		while (u) {
			if (tr[u].key <= key) {
				res += tr[tr[u].l].sz + tr[u].cnt;
				u = tr[u].r;
			}
			else u = tr[u].l;
		}
		return res;
	}
}

int tr[N << 1];

void add(int k, int val)
{
	for (int i = k; i < N << 1; i += lowbit(i))
		FHQ::insert(tr[i], val);
}
int query(int k, int val)
{
	int res = 0;
	for (int i = k; i; i -= lowbit(i))
		res += FHQ::query(tr[i], val);
	return res;
}

int main(void)
{
	srand(time(NULL));
	ios::sync_with_stdio(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		q[i].id = i;
		cin >> q[i].a >> q[i].b >> q[i].c;
	}
	sort(q + 1, q + 1 + n);
	for (int i = 1, j = 1; i <= n; ++j, i = j) {
		while (j < n && q[j + 1].a == q[j].a) ++j;
		for (int k = i; k <= j; ++k)
			add(q[k].b, q[k].c);
		for (int k = i; k <= j; ++k)
			++ans[query(q[k].b, q[k].c) - 1];
	}
	for (int i = 0; i < n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
