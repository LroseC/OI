#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
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
} read;

const int N = 5e5 + 10;

struct UnionFind
{
	int fa[N], sz[N], dis[N];
	int stk[N], top;

	void init(int n)
	{
		for (int i = 1; i <= n; ++i)
			fa[i] = i, sz[i] = 1;
	}
	int find(int x)
	{
		while (fa[x] != x)
			x = fa[x];
		return x;
	}
	int get(int x)
	{
		int res = 0;
		while (fa[x] != x)
			res ^= dis[x], x = fa[x];
		return res;
	}
	void merge(int x, int y)
	{
		int u = find(x), v = find(y);
		int dx = get(x), dy = get(y);
		if (u != v) {
			if (sz[u] < sz[v]) swap(u, v);
			fa[v] = u;
			dis[v] = dx ^ dy ^ 1;
			sz[u] += sz[v];
			stk[++top] = v;
		}
	}
	void back(void)
	{
		int u = stk[top--];
		sz[fa[u]] -= sz[u];
		fa[u] = u;
		dis[u] = 0;
	}
	bool check(int x, int y)
	{
		if (find(x) == find(y) && ((get(x) ^ get(y)) == 0))
			return 0;
		return 1;
	}
};

struct Query
{
	int e, c;
};

int n, m, q, K;
int bk[1010][55];
int ans[N];
UnionFind uf[55];
Query query[N];
int last[N];
pair<int, int> G[N];

namespace SegmentTree
{
	int dep;
	vector<int> tag[N << 4];

	void add(int L, int R, int val, int u = 1, int l = 1, int r = q)
	{
		if (L > R) return;
		if (L <= l && r <= R) {
			tag[u].emplace_back(val);
			return;
		}
		int mid = l + r >> 1;
		if (L <= mid) add(L, R, val, u << 1, l, mid);
		if (R > mid) add(L, R, val, u << 1 | 1, mid + 1, r);
	}
	void calc(int u = 1, int l = 1, int r = q)
	{
		++dep;
		for (int i = 1; i <= K; ++i) bk[dep][i] = uf[i].top;
		for (auto t : tag[u]) {
			int edge = query[t].e, color = query[t].c;
			if (ans[t])
				uf[color].merge(G[edge].first, G[edge].second);
			else
				uf[last[edge]].merge(G[edge].first, G[edge].second);
		}
		if (l == r) {
			int edge = query[l].e, color = query[l].c;
			ans[l] = uf[color].check(G[edge].first, G[edge].second);
			if (ans[l])
				last[edge] = color;
		}
		else {
			int mid = l + r >> 1;
			calc(u << 1, l, mid);
			calc(u << 1 | 1, mid + 1, r);
		}
		for (int i = 1; i <= K; ++i)
			while (uf[i].top != bk[dep][i]) uf[i].back();
		--dep;
	}
}

int main(void)
{
	read >> n >> m >> K >> q;
	for (int i = 1; i <= K; ++i)
		uf[i].init(n);
	for (int i = 1; i <= m; ++i) {
		int u, v; read >> u >> v;
		G[i] = make_pair(u, v);
	}
	for (int i = 1; i <= q; ++i) {
		read >> query[i].e >> query[i].c;
		if (last[query[i].e])
			SegmentTree::add(last[query[i].e] + 1, i - 1, last[query[i].e]);
		last[query[i].e] = i;
	}
	for (int i = 1; i <= m; ++i)
		if (last[i])
			SegmentTree::add(last[i] + 1, q, last[i]);
	memset(last, 0, sizeof last);
	SegmentTree::calc();
	for (int i = 1; i <= q; ++i)
		puts(ans[i] ? "YES" : "NO");
	return 0;
}
