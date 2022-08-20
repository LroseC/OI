#include <vector>
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
const int B = 2700, N = 1e5 + 10;

struct node
{
	i32 l, r;
	i32 sz;
};
struct Query
{
	i32 u, v, d, id;
	Query(i32 _u, i32 _v, i32 _d, i32 _id)
	{ u = _u, v = _v, d = _d, id = _id; }
	bool operator<(const Query &other) const
	{ return d < other.d; }
};

i32 n, m, dfnCnt, idx;
i32 sz[N], dep[N], fa[N], val[N], son[N], top[N];
i32 L[N], R[N], invL[N];
i32 root[N];
node tr[N << 6];
std::vector<PII> G[N];
std::vector<Query> q;
i64 ans[N];

void getSz(i32 u)
{
	sz[u] = 1;
	dep[u] = dep[fa[u]] + 1;
	for (auto e : G[u]) {
		i32 v = e.first;
		i32 w = e.second;
		if (v == fa[u]) continue;
		fa[v] = u;
		val[v] = w - 1;
		getSz(v);
		sz[u] += sz[v];
		if (sz[v] > sz[son[u]]) son[u] = v;
	}
}
void initCut(i32 u, i32 tp)
{
	dfnCnt += 1;
	L[u] = dfnCnt;
	invL[dfnCnt] = u;
	top[u] = tp;
	if (son[u]) initCut(son[u], tp);
	for (auto e : G[u]) {
		i32 v = e.first;
		if (v == fa[u] || v == son[u]) continue;
		initCut(v, v);
	}
	R[u] = dfnCnt;
}
i32 getCnt(i32 u, i32 v)
{
	i32 res = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			std::swap(u, v);
		res += dep[u] - dep[top[u]] + 1;
		u = fa[top[u]];
	}
	if (dep[u] < dep[v])
		std::swap(u, v);
	res += dep[u] - dep[v] + 1;
	return res;
}
i32 clone(i32 x)
{
	idx += 1;
	tr[idx] = tr[x];
	return idx;
}
void maintain(i32 u)
{ tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz; }
i32 insert(i32 v, i32 last, i32 l = 1, i32 r = 3e4)
{
	i32 u = clone(last);
	if (l == r) {
		tr[u].sz += 1;
		return u;
	}
	i32 mid = l + r >> 1;
	if (v <= mid)
		tr[u].l = insert(v, tr[u].l, l, mid);
	else
		tr[u].r = insert(v, tr[u].r, mid + 1, r);
	maintain(u);
	return u;
}
i32 query(i32 val, i32 u, i32 v, i32 l = 1, i32 r = 3e4)
{
//	printf("l = %d, r = %d, val = %d\n", l, r, tr[u].sz - tr[v].sz);
	if (val <= l)
		return tr[u].sz - tr[v].sz;
	i32 mid = l + r >> 1;
	i32 res = 0;
	if (val <= mid)
		res += query(val, tr[u].l, tr[v].l, l, mid);
	res += query(val, tr[u].r, tr[v].r, mid + 1, r);
	return res;
}
i64 queryPath(i32 u, i32 v, i32 d)
{
	i64 res = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			std::swap(u, v);
		for (i32 x = d; x <= 3e4; x += d) {
//			printf("u = %d, top[u] = %d\n", u, top[u]);
//			printf("q(%d, (%d -> %d))\n", x, L[u], L[top[u]] - 1);
			res += query(x, root[L[u]], root[L[top[u]] - 1]);
		}
		u = fa[top[u]];
	}
	if (u == v) return res;
	if (dep[u] < dep[v])
		std::swap(u, v);
	for (i32 x = d; x <= 3e4; x += d) {
//		printf("u = %d, v = %d\n", u, v);
//		printf("q(%d, (%d -> %d))\n", x, L[u], L[v]);
		res += query(x, root[L[u]], root[L[v] + 1 - 1]);
	}
	return res;
}
namespace Seg
{
	i64 tr[N << 2];
	void build(i32 d, i32 u = 1, i32 l = 1, i32 r = n)
	{
		if (l == r) {
			tr[u] = val[invL[l]] / d;
			return;
		}
		i32 mid = l + r >> 1;
		build(d, u << 1, l, mid);
		build(d, u << 1 | 1, mid + 1, r);
		tr[u] = tr[u << 1] + tr[u << 1 | 1];
	}
	i64 query(i32 L, i32 R, i32 u = 1, i32 l = 1, i32 r = n)
	{
		if (L <= l && r <= R)
			return tr[u];
		i32 mid = l + r >> 1;
		i64 res = 0;
		if (L <= mid)
			res += query(L, R, u << 1, l, mid);
		if (R > mid)
			res += query(L, R, u << 1 | 1, mid + 1, r);
		return res;
	}
	i64 queryPath(i32 u, i32 v)
	{
		i64 res = 0;
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]])
				std::swap(u, v);
			res += query(L[top[u]], L[u]);
			u = fa[top[u]];
		}
		if (u == v) return res;
		if (dep[u] < dep[v])
			std::swap(u, v);
		res += query(L[v] + 1, L[u]);
		return res;
	}
}
void solve(void)
{
	std::sort(q.begin(), q.end());
	for (int i = 0; i < q.size(); ++i) {
		if (i == 0 || q[i].d != q[i - 1].d)
			Seg::build(q[i].d);
		ans[q[i].id] = Seg::queryPath(q[i].u, q[i].v) + getCnt(q[i].u, q[i].v);
	}
}

int main(void)
{
#ifndef DEBUG
	freopen("delivery.in", "r", stdin);
	freopen("delivery.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i < n; ++i) {
		i32 u, v, d;
		read >> u >> v >> d;
		G[u].emplace_back(v, d);
		G[v].emplace_back(u, d);
	}
	getSz(1);
	initCut(1, 1);
	for (int i = 1; i <= n; ++i) {
		root[i] = insert(val[invL[i]], root[i - 1]);
	}
	for (int i = 1; i <= m; ++i) {
		i32 u, v, d;
		read >> u >> v >> d;
		if (d > B) {
//			printf("u = %d, v = %d, d = %d\n", u, v, d);
			ans[i] = queryPath(u, v, d) + getCnt(u, v); //把边权放到点上, 注意别求 LCA 的.
		}
		else {
//			fprintf(stderr, "id = %d???\n", i);
			q.emplace_back(u, v, d, i);
		}
	}
	solve();
	for (int i = 1; i <= m; ++i) {
		printf("%lld\n", ans[i]);
	}
	return 0;
}
/*
   问题套上树剖之后等价于区间求 (a[i] / x).
   值域很小, 考虑根号分治.
   小于 B 的可以离线, 查询复杂度 n * B + mlog^2n.
   大于 B 的每次查询大于等于 x, 大于等于 2x...
   复杂度 mlog^2n * (3e4 / B);
   故块长 B 取 sqrt(3e4 * m * log^2n / n)
   复杂度约为 5e8, 应该能过?
   如果是 NOI 场上大概就过了反正.
   开码!
   但是码量略大?
   树剖套主席树 + 树剖套线段树
   毒瘤的一批.
   等下我不会被卡空间把.
   好像不卡, 而且很宽松.
   大家好像都码了一会又停了一下, 什么意思呢?
   莫非 T1 其实有小码量, 小常数做法?
   话说这东西是不是叫阈值分治来着?
   我靠, 万万没想到, 有一天线段树会靠着它的 O(n) build 吊打树状数组.
   本来还寻思着树状数组好写, 是不是可以写树状数组.
   大意了, 没有闪.
   码完了, 码码码码码码码.
   巨长无比, 但是全是板子, 为啥我敲了这么久?
   现在大脑发热严重, 性能急剧下降.
   才过两个小时呢, 肯定能调出来 (flag++);
   极限数据 2.58s, 开拍!
*/
