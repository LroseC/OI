#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n, m, q;
int A[N];

struct Operation
{
	int op, l, r;
} operation[N];

struct node
{
	int len, sum, chg;
} tr[N << 3];

void chg(int u, int val)
{
	tr[u].chg = val;
	tr[u].sum = tr[u].len * val;
}
void maintain(int u)
{
	tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}
void spread(int u)
{
	if (tr[u].chg != -1) {
		if (tr[u].len != 1) {
			chg(u << 1, tr[u].chg);
			chg(u << 1 | 1, tr[u].chg);
		}
		tr[u].chg = -1;
	}
}
void build(int key, int u = 1, int l = 1, int r = n)
{
	tr[u].chg = -1;
	tr[u].len = r - l + 1;
	if (l == r) {
		tr[u].sum = A[l] > key;
		return;
	}
	int mid = l + r >> 1;
	build(key, u << 1, l, mid);
	build(key, u << 1 | 1, mid + 1, r);
	maintain(u);
}
void change(int L, int R, int val, int u = 1, int l = 1, int r = n)
{
	if (L > R) return;
	if (L <= l && r <= R) {
		chg(u, val);
		return;
	}
	spread(u);
	int mid = l + r >> 1;
	if (L <= mid)
		change(L, R, val, u << 1, l, mid);
	if (R > mid)
		change(L, R, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R)
		return tr[u].sum;
	spread(u);
	int mid = l + r >> 1;
	int res = 0;
	if (L <= mid)
		res += query(L, R, u << 1, l, mid);
	if (R > mid)
		res += query(L, R, u << 1 | 1, mid + 1, r);
	return res;
}

bool check(int x)
{
	build(x);
	for (int i = 1; i <= m; ++i) {
		int onecnt = query(operation[i].l, operation[i].r);
		int zerocnt = operation[i].r - operation[i].l + 1 - onecnt;
		if (operation[i].op == 0) {
			change(operation[i].l, operation[i].l + zerocnt - 1, 0);
			change(operation[i].r - onecnt + 1, operation[i].r, 1);
		}
		else {
			change(operation[i].l, operation[i].l + onecnt - 1, 1);
			change(operation[i].r - zerocnt + 1, operation[i].r, 0);
		}
	}
	return query(q, q) == 0;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> A[i];
	for (int i = 1; i <= m; ++i)
		cin >> operation[i].op >> operation[i].l >> operation[i].r;
	cin >> q;

	int l = 1, r = n;
	while (l < r) {
		int mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}
