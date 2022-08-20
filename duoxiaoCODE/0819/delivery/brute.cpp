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
i64 getCnt(i32 u, i32 v, i32 d)
{
	i64 res = 0;
	while (dep[u] != dep[v]) {
		if (dep[u] < dep[v])
			std::swap(u, v);
		res += 1 + (val[u] / d);
		u = fa[u];
	}
	while (u != v) {
		res += 1 + (val[u] / d);
		res += 1 + (val[v] / d);
		u = fa[u];
		v = fa[v];
	}
	return res + 1;
}
int main(void)
{
#ifndef DEBUG
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
	for (int i = 1; i <= m; ++i) {
		i32 u, v, d;
		read >> u >> v >> d;
		printf("%d\n", getCnt(u, v, d));
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
