#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
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

const int N = 410, M = 1e6 + 10;

int n, m, C, S, T = N - 1;
bool vis[N];
int lim[N], s[N], ans[N], ans2[N];
std::vector<int> G[N][N];
int idx = 1, head[N], nex[M], to[M], fl[M];
int now[N], d[N];

void addEdge(int u, int v, int f)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, fl[idx] = f;
}
void addFlow(int u, int v, int f)
{
	addEdge(u, v, f);
	addEdge(v, u, 0);
}

bool BFS(int &res)
{
	std::queue<int> q;
	std::memset(d, 0, sizeof d);
	std::memcpy(now, head, sizeof now);
	d[S] = 1;
	q.emplace(S);
	while (q.size()) {
		int u = q.front(); q.pop();
		if (u != S && u <= n) res = std::max(res, u);
		for (int e = head[u]; e; e = nex[e])
			if (fl[e] && !d[to[e]]) {
				d[to[e]] = d[u] + 1;
				if (to[e] == T)
					return 1;
				q.emplace(to[e]);
			}
	}
	return 0;
}
int dfs(int u, int flow)
{
	if (u == T)
		return flow;
	int rest = flow;
	for (int e = now[u]; rest && e; e = nex[e])
		if (fl[e] && d[to[e]] == d[u] + 1) {
			now[u] = e;
			int tmp = dfs(to[e], std::min(rest, fl[e]));
			if (!tmp) d[to[e]] = 0;
			rest -= tmp;
			fl[e] -= tmp;
			fl[e ^ 1] += tmp;
		}
	return flow - rest;
}

void work(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		read >> lim[i];
		addFlow(n + i, T, lim[i]);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int aij; read >> aij;
			if (aij == 0) continue;
			G[i][aij].emplace_back(j + n);
		}
	for (int i = 1; i <= n; ++i)
		read >> s[i];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int bak = idx;
			for (int k = G[i][j].size() - 1; k >= 0; --k)
				addFlow(i, G[i][j][k], 1);
			S = i;
			if (BFS(j <= s[i] ? ans2[i] : ans2[0])) {
				dfs(i, 1);
				ans[i] = j;
				if (ans[i] <= s[i]) ans2[i] = i;
				break;
			}
			for (int k = G[i][j].size() - 1; k >= 0; --k)
				while (head[i] > bak) head[i] = nex[head[i]];
		}
	for (int i = 1; i <= n; ++i)
		printf("%d ", ans[i] == 0 ? m + 1 : ans[i]);
	puts("");
	for (int i = 1; i <= n; ++i)
		printf("%d ", i - ans2[i]);
	puts("");
}
void clear(void)
{
	idx = 1;
	std::memset(head, 0, sizeof head);
	std::memset(ans, 0, sizeof ans);
	std::memset(ans2, 0, sizeof ans2);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			G[i][j].clear();
}
int main(void)
{
//	freopen("menter.in", "r", stdin);
//	freopen("menter.out", "w", stdout);
	int T;
	read >> T >> C;
	while (T--) {
		work();
		clear();
	}
	return 0;
}
