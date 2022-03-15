#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, M = 2e5 + 10;

int n, m;
int inedge[N], outedge[N];
int now[N];
vector<int> ans, G[N];

int stk[M], top;

void dfs(int u)
{
	stk[++top] = u;
	while (top) {
		u = stk[top];
		if (now[u] < G[u].size()) {
			stk[++top] = G[u][now[u]];
			++now[u];
		}
		else {
			--top;
			ans.emplace_back(u);
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(v);
		++outedge[u];
		++inedge[v];
	}
	int st = -1, ed = -1;
	int oddcnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (inedge[i] != outedge[i]) ++oddcnt;
		if (inedge[i] == outedge[i] - 1) st = i;
		if (inedge[i] == outedge[i] + 1) ed = i;
		sort(G[i].begin(), G[i].end());
	}
	if (oddcnt == 2 && ~st && ~ed) {
		dfs(st);
		for (int i = ans.size() - 1; i >= 0; --i)
			printf("%d ", ans[i]);
		puts("");
	}
	else if (oddcnt == 0) {
		dfs(1);
		for (int i = ans.size() - 1; i >= 0; --i)
			printf("%d ", ans[i]);
		puts("");
	}
	else puts("No");
	return 0;
}
