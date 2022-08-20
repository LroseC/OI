#include <cctype>
#include <cstdio>
#include <cstdint>
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

using i32 = int32_t;
using i64 = int64_t;
using PII = std::pair<i32, i32>;
const int N = 1e5 + 10;

struct node
{
	i32 tag, val;
	friend node operator+(const node &a, const node &b)
	{
		node res;
		res.tag = 0;
		res.val = std::min(a.val, b.val);
		return res;
	}
};

i32 n, m;
i32 a[N];
node tr[N << 2];

void addNode(i32 u, i32 val)
{
	tr[u].val += val;
	tr[u].tag += val;
}
void spread(i32 u)
{
	if (tr[u].tag) {
		addNode(u << 1, tr[u].tag);
		addNode(u << 1 | 1, tr[u].tag);
		tr[u].tag = 0;
	}
}
void build(i32 u = 1, i32 l = 1, i32 r = n)
{
	tr[u].val = tr[u].tag = 0;
	if (l == r) return;
	i32 mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
}
void add(i32 L, i32 R, i32 v, i32 u = 1, i32 l = 1, i32 r = n)
{
	if (L <= l && r <= R) {
		addNode(u, v);
		return;
	}
	i32 mid = l + r >> 1;
	spread(u);
	if (L <= mid) add(L, R, v, u << 1, l, mid);
	if (R > mid) add(L, R, v, u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
i32 query(i32 L, i32 R, i32 u = 1, i32 l = 1, i32 r = n)
{
	if (L > R) return 0;
	if (L <= l && r <= R) {
		if (tr[u].val > 0) return 0;
		if (l == r) return l;
		i32 mid = l + r >> 1;
		spread(u);
		if (tr[u << 1 | 1].val == 0) {
			return query(L, R, u << 1 | 1, mid + 1, r);
		}
		else
			return query(L, R, u << 1, l, mid);
	}
	i32 mid = l + r >> 1;
	spread(u);
	i32 res = 0;
	if (R > mid) {
		res = std::max(res, query(L, R, u << 1 | 1, mid + 1, r));
	}
	if (res != 0) return res;
	if (L <= mid) {
		res = std::max(res, query(L, R, u << 1, l, mid));
	}
	return res;
}

void work(void)
{
	read >> n;
	build();
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
	}
	for (int i = 1; i <= n; ++i) {
		if (a[i] < i) add(a[i], i - 1, 1);
	}
	read >> m;
	for (int i = 1; i <= m; ++i) {
		i32 op;
		read >> op;
		if (op == 1) {
			i32 x, y;
			read >> x >> y;
			if (a[x] < x) add(a[x], x - 1, -1);
			a[x] = y;
			if (a[x] < x) add(a[x], x - 1, +1);
		}
		else {
			i32 x;
			read >> x;
			printf("%d\n", query(1, x - 1) + 1);
		}
	}
}

int main(void)
{
#ifndef DEBUG
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#endif
	//Think twice, code once.
	i32 tt;
	read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
/*
   有一说一, 看到 1e6 我其实不是很敢写线段树, 直到我想起一道题叫冰火战士.
   写到一半想写树状数组, 乐, 根本写不了.
   或者说我不会写?
   写挂了, 为什么??????????
   我靠, 我线段树都不会写了, 笑死.
   过了大样例, 懒得拍.
   不要挂分.
*/
