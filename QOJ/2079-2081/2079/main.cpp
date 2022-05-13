#include <cctype>
#include <cstdio>
#include <climits>
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
int a[N];

struct floor
{
	int val;
	floor(int x) { val = x; }
	floor operator/(const floor &other) const
	{
		if (val < 0 && val % other.val)
			return val / other.val - 1;
		return val / other.val;
	}
};
struct segNode
{
	i64 sum;
	int min, max, addTag;

	segNode(void)
	{
		min = INT_MAX;
		max = INT_MIN;
		sum = addTag = 0;
	}
} tr[N << 2];
segNode operator+(const segNode &a, const segNode &b)
{
	segNode res;
	res.sum = a.sum + b.sum;
	res.min = std::min(a.min, b.min);
	res.max = std::max(a.max, b.max);
	return res;
}

void nodeAdd(int u, int l, int r, int v)
{
	tr[u].min += v;
	tr[u].max += v;
	tr[u].addTag += v;
	tr[u].sum += 1ll * (r - l + 1) * v;
}
void spread(int u, int l, int r)
{
	if (tr[u].addTag) {
		int mid = l + r >> 1;
		nodeAdd(u << 1, l, mid, tr[u].addTag);
		nodeAdd(u << 1 | 1, mid + 1, r, tr[u].addTag);
		tr[u].addTag = 0;
	}
}
void build(int u = 1, int l = 0, int r = n - 1)
{
	if (l == r) {
		tr[u].sum = tr[u].min = tr[u].max = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void segAdd(int L, int R, int v, int u = 1, int l = 0, int r = n - 1)
{
	if (L <= l && r <= R) {
		nodeAdd(u, l, r, v);
		return;
	}
	int mid = l + r >> 1;
	spread(u, l, r);
	if (L <= mid)
		segAdd(L, R, v, u << 1, l, mid);
	if (R > mid)
		segAdd(L, R, v, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void segDev(int L, int R, int v, int u = 1, int l = 0, int r = n - 1)
{
	if (l == r) {
		int val = ((floor)tr[u].sum / v).val;
		tr[u].sum = tr[u].max = tr[u].min = val;
		return;
	}
	if (L <= l && r <= R) {
		int delMax = tr[u].max - ((floor)tr[u].max / v).val;
		int delMin = tr[u].min - ((floor)tr[u].min / v).val;
		if (delMax == delMin) {
			nodeAdd(u, l, r, -delMax);
			return;
		}
		int mid = l + r >> 1;
		spread(u, l, r);
		segDev(L, R, v, u << 1, l, mid);
		segDev(L, R, v, u << 1 | 1, mid + 1, r);
		tr[u] = tr[u << 1] + tr[u << 1 | 1];
		return;
	}
	int mid = l + r >> 1;
	spread(u, l, r);
	if (L <= mid)
		segDev(L, R, v, u << 1, l, mid);
	if (R > mid)
		segDev(L, R, v, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
segNode query(int L, int R, int u = 1, int l = 0, int r = n - 1)
{
	if (L <= l && r <= R)
		return tr[u];
	int mid = l + r >> 1;
	spread(u, l, r);
	segNode res;
	if (L <= mid)
		res = res + query(L, R, u << 1, l, mid);
	if (R > mid)
		res = res + query(L, R, u << 1 | 1, mid + 1, r);
	return res;
}

int main(void)
{
	read >> n >> m;
	for (int i = 0; i < n; ++i)
		read >> a[i];
	build();
	while (m--) {
		int op, l, r, v;
		read >> op >> l >> r;
		if (op == 1) {
			read >> v;
			segAdd(l, r, v);
		}
		if (op == 2) {
			read >> v;
			segDev(l, r, v);
		}
		if (op == 3)
			printf("%d\n", query(l, r).min);
		if (op == 4)
			printf("%lld\n", query(l, r).sum);
	}
	return 0;
}
