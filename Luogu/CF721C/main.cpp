#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 5010;

struct Edge
{
	int v, w;
	Edge(void) { v = w = 0; }
	Edge(int _v, int _w) : v(_v), w(_w) {}
};

int inedge[N];
int n, m, limit;
vector<Edge> G[N];
int f[N][N], pre[N][N];
/*
   f[i][j] 表示以点 i 为终点, 经过 j 个点所经过的最小距离.
*/

void print(int u, int dis)
{
	if (u == 1) printf("%d ", u);
	else {
		print(pre[u][dis], dis - 1);
		printf("%d ", u);
		return;
	}
}
void toposort(void)
{
	queue<int> q;
	memset(f, 0x3f, sizeof f);
	f[1][1] = 0;
	for (int i = 1; i <= n; ++i)
		if (!inedge[i])
			q.emplace(i);
	while (q.size()) {
		int u = q.front(); q.pop();
		for (auto t : G[u]) {
			--inedge[t.v];
			if (!inedge[t.v])
				q.emplace(t.v);
			for (int i = 2; i <= n; ++i) {
				if (f[u][i - 1] == 0x3f3f3f3f) continue;
				if (f[u][i - 1] + t.w > limit) continue;
				if (f[u][i - 1] + t.w < f[t.v][i]) {
					pre[t.v][i] = u;
					f[t.v][i] = f[u][i - 1] + t.w;
				}
			}
		}
	}
	for (int i = n; i >= 0; --i)
		if (f[n][i] <= limit) {
			printf("%d\n", i);
			print(n, i);
			break;
		}
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> m >> limit;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		G[u].emplace_back(v, w);
		++inedge[v];
	}
	toposort();
	return 0;
}
