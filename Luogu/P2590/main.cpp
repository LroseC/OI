#include <vector>
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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int N = 3e4 + 10;

int n, m;
int val[N];
int sz[N], fa[N], son[N], dep[N], top[N];
int idx, L[N], R[N], revL[N];
std::vector<int> G[N];
i64 sum[N << 2], maxv[N << 2];

void getFa(int u)
{
	sz[u] = 1;
	son[u] = 0;
	dep[u] = dep[fa[u]] + 1;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			getFa(v);
			if (sz[v] > sz[son[u]])
				son[u] = v;
			sz[u] += sz[v];
		}
}
void initCut(int u, int tp)
{
	L[u] = ++idx;
	revL[idx] = u;
	top[u] = tp;
	if (son[u])
		initCut(son[u], tp);
	for (int v : G[u])
		if (v != fa[u] && v != son[u])
			initCut(v, v);
	R[u] = idx;
}
void maintain(int u)
{
	sum[u] = sum[u << 1] + sum[u << 1 | 1];
	maxv[u] = std::max(maxv[u << 1], maxv[u << 1 | 1]);
}
void build(int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		sum[u] = maxv[u] = val[revL[l]];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void change(int pos, int val, int u = 1, int l = 1, int r = n)
{
	if (l == r) {
		sum[u] = maxv[u] = val;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
		change(pos, val, u << 1, l, mid);
	else
		change(pos, val, u << 1 | 1, mid + 1, r);
	maintain(u);
}
i64 queryMax(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R)
		return maxv[u];
	int mid = l + r >> 1;
	i64 res = INT_MIN;
	if (L <= mid)
		res = std::max(res, queryMax(L, R, u << 1, l, mid));
	if (R > mid)
		res = std::max(res, queryMax(L, R, u << 1 | 1, mid + 1, r));
	return res;
}
i64 querySum(int L, int R, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R)
		return sum[u];
	int mid = l + r >> 1;
	i64 res = 0;
	if (L <= mid)
		res += querySum(L, R, u << 1, l, mid);
	if (R > mid)
		res += querySum(L, R, u << 1 | 1, mid + 1, r);
	return res;
}
i64 queryPath(int u, int v, const char type[])
{
	i64 res = (type[0] == 'S' ? 0 : INT_MIN);
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			std::swap(u, v);
		if (type[0] == 'S')
			res = res + querySum(L[top[u]], L[u]);
		else
			res = std::max(res, queryMax(L[top[u]], L[u]));
		u = fa[top[u]];
	}
	if (L[u] > L[v])
		std::swap(u, v);
	if (type[0] == 'S')
		res = res + querySum(L[u], L[v]);
	else
		res = std::max(res, queryMax(L[u], L[v]));
	return res;
}

int main(void)
{
	read >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		read >> val[i];

	getFa(1);
	initCut(1, 1);
	build();
	read >> m;
	while (m--) {
		char op[10];
		scanf("%s", op);
		if (op[0] == 'C') {
			int u, val;
			read >> u >> val;
			change(L[u], val);
		}
		else if (op[1] == 'M') {
			int u, v;
			read >> u >> v;
			printf("%lld\n", queryPath(u, v, "MAX"));
		}
		else {
			int u, v;
			read >> u >> v;
			printf("%lld\n", queryPath(u, v, "SUM"));
		}
	}
	return 0;
}
