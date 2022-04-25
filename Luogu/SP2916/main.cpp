#include <cctype>
#include <cstdio>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int N = 1e5 + 10;

int n, m;
int val[N], sum[N];

struct node
{
	int sum, sub, lsub, rsub, min, max;
} tr[N << 2];

node operator+(const node &x, const node &y)
{
	node res;
	res.sum = x.sum + y.sum;
	res.sub = std::max(x.sub, y.sub);
	res.sub = std::max(res.sub, x.rsub + y.lsub);
	res.lsub = std::max(x.lsub, x.sum + y.lsub);
	res.rsub = std::max(y.rsub, y.sum + x.rsub);
	res.min = std::min(x.min, y.min);
	res.max = std::max(x.max, y.max);
	return res;
}

void build(int u = 1, int l = 0, int r = n)
{
	if (l == r) {
		tr[u].sub = tr[u].sum = val[l];
		tr[u].lsub = tr[u].rsub = val[l];
		tr[u].min = tr[u].max = sum[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
node getNode(int L, int R, int u = 1, int l = 0, int r = n)
{
	if (L <= l && r <= R)
		return tr[u];
	int mid = l + r >> 1;
	if (R <= mid)
		return getNode(L, R, u << 1, l, mid);
	if (L > mid)
		return getNode(L, R, u << 1 | 1, mid + 1, r);
	return getNode(L, R, u << 1, l, mid) + getNode(L, R, u << 1 | 1, mid + 1, r);
}
int queryMax(int L, int R)
{
	auto t = getNode(L, R);
	return t.max;
}
int queryMin(int L, int R)
{
	auto t = getNode(L, R);
	return t.min;
}
int querySub(int L, int R)
{
	auto t = getNode(L, R);
	return t.sub;
}

int query(int l1, int r1, int l2, int r2)
{
	if (l2 > r2 || l1 > r1)
		return -2e9;
	return queryMax(l2, r2) - queryMin(l1 - 1, r1 - 1);
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		read >> n;
		for (int i = 1; i <= n; ++i) {
			read >> val[i];
			sum[i] = val[i] + sum[i - 1];
		}
		build();
		read >> m;
		while (m--) {
			int l1, r1, l2, r2;
			read >> l1 >> r1 >> l2 >> r2;
			if (r1 < l2)
				printf("%d\n", query(l1, r1, l2, r2));
			else {
				int res = -2e9;
				res = std::max(res, query(l1, l2 - 1, l2, r2));
				res = std::max(res, query(l1, r1, r1 + 1, r2));
				res = std::max(res, querySub(std::max(l1, l2), std::min(r1, r2)));
				printf("%d\n", res);
			}
		}
	}
	return 0;
}
