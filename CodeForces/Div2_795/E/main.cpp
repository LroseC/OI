#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 1e5 + 10;

struct segNode
{
	int c, l, r;
	segNode(void) {}
	segNode(int _c, int _l, int _r)
	{ c = _c, l = _l, r = _r; }
};

int n, idx;
vint nums;
int tr[N << 3];
vint G[N << 3];
bool vis[N << 3][2];
segNode seg[N << 3];

inline void addEdge(int u, int v)
{
	G[u].emplace_back(v);
	G[v].emplace_back(u);
}
void build(int u = 1, int l = 0, int r = nums.size())
{
	tr[u] = ++idx;
	if (l == r) {
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	addEdge(tr[u], tr[u << 1]);
	addEdge(tr[u], tr[u << 1 | 1]);
}
void add(int L, int R, int v, int u = 1, int l = 0, int r = nums.size())
{
	if (L <= l && r <= R) {
		addEdge(tr[u], v);
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) add(L, R, v, u << 1, l, mid);
	if (R > mid) add(L, R, v, u << 1 | 1, mid + 1, r);
}
void dfs(int u, int color)
{
	printf("u = %d, color = %d\n", u, color);
	vis[u][color] = 1;
	for (int v : G[u]) {
		if (v <= n && seg[v].c == color) continue;
		if (v <= n) {
			if (vis[v][color ^ 1]) continue;
			dfs(v, color ^ 1);
		}
		else {
			if (vis[v][color]) continue;
			dfs(v, color);
		}
	}
}

void work(void)
{
	read >> n;
	idx = n;
	for (int i = 1; i <= n; ++i) {
		read >> seg[i].c >> seg[i].l >> seg[i].r;
		nums.emplace_back(seg[i].l);
		nums.emplace_back(seg[i].r);
	}
	std::sort(nums.begin(), nums.end());
	nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	for (int i = 1; i <= n; ++i) {
		seg[i].l = std::lower_bound(nums.begin(), nums.end(), seg[i].l) - nums.begin();
		seg[i].r = std::lower_bound(nums.begin(), nums.end(), seg[i].r) - nums.begin();
	}
	build();
	for (int i = 1; i <= n; ++i) {
		add(seg[i].l, seg[i].r, i);
	}
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		if (!vis[i][seg[i].c]) {
			++res;
			dfs(i, seg[i].c);
		}
	}
	printf("%d\n", res);
	for (int i = 1; i <= idx; ++i) {
		vis[i][0] = vis[i][1] = 0;
		G[i].clear();
	}
	nums.clear();
}

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	int tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
