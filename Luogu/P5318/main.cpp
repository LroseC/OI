#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;

struct Edge
{
	int u, v;
	bool operator<(const Edge &b) const
	{
		if (u != b.u) return u < b.u;
		return v > b.v;
	}
};

int n, m;
int idx, head[N], nex[M], to[M];
bool vis[N];
vector<Edge> edge;
queue<int> q;


void AddEdge(int u, int v)
{
	nex[++idx] = head[u];
	head[u] = idx, to[idx] = v;
}
void dfs(int u)
{
	vis[u] = 1;
	printf("%d ", u);
	for (int e = head[u]; e; e = nex[e]) {
		int v = to[e];
		if (vis[v]) continue;
		dfs(v);
	}
}
void bfs(int S)
{
	while (q.size()) q.pop();
	q.push(S);
	vis[S] = 1;
	while (q.size()) {
		int u = q.front(); q.pop();
		printf("%d ", u);
		for (int e = head[u]; e; e = nex[e]) {
			int v = to[e];
			if (vis[v]) continue;
			vis[v] = 1;
			q.push(v);
		}
	}
}

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		edge.emplace_back(Edge({u, v}));
	}
	sort(edge.begin(), edge.end());
	for (auto &a : edge) AddEdge(a.u, a.v);
	dfs(1);
	puts("");
	memset(vis, 0, sizeof vis);
	bfs(1);
	return 0;
}