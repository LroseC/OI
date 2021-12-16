#include <cctype>
#include <cstdio>
#include <algorithm>

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
} io;

const int N = 5010;
using LL = long long;

struct Vector
{
	int x, y;
	Vector(void) { x = y = 0; }
	Vector(int _x, int _y) : x(_x), y(_y) {}
};
struct Matrix
{
	Vector p1, p2;
};
FSI& operator>>(FSI& io, Vector &a)
{
	return io >> a.x >> a.y;
}
FSI& operator>>(FSI& io, Matrix &m)
{
	return io >> m.p1 >> m.p2;
}

struct Query
{
	int x, l, r, v;
	Query(void) { x = l = r = v = 0; }
	Query(int _x, int _l, int _r, int _v) : x(_x), l(_l), r(_r), v(_v) {}
	bool operator<(const Query& other) const
	{
		if (x != other.x) return x < other.x;
		return v > other.v;
	}
};

int n;
Matrix M[N];
int idx;
Query q[N << 1];

struct node
{
	int l, r;
	int cnt, res;
} tr[(int)1e6];

LL ans;

void maintain(int u)
{
	if (tr[u].cnt) tr[u].res = tr[u].r - tr[u].l + 1;
	else {
		if (tr[u].l == tr[u].r) tr[u].res = 0;
		else tr[u].res = tr[u << 1].res + tr[u << 1 | 1].res;
	}
}
void build(int u, int l, int r)
{
	tr[u].l = l; tr[u].r = r;
	if (l == r) {
		tr[u].cnt = tr[u].res = 0;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void add(int L, int R, int v, int u = 1)
{
	int l = tr[u].l, r = tr[u].r;
	if (L <= l && r <= R) {
		tr[u].cnt += v;
		maintain(u);
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, v, u << 1);
	if (R > mid) add(L, R, v, u << 1 | 1);
	maintain(u);
}

void calc(void)
{
	build(1, -10000, 10000);
	sort(q + 1, q + 1 + idx);
	for (int i = 1, last = -100000, res = 0; i <= idx; ++i) {
		add(q[i].l, q[i].r - 1, q[i].v);
		if (q[i + 1].x != q[i].x || q[i + 1].v != q[i].v) {
			ans += abs(tr[1].res - res);
			res = tr[1].res;
		}
	}
}

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) io >> M[i];
	for (int i = 1; i <= n; ++i) {
		q[++idx] = Query(M[i].p1.x, M[i].p1.y, M[i].p2.y, 1);
		q[++idx] = Query(M[i].p2.x, M[i].p1.y, M[i].p2.y, -1);
	}
	calc();
	idx = 0;
	for (int i = 1; i <= n; ++i) {
		q[++idx] = Query(M[i].p1.y, M[i].p1.x, M[i].p2.x, 1);
		q[++idx] = Query(M[i].p2.y, M[i].p1.x, M[i].p2.x, -1);
	}
	calc();
	printf("%lld\n", ans);
	return 0;
}
