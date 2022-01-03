#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

using LL = long long;
const int N = 5e4 + 10, M = 5e5 + 10;

struct Edge
{
	int u, v, w;
	bool operator<(const Edge& other) const
	{
		return w < other.w;
	}
};

int edgecnt;
int n, m, s, k;
bool vis[M];
Edge edge[M];

namespace UnionFind
{
	int fa[N];

	void init(int n)
	{
		for (int i = 1; i <= n; ++i)
			fa[i] = i;
	}
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int a, int b)
	{
		a = find(a), b = find(b);
		if (a == b) return;
		fa[a] = b;
	}
}

namespace Kruskal
{
	int ans, ecnt;
	void calc(void)
	{
		ans = ecnt = 0;
		UnionFind::init(n);
		for (int i = 1; i <= m; ++i) {
			int u = UnionFind::find(edge[i].u), v = UnionFind::find(edge[i].v);
			if (u == v) continue;
			++ecnt;
			vis[i] = 1;
			ans += edge[i].w;
			UnionFind::merge(u, v);
		}
	}
}

int check(int x)
{
	for (int i = 1; i <= m; ++i)
		if (edge[i].u == s || edge[i].v == s)
			edge[i].w += x;
	sort(edge + 1, edge + 1 + m);
	memset(vis, 0, sizeof vis);
	Kruskal::calc();
	int res = 0;
	for (int i = 1; i <= m; ++i)
		if (edge[i].u == s || edge[i].v == s) {
			res += vis[i];
			edge[i].w -= x;
		}
	return res;
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m >> s >> k;
	for (int i = 1; i <= m; ++i) {
		cin >> edge[i].u >> edge[i].v >> edge[i].w;
		edgecnt += (s == edge[i].u) || (s == edge[i].v);
	}
	int l = -1e5, r = 1e5;
	if (edgecnt < k) {
		puts("Impossible");
		return 0;
	}
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (check(mid) >= k) l = mid;
		else r = mid - 1;
	}
	if (check(l) != k) {
		puts("Impossible");
		return 0;
	}
	printf("%d\n", Kruskal::ans - l * k);
	return 0;
}
