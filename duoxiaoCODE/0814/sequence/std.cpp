#include <bits/stdc++.h>
#define ls (ro << 1)
#define rs ((ro << 1) | 1)
#define mid ((l + r) >> 1)
using namespace std;
int const N = 2e5 + 10;
struct stu1 {
	int Or, And, mx, tag;
} t[N * 4];
int n, q, a[N];
inline void pushup(int ro) {
	t[ro].mx = max(t[ls].mx, t[rs].mx);
	t[ro].Or = t[ls].Or | t[rs].Or;
	t[ro].And = t[ls].And & t[rs].And;
}
inline void change(int ro, int v) {
	t[ro].Or += v;
	t[ro].And += v;
	t[ro].mx += v;
	t[ro].tag += v;
}
inline void spread(int ro) {
	if (t[ro].tag) {
		change(ls, t[ro].tag);
		change(rs, t[ro].tag);
		t[ro].tag = 0;
	}
}
void build(int ro, int l, int r) {
	if (l == r) {
		t[ro].Or = t[ro].And = t[ro].mx = a[l];
		return;
	}
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(ro);
}
void xg1(int ro, int l, int r, int L, int R, int v) {
	if (L <= l && r <= R && (((t[ro].Or & v) - t[ro].Or) == ((t[ro].And & v) - t[ro].And))) {
		change(ro, (t[ro].Or & v) - t[ro].Or);
		return;
	}
	spread(ro);
	if (L <= mid)
		xg1(ls, l, mid, L, R, v);
	if (R > mid)
		xg1(rs, mid + 1, r, L, R, v);
	pushup(ro);
}
void xg2(int ro, int l, int r, int L, int R, int v) {
	if (L <= l && r <= R && (((t[ro].Or | v) - t[ro].Or) == ((t[ro].And | v) - t[ro].And))) {
		change(ro, (t[ro].Or | v) - t[ro].Or);
		return;
	}
	spread(ro);
	if (L <= mid)
		xg2(ls, l, mid, L, R, v);
	if (R > mid)
		xg2(rs, mid + 1, r, L, R, v);
	pushup(ro);
}
int cx(int ro, int l, int r, int L, int R) {
	if (L <= l && r <= R)
		return t[ro].mx;
	spread(ro);
	int res = 0;
	if (L <= mid)
		res = max(res, cx(ls, l, mid, L, R));
	if (R > mid)
		res = max(res, cx(rs, mid + 1, r, L, R));
	return res;
}
int main() {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	build(1, 1, n);
	int op, l, r, x;
	while (q) {
		q--;
		scanf("%d%d%d", &op, &l, &r);
		if (op != 3)
			scanf("%d", &x);
		if (op == 1)
			xg1(1, 1, n, l, r, x);
		if (op == 2)
			xg2(1, 1, n, l, r, x);
		if (op == 3)
			printf("%d\n", cx(1, 1, n, l, r));
	}
}
