#include <vector>
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

using i32 = int;
using i64 = long long;
using PII = std::pair<i32, i32>;
const int N = 1e5 + 10;

i32 n, m, idx;
i32 sz[N], top[N], dep[N], fa[N], son[N], invId[N], L[N], R[N];
PII pth[N];
std::vector<i32> G[N];

void getSz(i32 u)
{
	sz[u] = 1;
	dep[u] = dep[fa[u]] + 1;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			getSz(v);
			sz[u] += sz[v];
			if (sz[v] > sz[son[u]]) {
				son[u] = v;
			}
		}
}
void initCut(i32 u, i32 fa, i32 tp)
{
	idx += 1;
	invId[idx] = u;
	L[u] = idx;
	top[u] = tp;
	if (son[u])
		initCut(son[u], u, tp);
	for (int v : G[u])
		if (v != fa && v != son[u]) {
			initCut(v, u, v);
		}
	R[u] = idx;
}
i32 LCA(i32 u, i32 v)
{
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			std::swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}
namespace Seg1
{
	i32 dec[N];
	void decPath(i32 u, i32 v)
	{
		i32 d = LCA(u, v);
		dec[u] += 1;
		dec[v] += 1;
		dec[d] -= 2;
	}
	i32 calc(i32 u, i32 fa)
	{
		i32 res = 0;
		for (i32 v : G[u])
			if (v != fa) {
				res += calc(v, u);
				dec[u] += dec[v];
			}
		res += std::min(2, dec[u]);
		return res;
	}
}
namespace Seg2
{
	struct node
	{
		i32 tag[2];
		i32 sum[2];
	} tr[N << 2];
	void covNode(i32 u, i32 l, i32 r, i32 v, i32 op)
	{
		tr[u].tag[op] = v;
		tr[u].sum[op] = (r - l + 1) * v;
	}
	void spread(i32 u, i32 l, i32 r)
	{
		for (int op = 0; op < 2; ++op) {
			if (~tr[u].tag[op]) {
				i32 mid = l + r >> 1;
				covNode(u << 1, l, mid, tr[u].tag[op], op);
				covNode(u << 1 | 1, mid + 1, r, tr[u].tag[op], op);
				tr[u].tag[op] = -1;
			}
		}
	}
	void cover(i32 L, i32 R, i32 v, i32 op, i32 u = 1, i32 l = 1, i32 r = n)
	{
		if (L <= l && r <= R) {
			covNode(u, l, r, v, op);
			return;
		}
		i32 mid = l + r >> 1;
		spread(u, l, r);
		if (L <= mid)
			cover(L, R, v, op, u << 1, l, mid);
		if (R > mid)
			cover(L, R, v, op, u << 1 | 1, mid + 1, r);
		for (int op = 0; op < 2; ++op)
			tr[u].sum[op] = tr[u << 1].sum[op] + tr[u << 1 | 1].sum[op];
	}
	i32 query(i32 L, i32 R, i32 op, i32 u = 1, i32 l = 1, i32 r = n)
	{
		if (L <= l && r <= R) {
			return tr[u].sum[op];
		}
		i32 mid = l + r >> 1;
		spread(u, l, r);
		i32 res = 0;
		if (L <= mid)
			res += query(L, R, op, u << 1, l, mid);
		if (R > mid)
			res += query(L, R, op, u << 1 | 1, mid + 1, r);
		return res;
	}
	void covPath(i32 u, i32 v, i32 val)
	{
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]]) {
				cover(L[top[u]], L[u], val, 0);
				u = fa[top[u]];
			}
			else {
				cover(L[top[v]], L[v], val, 1);
				v = fa[top[v]];
			}
		}
		if (u == v) return;
		if (dep[u] > dep[v])
			cover(L[v] + 1, L[u], val, 0);
		else
			cover(L[u] + 1, L[v], val, 1);
	}
	i32 queryPath(i32 u, i32 v)
	{
		i32 res = 0;
		while (top[u] != top[v]) {
			if (dep[top[u]] > dep[top[v]]) {
				res += query(L[top[u]], L[u], 0);
				u = fa[top[u]];
			}
			else {
				res += query(L[top[v]], L[v], 1);
				v = fa[top[v]];
			}
		}
		if (u == v) return res;
		if (dep[u] > dep[v])
			res += query(L[v] + 1, L[u], 0);
		else
			res += query(L[u] + 1, L[v], 1);
		return res;
	}
}

int main(void)
{
#ifndef DEBUG
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
#endif
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i < n; ++i) {
		i32 u, v;
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	getSz(1);
	initCut(1, 1, 1);
	for (int i = 0; i < m; ++i) {
		read >> pth[i].first >> pth[i].second;
		Seg1::decPath(pth[i].first, pth[i].second);
	}
	i32 res;
	printf("%d\n", res = Seg1::calc(1, 1));
	if (m <= 15) {
		for (int i = 0; i < 1 << m; ++i) {
			i32 ans = 0;
			Seg2::cover(1, n, 1, 0);
			Seg2::cover(1, n, 1, 1);
			for (int j = 0; j < m; ++j) {
				if (i >> j & 1) {
					ans += Seg2::queryPath(pth[j].first, pth[j].second);
					Seg2::covPath(pth[j].first, pth[j].second, 0);
				}
				else {
					ans += Seg2::queryPath(pth[j].second, pth[j].first);
					Seg2::covPath(pth[j].second, pth[j].first, 0);
				}
			}
			if (ans == res) {
				for (int j = 0; j < m; ++j) {
					if (i >> j & 1) {
						printf("%d %d\n", pth[j].first, pth[j].second);
					}
					else {
						printf("%d %d\n", pth[j].second, pth[j].first);
					}
				}
				return 0;
			}
		}
	}
	for (int i = 0; i < m; ++i)
		printf("%d %d\n", pth[i].first, pth[i].second);
	return 0;
}
