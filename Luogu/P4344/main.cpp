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
const int N = 2e5 + 10;

struct segNode
{
	int tag;
	int full;
	int sum0, sum1;
	int sub, lsub, rsub;
};
segNode operator+(const segNode &a, const segNode &b)
{
	segNode res;
	res.tag = -1;
	if (a.full == b.full)
		res.full = a.full;
	else res.full = -1;
	res.sum0 = a.sum0 + b.sum0;
	res.sum1 = a.sum1 + b.sum1;
	res.sub = std::max(a.sub, b.sub);
	res.sub = std::max(res.sub, a.rsub + b.lsub);
	res.lsub = a.lsub;
	if (a.full == 0)
		res.lsub = std::max(res.lsub, a.sub + b.lsub);
	res.rsub = b.rsub;
	if (b.full == 0)
		res.rsub = std::max(res.rsub, a.rsub + b.sub);
	return res;
}

int n, m;
segNode tr[N << 2];

void coverNode(int v, int u, int l, int r)
{
	tr[u].tag = v;
	tr[u].full = v;
	tr[u].sum0 = tr[u].sum1 = 0;
	if (v == 0) {
		tr[u].sum0 = (r - l + 1);
		tr[u].sub = tr[u].lsub = tr[u].rsub = r - l + 1;
	}
	else {
		tr[u].sum1 = (r - l + 1);
		tr[u].sub = tr[u].lsub = tr[u].rsub = 0;
	}
}
void spread(int u, int l, int r)
{
	if (tr[u].tag != -1) {
		int mid = l + r >> 1;
		coverNode(tr[u].tag, u << 1, l, mid);
		coverNode(tr[u].tag, u << 1 | 1, mid + 1, r);
		tr[u].tag = -1;
	}
}
void build(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		tr[u].tag = -1;
		tr[u].full = 1;
		tr[u].sum0 = 0;
		tr[u].sum1 = 1;
		tr[u].sub = tr[u].lsub = tr[u].rsub = 0;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
segNode query(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R)
		return tr[u];
	int mid = l + r >> 1;
	spread(u, l, r);
	if (L <= mid && R > mid)
		return query(L, R, u << 1, l, mid) + query(L, R, u << 1 | 1, mid + 1, r);
	if (L <= mid)
		return query(L, R, u << 1, l, mid);
	if (R > mid)
		return query(L, R, u << 1 | 1, mid + 1, r);
}
void cover(int v, int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		coverNode(v, u, l, r);
		return;
	}
	int mid = l + r >> 1;
	spread(u, l, r);
	if (L <= mid)
		cover(v, L, R, u << 1, l, mid);
	if (R > mid)
		cover(v, L, R, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
int queryCnt(int L, int R)
{ return query(L, R).sum1; }
int queryGap(int L, int R)
{ return query(L, R).sub; }
int binarySearch(int L, int R, int cnt)
{
	if (L > 1)
		cnt += query(1, L - 1).sum0;
	int u = 1, l = 1, r = n;
	while (l != r) {
		int mid = l + r >> 1;
		spread(u, l, r);
		if (tr[u << 1].sum0 >= cnt)
			u = u << 1, r = mid;
		else {
			cnt -= tr[u << 1].sum0;
			u = u << 1 | 1, l = mid + 1;
		}
	}
	return std::min(l, R);
}

int main(void)
{
	read >> n >> m;
	build();
	int op, l, r, l2, r2;
	while (m--) {
		read >> op;
		if (op == 0) {
			read >> l >> r;
			cover(0, l, r);
		}
		else if (op == 1) {
			read >> l >> r >> l2 >> r2;
			int cnt = queryCnt(l, r);
			cover(0, l, r);
			int r3 = binarySearch(l2, r2, cnt);
			cover(1, l2, r3);
		}
		else {
			read >> l >> r;
			printf("%d\n", queryGap(l, r));
		}
	}
	return 0;
}
