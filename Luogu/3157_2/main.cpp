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
		int w, key, sz;
		node *l, *r;

		node(int _key)
		{
			sz = 1;
			key = _key;
			w = rand();
			l = r = nullptr;
		}
	};
	int size(node *u)
	{
		return u == nullptr ? 0 : u->sz;
	}
	void maintain(node *u)
	{
		u->sz = size(u->l) + size(u->r) + 1;
	}
	pair< node*, node* > split(node *u, int key)
	{
		if (u == nullptr)
			return make_pair(nullptr, nullptr);
		if (u->key <= key) {
			auto t = split(u->r, key);
			u->r = t.first;
			maintain(u);
			return make_pair(u, t.second);
		}
		else {
			auto t = split(u->l, key);
			u->l = t.second;
			maintain(u);
			return make_pair(t.first, u);
		}
	}
	node* merge(node *x, node *y)
	{
		if (x == nullptr) return y;
		if (y == nullptr) return x;
		if (x->w < y->w) {
			x->r = merge(x->r, y);
			maintain(x);
			return x;
		}
		else {
			y->l = merge(x, y->l);
			maintain(y);
			return y;
		}
	}
	void insert(node *&root, int key)
	{
		auto t = split(root, key - 1);
		root = merge(t.first, merge(new node(key), t.second));
	}
	void remove(node *&root, int key)
	{
		auto x = split(root, key - 1);
		auto y = split(x.second, key);
		y.first = merge(y.first->l, y.first->r);
		root = merge(x.first, merge(y.first, y.second));
	}
	int queryBigger(node *&root, int key)
	{
		int res = 0;
		node *u = root;
		while (u != nullptr) {
			if (u->key >= key) {
				res += size(u->r) + 1;
				u = u->l;
			}
			else u = u->r;
		}
		return res;
	}
	int querySmaller(node *&root, int key)
	{
		int res = 0;
		node *u = root;
		while (u != nullptr) {
			if (u->key <= key) {
				res += size(u->l) + 1;
				u = u->r;
			}
			else u = u->l;
		}
		return res;
	}
};

int n, m;
int a[N], pos[N];
LL ans;
FHQ::node *Pre[N], *Nex[N];

void addPre(int k, int val)
{
	for (int i = k; i <= n; i += lowbit(i))
		FHQ::insert(Pre[i], val);
}
void addNex(int k, int val)
{
	for (int i = k; i; i -= lowbit(i))
		FHQ::insert(Nex[i], val);
}
void delPre(int k, int val)
{
	for (int i = k; i <= n; i += lowbit(i))
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
	for (int i = k; i <= n; i += lowbit(i))
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
