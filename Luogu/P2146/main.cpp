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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

const int N = 1e5 + 10;

int n, m;
int sz[N], fa[N], son[N], dep[N], top[N];
int idx, L[N], R[N], invL[N];
std::vector<int> G[N];
int sum[N << 2], tag[N << 2];

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
	invL[idx] = u;
	top[u] = tp;
	if (son[u])
		initCut(son[u], tp);
	for (int v : G[u])
		if (v != fa[u] && v != son[u])
			initCut(v, v);
	R[u] = idx;
}
void covernode(int u, int val, int l, int r)
{
	tag[u] = val;
	sum[u] = (r - l + 1) * val;
}
void maintain(int u) { sum[u] = sum[u << 1] + sum[u << 1 | 1]; }
void spread(int u, int l, int r)
{
	if (tag[u] != -1) {
		int mid = l + r >> 1;
		covernode(u << 1, tag[u], l, mid);
		covernode(u << 1 | 1, tag[u], mid + 1, r);
		tag[u] = -1;
	}
}
void build(int u = 1, int l = 1, int r = n)
{
	tag[u] = -1;
	if (l == r) {
		sum[u] = 0;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	maintain(u);
}
void cover(int L, int R, int v, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		covernode(u, v, l, r);
		return;
	}
	int mid = l + r >> 1;
	spread(u, l, r);
	if (L <= mid)
		cover(L, R, v, u << 1, l, mid);
	if (R > mid)
		cover(L, R, v, u << 1 | 1, mid + 1, r);
	maintain(u);
}
int query(int L, int R, int type, int u = 1, int l = 1, int r = n)
{
	if (L <= l && r <= R) {
		if (type == 0)
			return (r - l + 1) - sum[u];
		else
			return sum[u];
	}
	int res = 0;
	int mid = l + r >> 1;
	spread(u, l, r);
	if (L <= mid)
		res += query(L, R, type, u << 1, l, mid);
	if (R > mid)
		res += query(L, R, type, u << 1 | 1, mid + 1, r);
	return res;
}
void coverPath(int u)
{
	do {
		cover(L[top[u]], L[u], 1);
		u = fa[top[u]];
	} while (u);
}
int queryPath(int u)
{
	int res = 0;
	do {
		res += query(L[top[u]], L[u], 0);
		u = fa[top[u]];
	} while (u);
	return res;
}

int main(void)
{
	read >> n;
	for (int i = 2; i <= n; ++i) {
		read >> fa[i];
		++fa[i];
		G[fa[i]].emplace_back(i);
	}
	getFa(1);
	initCut(1, 1);
	build();
	read >> m;
	while (m--) {
		int u;
		char type[20];
		scanf("%s", type);
		read >> u; ++u;
		if (type[0] == 'i') {
			printf("%d\n", queryPath(u));
			coverPath(u);
		}
		else {
			printf("%d\n", query(L[u], R[u], 1));
			cover(L[u], R[u], 0);
		}
	}
	return 0;
}
