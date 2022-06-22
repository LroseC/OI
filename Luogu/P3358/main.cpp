#include <queue>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
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
using PII = std::pair<int, int>;
const int N = 1e5 + 10, M = 1e6 + 10;

int n, K, S = N - 1, T = N - 2;
PII line[N];
int idx = 1, head[N], nex[M], to[M], fl[M], w[M];

void addEdge(int u, int v, int f, int wi)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, fl[idx] = f, w[idx] = wi;
}
void addFlow(int u, int v, int f, int w)
{
	addEdge(u, v, f, w);
	addEdge(v, u, 0, -w);
}

namespace dinic
{
	bool vis[N];
	int dis[N], now[N];
	void SPFA(void)
	{
		std::queue<int> q;
		std::memset(dis, 0xcf, sizeof dis);
		std::memcpy(now, head, sizeof head);
		dis[S] = 0; q.emplace(S);
		while (q.size()) {
			int u = q.front(); q.pop();
			vis[u] = 0;
			for (int e = head[u]; e; e = nex[e])
				if (fl[e] && dis[u] + w[e] > dis[to[e]]) {
					dis[to[e]] = dis[u] + w[e];
					if (!vis[to[e]]) {
						vis[to[e]] = 1;
						q.emplace(to[e]);
					}
				}
		}
		return dis[T] != 0xcfcfcfcf;
	}
	int dfs(int u, int flow, int &cost)
	{
		if (u == T) {
			cost += flow * dis[T];
			return flow;
		}
		vis[u] = 1;
		int rest = flow;
		for (int e = now[u]; rest && e; e = nex[e])
			if (fl[e] && dis[to[e]] == dis[u] + w[e] && !vis[to[e]]) {
				now[u] = e;
				int tmp = dfs(to[e], std::min(rest, fl[e]), cost);
				if (!tmp) 
			}
		vis[u] = 0;
	}
	void main(int &res, int &cost)
	{
		while (SPFA()) {
			res += dfs(S, INT_MAX, cost);
		}
	}
}

int main(void)
{
	read >> n >> K;
	for (int i = 1; i <= n; ++i) {
		read >> line[i].first >> line[i].second;
		addFlow(S, line[i].first, 1, 0);
		addFlow(line[i].second, T, 1, 0);
		addFlow(line[i].first, line[i].second, 1, line[i].second - line[i].first);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (line[i].second < line[j].first) {
				addFlow(line[i].second, line[j].first, 1, 0);
			}
		}
	}
	int res = 0, cost = 0;
	dinic::main(res, cost);
	printf("%d\n", cost);
	return 0;
}
