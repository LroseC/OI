#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;

struct node
{
	int l, r;
	int fa, sz;
};

int n, m, tick;

namespace SegmentTree
{
	int idx;
	int root[N << 2];
	node tr[N << 6];
	int build(int l, int r) 
	{
		int u = ++idx;
		if (l == r) {
			tr[u].fa = l;
			tr[u].sz = 1;
			return u;
		}
		int mid = l + r >> 1;
		tr[u].l = build(l, mid);
		tr[u].r = build(mid + 1, r);
		return u;
	}
	node find(int u, int k, int l, int r)
	{
		if (l == r) return tr[u];
		int mid = l + r >> 1;
		if (k <= mid) return find(tr[u].l, k, l, mid);
		else return find(tr[u].r, k, mid + 1, r);
	}
	int changefa(int k, int val, int pre, int l, int r)
	{
		int u = ++idx;
		tr[u] = tr[pre];
		if (l == r) {
			tr[u].fa = val;
			return u;
		}
		int mid = l + r >> 1;
		if (k <= mid) tr[u].l = changefa(k, val, tr[u].l, l, mid);
		else tr[u].r = changefa(k, val, tr[u].r, mid + 1, r);
		return u;
	}
	int changesz(int k, int val, int pre, int l, int r)
	{
		int u = ++idx;
		tr[u] = tr[pre];
		if (l == r) {
			tr[u].sz += val;
			return u;
		}
		int mid = l + r >> 1;
		if (k <= mid) tr[u].l = changesz(k, val, tr[u].l, l, mid);
		else tr[u].r = changesz(k, val, tr[u].r, mid + 1, r);
		return u;
	}
	void clone(int pre)
	{
		++tick;
		root[tick] = ++idx;
		tr[idx] = tr[pre];
	}
}

namespace UnionFind
{
	node find(int x)
	{
		auto X = SegmentTree::find(SegmentTree::root[tick], x, 1, n);
		while (X.fa != x) {
			x = X.fa;
			X = SegmentTree::find(SegmentTree::root[tick], x, 1, n);
		}
		return X;
	}
	void merge(int a, int b)
	{
		auto A = find(a), B = find(b);
		if (A.fa != B.fa) {
			if (A.sz > B.sz) swap(A, B);
			++tick;
			SegmentTree::root[tick] = SegmentTree::changefa(A.fa, B.fa, SegmentTree::root[tick - 1], 1, n);
			++tick;
			SegmentTree::root[tick] = SegmentTree::changesz(B.fa, A.sz, SegmentTree::root[tick - 1], 1, n);
		}
	}
}

int opclock[N << 1];

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	SegmentTree::root[tick] = SegmentTree::build(1, n);
	for (int i = 1; i <= m; ++i) {
		int op; cin >> op;
		if (op == 1) {
			int a, b; cin >> a >> b;
			UnionFind::merge(a, b);
		}
		else if (op == 2) {
			int k; cin >> k;
			SegmentTree::clone(SegmentTree::root[opclock[k]]);
		}
		else {
			int a, b; cin >> a >> b;
			auto A = UnionFind::find(a), B = UnionFind::find(b);
			puts(A.fa == B.fa ? "1" : "0");
		}
		opclock[i] = tick;
	}
	return 0;
}
