#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 8e4 + 10, LOG = 20;

int CASEID;
int n, m, q, w[N];
int dep[N];
vector<int> nums;
vector<int> G[N];
int idx;
int fa[N][LOG];
int root[N];

struct node
{
	int l, r, sz;
} tr[N << 7];

int add(int pre, int key, int l = 0, int r = n)
{
	int u = ++idx;
	tr[u] = tr[pre];
	if (l == r) {
		++tr[u].sz;
		return u;
	}
	int mid = l + r >> 1;
	if (key <= mid) tr[u].l = add(tr[u].l, key, l, mid);
	else tr[u].r = add(tr[u].r, key, mid + 1, r);
	tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz;
	return u;
}
int query(int u1, int u2, int p1, int p2, int k, int l = 0, int r = n)
{
	if (l == r) return nums[l];
	int mid = l + r >> 1;
	int sz = tr[u1].sz + tr[u2].sz - tr[p1].sz - tr[p2].sz;
	int leftsz = tr[tr[u1].l].sz + tr[tr[u2].l].sz - tr[tr[p1].l].sz - tr[tr[p2].l].sz;
	if (leftsz >= k)
		return query(tr[u1].l, tr[u2].l, tr[p1].l, tr[p2].l, k, l, mid);
	else
		return query(tr[u1].r, tr[u2].r, tr[p1].r, tr[p2].r, k - leftsz, mid + 1, r);
}

void dfs(int u, int father)
{
	dep[u] = dep[father] + 1;
	fa[u][0] = father;
	for (int k = 1; k < LOG; ++k)
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
	root[u] = add(root[father], w[u]);
	for (int v : G[u])
		if (v != father) {
			dfs(v, u);
		}
}
int LCA(int a, int b)
{
	if (dep[a] < dep[b]) swap(a, b);
	for (int k = LOG - 1; k >= 0; --k)
		if (dep[fa[a][k]] >= dep[b]) a = fa[a][k];
	if (a == b) return a;
	for (int k = LOG - 1; k >= 0; --k)
		if (fa[a][k] != fa[b][k]) {
			a = fa[a][k];
			b = fa[b][k];
		}
	return fa[a][0];
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> CASEID;
	cin >> n >> m >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> w[i];
		nums.emplace_back(w[i]);
	}
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i)
		w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();

	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		if (!dep[i]) {
			dfs(i, 0);
		}

	int lastans = 0;
	for (int i = 1; i <= q; ++i) {
		char op;
		int x, y, k;
		cin >> op >> x >> y;
		x ^= lastans, y ^= lastans;
		if (op == 'Q') {
			cin >> k; k ^= lastans;
			int lca = LCA(x, y);
			printf("%d\n", lastans = query(root[x], root[y], root[lca], root[fa[lca][0]], k));
		}
		else {
			if (tr[root[x]].sz > tr[root[y]].sz) swap(x, y);
			G[x].emplace_back(y);
			G[y].emplace_back(x);
			dfs(x, y);
		}
	}
	return 0;
}
