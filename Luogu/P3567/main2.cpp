#include <cctype>
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 5e5 + 10;

int n, m, idx;
int A[N];
int root[N];
struct node
{
	int l, r, sum;
}tr[N << 5];

int add(int prev, int val, int l = 1, int r = n)
{
	int u = ++idx;
	tr[u] = tr[prev];
	if (l == r) {
		++tr[u].sum;
		return u;
	}
	int mid = l + r >> 1;
	if (val <= mid) tr[u].l = add(tr[u].l, val, l, mid);
	else tr[u].r = add(tr[u].r, val, mid + 1, r);
	tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum;
	return u;
}
int query(int u1, int u2, int S, int l = 1, int r = n)
{
	if (l == r) return l;
	int mid = l + r >> 1;
	if (tr[tr[u2].l].sum - tr[tr[u1].l].sum > S / 2.0) return query(tr[u1].l, tr[u2].l, S, l, mid);
	else if (tr[tr[u2].r].sum - tr[tr[u1].r].sum > S / 2.0) return query(tr[u1].r, tr[u2].r, S, mid + 1, r);
	else return 0;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> A[i];
	for (int i = 0; i <= n; ++i) root[i] = add(root[i - 1], A[i]);
	for (int i = 1; i <= m; ++i) {
		int left_bound, right_bound; cin >> left_bound >> right_bound;
		printf("%d\n", query(root[left_bound - 1], root[right_bound], right_bound - left_bound + 1));
	}
	return 0;
}
