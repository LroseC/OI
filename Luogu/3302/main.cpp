#include <cstdio>
#include <iostream>

using namespace std;

int CASEID;
int n, m, q;

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> CASEID;
	cin >> n >> m >> q;
	for (int i = 1; i <= n; ++i) cin >> w[i];
	for (int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) dfs(i, i);

	int lastans = 0;
	for (int i = 1; i <= q; ++i) {
		char op, x, y, k;
		cin >> op >> x >> y;
		x ^= lastans, y ^= lastans;
		if (op == 'Q') {
			cin >> k; k ^= lastans;
			int lca = LCA(x, y);
			printf("%d\n", query(root[x], root[y], root[lca], root[fa[lca][0]], k));
		}
		else {
		}
	}
	return 0;
}
