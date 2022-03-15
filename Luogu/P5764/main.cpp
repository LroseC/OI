#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

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

const int N = 5e4 + 10;

struct Edge
{
	int v, w;
	Edge(void) { v = w = 0; }
	Edge(int _v, int _w) { v = _v, w = _w; }
};

struct PII
{
	int dis, u;

	PII(void) { dis = u = 0; }
	PII(int _d, int _u) { dis = _d, u = _u; }
	bool operator<(const PII &other) const
	{
		return dis > other.dis;
	}
};

int n, m;
long long ans = INT_MAX;
int dis[10][N];
bool vis[N], inque[N];
int pos[10];
vector<Edge> G[N];

void Dij(int S, int dis[])
{
	priority_queue<PII> heap;
	memset(vis, 0, sizeof vis);
	memset(inque, 0, sizeof inque);
	dis[S] = 0;
	heap.emplace(0, S);
	while (heap.size()) {
		auto tmp = heap.top(); heap.pop();
		int u = tmp.u;
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto t : G[u]) {
			if (vis[t.v]) continue;
			if (dis[t.v] > dis[u] + t.w) {
				dis[t.v] = dis[u] + t.w;
				heap.emplace(dis[t.v], t.v);
			}
		}
	}
}

int stk[10];
int order[10];
bool used[10];

void dfs(int id)
{
	if (id > 5) {
		long long res = 0;
		order[0] = 1;
		for (int i = 1; i <= 5; ++i)
			order[i] = pos[stk[i]];
		for (int i = 1; i <= 5; ++i)
			res += dis[stk[i]][order[i - 1]];
//		for (int i = 1; i <= 5; ++i)
//			printf("i = %d, stk[i] = %d, tpos[i] = %d\n", i, stk[i], pos[stk[i]]);
//		printf("res = %lld\n", res);
		ans = min(ans, res);
		return;
	}
	for (int i = 1; i <= 5; ++i)
		if (!used[i]) {
			used[i] = 1;
			stk[id] = i;
			dfs(id + 1);
			used[i] = 0;
		}
}

int main(void)
{
	read >> n >> m;
	memset(dis, 0x3f, sizeof dis);
	for (int i = 1; i <= 5; ++i)
		read >> pos[i];
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		read >> u >> v >> w;
		G[v].emplace_back(u, w);
		G[u].emplace_back(v, w);
	}
	for (int i = 1; i <= 5; ++i)
		Dij(pos[i], dis[i]);
//	for (int i = 1; i <= 5; ++i)
//		for (int j = 1; j <= n; ++j)
//			printf("dis %d->%d = %d\n", j, pos[i], dis[i][j]);
	dfs(1);
	printf("%lld\n", ans);
	return 0;
}
