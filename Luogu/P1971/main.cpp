#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

const int N = 1e4 + 10, M = 1e5 + 10;
int gox[] = {1, -1, 0, 0};
int goy[] = {0, 0, 1, -1};

bool vis[50][50], win[N];
char G[50][50];
int n, m, K, S = N - 1, T = N - 2;
int idx = 1, head[N], nex[M], to[M], fl[M];
std::vector< std::pair<int, int> > del	;

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

namespace dinic
{
	int now[N], d[N];

	bool BFS(void)
	{
		std::queue<int> q;
		std::memset(d, 0, sizeof d);
		std::memcpy(now, head, sizeof head);
		d[S] = 1; q.emplace(S);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (int e = head[u]; e; e = nex[e])
				if (fl[e] && !d[to[e]]) {
					d[to[e]] = d[u] + 1;
					if (to[e] == T) return 1;
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
	int main(void)
	{
		int res = 0;
		while (BFS())
			res += dfs(S, INT_MAX);
		return res;
	}
}

inline int getId(int x, int y)
{
	return (x - 1) * m + y;
}
int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		scanf("%s", G[i] + 1);
		for (int j = 1; j <= m; ++j) {
			if (G[i][j] == '.') {
				addFlow(S, getId(i, j), 1);
				vis[i][j] = 1;
				del.emplace_back(i, j);
			}
			if (G[i][j] == 'X')
				addFlow(S, getId(i, j), 1);
			if (G[i][j] == 'O')
				addFlow(getId(i, j), T, 1);
		}
	}
	read >> K;
	for (int i = 1, x, y; i <= K << 1; ++i) {
		read >> x >> y;
		vis[x][y] = 1;
		del.emplace_back(x, y);
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (!vis[i][j] && G[i][j] == 'X')
				for (int k = 0; k < 4; ++k) {
					int xx = i + gox[k];
					int yy = j + goy[k];
					if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
					if (!vis[xx][yy] && G[i][j] != G[xx][yy])
						addFlow(getId(i, j), getId(xx, yy), 1);
				}
	dinic::main();
	int tmp = 0;
	for (int i = K << 1; i >= 0; --i) {
		auto t = del[i];
		tmp ^= 1;
		vis[t.first][t.second] = 0;
		for (int k = 0; k < 4; ++k) {
			int xx = t.first + gox[k];
			int yy = t.second + goy[k];
			if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
			if (!vis[xx][yy] && G[t.first][t.second] != G[xx][yy]) {
				if (G[xx][yy] == 'X' || G[xx][yy] == '.')
					addFlow(getId(xx, yy), getId(t.first, t.second), 1);
				else
					addFlow(getId(t.first, t.second), getId(xx, yy), 1);
			}
		}
		win[i] = dinic::main();
	}
	int res = 0;
	for (int i = 0; i <= K << 1; i += 2)
		if (win[i] && win[i + 1])
			++res;
	printf("%d\n", res);
	for (int i = 0; i <= K << 1; i += 2)
		if (win[i] && win[i + 1])
			printf("%d\n", (i >> 1) + 1);
	return 0;
}
