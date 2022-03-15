#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, M = 5e5 + 10, LOG = 18;

struct Edge
{
	int u, v, w;
	bool operator<(const Edge &other) const
	{
		return w < other.w;
	}
};

int n, m, q;
int h[N];
Edge edge[M];
vector<int> nums;

namespace UnionFind
{
	int fa[N << 1];
	void init(int n)
	{
		for (int i = 0; i <= n; ++i) fa[i] = i;
	}
	int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
	void merge(int a, int b)
	{
		a = find(a), b = find(b);
		if (a == b) return;
		fa[a] = b;
	}
}
namespace SGT
{
	int idx;
	struct node
	{
		int l, r;
		int sz;
	} tr[(int)5e6];

	int add(int pre, int key, int val, int l = 0, int r = n)
	{
		int u = ++idx;
		tr[u] = tr[pre];
		if (l == r) {
			++tr[u].sz;
			return u;
		}
		int mid = l + r >> 1;
		if (key <= mid) tr[u].l = add(tr[u].l, key, val, l, mid);
		else tr[u].r = add(tr[u].r, key, val, mid + 1, r);
		tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz;
		return u;
	}
	int queryk(int u1, int u2, int k, int l = 0, int r = n)
	{
		if (tr[u2].sz - tr[u1].sz < k) return -1;
		if (l == r) return nums[l];
		int mid = l + r >> 1;
		if (tr[tr[u2].r].sz - tr[tr[u1].r].sz >= k) return queryk(tr[u1].r, tr[u2].r, k, mid + 1, r);
		else return queryk(tr[u1].l, tr[u2].l, k - (tr[tr[u2].r].sz - tr[tr[u1].r].sz), l, mid);
	}
	void print(int u, int l = 0, int r = n)
	{
		printf("u = %d, sz = %d, l = %d, r = %d\n", u, tr[u].sz, l, r);
		if (l == r) return;
		int mid = l + r >> 1;
		print(tr[u].l, l, mid);
		print(tr[u].r, mid + 1, r);
	}
}
namespace Kruskal
{
	int nodecnt;
	int root[N << 1];
	int id[N << 1], idx;
	int L[N << 1], R[N << 1];
	int ch[N << 1][2];
	int fa[N << 1][LOG];
	int Difficulty[N << 1];

	void dfs(int u)
	{
		for (int k = 1; k <= LOG - 1; ++k)
			fa[u][k] = fa[fa[u][k - 1]][k - 1];
		if (!ch[u][0]) {
			L[u] = R[u] = ++idx;
			root[idx] = SGT::add(root[idx - 1], h[u], 1);
			return;
		}
		fa[ch[u][0]][0] = fa[ch[u][1]][0] = u;
		dfs(ch[u][0]); dfs(ch[u][1]);
		L[u] = min(L[ch[u][0]], L[ch[u][1]]);
		R[u] = max(R[ch[u][0]], R[ch[u][1]]);
	}
	void build(void)
	{
		nodecnt = n;
		UnionFind::init(n * 2);
		sort(edge + 1, edge + 1 + m);
		for (int i = 1; i <= m; ++i) {
			int u = UnionFind::find(edge[i].u), v = UnionFind::find(edge[i].v);
			if (u == v) continue;
			++nodecnt;
			ch[nodecnt][0] = u;
			ch[nodecnt][1] = v;
			UnionFind::merge(u, nodecnt);
			UnionFind::merge(v, nodecnt);
			Difficulty[nodecnt] = edge[i].w;
		}
		dfs(nodecnt);
	}
	int query(int u, int limit, int k)
	{
		for (int k = LOG - 1; k >= 0; --k)
			if (fa[u][k] && Difficulty[fa[u][k]] <= limit) {
				u = fa[u][k];
			}
		return SGT::queryk(root[L[u] - 1], root[R[u]], k);
	}
}

int main(void)
{
	//Read And Rispersed
	ios::sync_with_stdio(0);
	cin >> n >> m >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> h[i];
		nums.emplace_back(h[i]);
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i) h[i] = lower_bound(nums.begin(), nums.end(), h[i]) - nums.begin();


	//Init
	for (int i = 1; i <= m; ++i) {
		cin >> edge[i].u >> edge[i].v >> edge[i].w;
	}
	Kruskal::build();


	//Solve
	for (int i = 1; i <= q; ++i) {
		int u, limit, k; cin >> u >> limit >> k;
		printf("%d\n", Kruskal::query(u, limit, k));
	}
	return 0;
}
