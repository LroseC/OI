#include <cctype>
#include <cstdio>
#include <random>

using namespace std;

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
} read;

const int M = 5e5 + 10;

int m;
int rt[M];

namespace FHQ
{
	const int SIZE = 3e7 + 10;
	using PII = pair<int, int>;
	random_device srd;
	mt19937 rd(srd());

	struct node
	{
		int l, r;
		int cnt, sz, val, w;
	} tr[SIZE];
	int idx;

	int New(int val)
	{
		++idx;
		tr[idx].w = rd();
		tr[idx].val = val;
		tr[idx].sz = tr[idx].cnt = 1;
		return idx;
	}
	int clone(int u)
	{
		tr[++idx] = tr[u];
		return idx;
	}
	void maintain(int u)
	{
		tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + tr[u].cnt;
	}
	PII split(int u, int val)
	{
		PII t = make_pair(0, 0);
		if (!u) return t;
		u = clone(u);
		if (tr[u].val <= val) {
			t = split(tr[u].r, val);
			tr[u].r = t.first;
			t.first = u;
		}
		else {
			t = split(tr[u].l, val);
			tr[u].l = t.second;
			t.second = u;
		}
		maintain(u);
		return t;
	}
	int merge(int x, int y)
	{
		if (!x || !y) return x + y;
		if (tr[x].w > tr[y].w) {
			x = clone(x);
			tr[x].r = merge(tr[x].r, y);
			maintain(x);
			return x;
		}
		else {
			y = clone(y);
			tr[y].l = merge(x, tr[y].l);
			maintain(y);
			return y;
		}
	}
	int insert(int root, int x)
	{
		PII a = split(root, x - 1);
		PII b = split(a.second, x);
		if (b.first) {
			b.first = clone(b.first);
			++tr[b.first].cnt;
			maintain(b.first);
		}
		else b.first = New(x);
		return merge(a.first, merge(b.first, b.second));
	}
	int remove(int root, int x)
	{
		PII a = split(root, x - 1);
		PII b = split(a.second, x);
		if (b.first) {
			b.first = clone(b.first);
			--tr[b.first].cnt;
			maintain(b.first);
		}
		if (tr[b.first].cnt == 0) b.first = 0;
		return merge(a.first, merge(b.first, b.second));
	}
	int queryRank(int root, int x)
	{
		int res = 0, u = root;
		while (u && tr[u].val != x) {
			if (tr[u].val < x) {
				res += tr[u].cnt + tr[tr[u].l].sz;
				u = tr[u].r;
			}
			else u = tr[u].l;
		}
		if (u) res += tr[tr[u].l].sz;
		return res + 1;
	}
	int queryNum(int root, int rk)
	{
		int u = root;
		while (u) {
			if (rk <= tr[tr[u].l].sz)
				u = tr[u].l;
			else if (rk > tr[tr[u].l].sz + tr[u].cnt) {
				rk -= tr[tr[u].l].sz + tr[u].cnt;
				u = tr[u].r;
			}
			else return tr[u].val;
		}
	}
	int queryPre(int root, int x)
	{
		auto t = split(root, x - 1);
		int u = t.first;
		if (!u) return -(1ll << 31) + 1;
		while (tr[u].r)
			u = tr[u].r;
		return tr[u].val;
	}
	int queryNex(int root, int x)
	{
		auto t = split(root, x);
		int u = t.second;
		if (!u) return (1ll << 31) - 1;
		while (tr[u].l)
			u = tr[u].l;
		return tr[u].val;
	}
}

int main(void)
{
	read >> m;
	for (int i = 1; i <= m; ++i) {
		int v, opt, x;
		read >> v >> opt >> x;
		switch (opt) {
			case 1:
				rt[i] = FHQ::insert(rt[v], x);
				break;
			case 2:
				rt[i] = FHQ::remove(rt[v], x);
				break;
			case 3:
				printf("%d\n", FHQ::queryRank(rt[v], x));
				rt[i] = rt[v];
				break;
			case 4:
				printf("%d\n", FHQ::queryNum(rt[v], x));
				rt[i] = rt[v];
				break;
			case 5:
				printf("%d\n", FHQ::queryPre(rt[v], x));
				rt[i] = rt[v];
				break;
			case 6:
				printf("%d\n", FHQ::queryNex(rt[v], x));
				rt[i] = rt[v];
				break;
		}
	}
	return 0;
}
