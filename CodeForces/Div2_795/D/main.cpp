#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 2e5 + 10;

struct node
{
	i64 min, max;
	friend node operator+(const node &a, const node &b)
	{
		node res;
		res.min = std::min(a.min, b.min);
		res.max = std::max(a.max, b.max);
		return res;
	}
};

int n;
int stk[N], top;
int a[N], nex[N], pre[N];
i64 sum[N];
node tr[N << 2];

void build(int u = 1, int l = 0, int r = n)
{
	if (l == r) {
		tr[u].min = tr[u].max = sum[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
node query(int L, int R, int u = 1, int l = 0, int r = n)
{
	if (L <= l && r <= R)
		return tr[u];
	int mid = l + r >> 1;
	if (L <= mid && R > mid)
		return query(L, R, u << 1, l, mid) + query(L, R, u << 1 | 1, mid + 1, r);
	else if (L <= mid)
		return query(L, R, u << 1, l, mid);
	else
		return query(L, R, u << 1 | 1, mid + 1, r);
}
i64 queryMin(int L, int R)
{ return query(L, R).min; }
i64 queryMax(int L, int R)
{ return query(L, R).max; }

void work(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	build();
	top = 0;
	for (int i = 1; i <= n; ++i) {
		while (top && a[i] >= a[stk[top]]) --top;
		pre[i] = stk[top] + 1;
		stk[++top] = i;
	}
	top = 0;
	for (int i = n; i >= 1; --i) {
		while (top && a[i] >= a[stk[top]]) --top;
		nex[i] = stk[top] == 0 ? n : stk[top] - 1;
		stk[++top] = i;
	}
	bool fail = 0;
	for (int i = 1; i <= n; ++i) {
		if (queryMax(i, nex[i]) - queryMin(pre[i] - 1, i - 1) > a[i])
			fail = 1;
	}
	puts(fail ? "NO" : "YES");
}

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
