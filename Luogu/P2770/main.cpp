#include <map>
#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>

const int N = 1e4 + 10, M = 1e5 + 10;

int n, m, S = N - 1, T = N - 2;
int idx = 1, head[N], nex[M], to[M], fl[M], w[M];
bool vis[N];
std::string cityName[110];
std::map<std::string, int> mp;

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

namespace Dinic
{
	bool vis[N];
	int dis[N], now[N];

	bool SPFA(void)
	{
		std::queue<int> q;
		std::memset(dis, 0xcf, sizeof dis);
		std::memcpy(now, head, sizeof head);
		dis[S] = 0;
		q.emplace(S);
		while (q.size()) {
			int u = q.front(); q.pop();
			vis[u] = 0;
			for (int e = head[u]; e; e = nex[e])
				if (fl[e] && dis[to[e]] < dis[u] + w[e]) {
					dis[to[e]] = dis[u] + w[e];
					if (!vis[to[e]]) {
						vis[to[e]] = 1;
						q.emplace(to[e]);
					}
				}
		}
		return dis[T] != dis[0];
	}
	int dfs(int u, int flow, int &cost)
	{
		if (u == T) {
			cost += dis[T] * flow;
			return flow;
		}
		vis[u] = 1;
		int rest = flow;
		for (int e = now[u]; rest && e; e = nex[e])
			if (fl[e] && dis[to[e]] == dis[u] + w[e] && !vis[to[e]]) {
				now[u] = e;
				int tmp = dfs(to[e], std::min(fl[e], rest), cost);
				if (!tmp) dis[to[e]] = 0xcfcfcfcf;
				rest -= tmp;
				fl[e] -= tmp;
				fl[e ^ 1] += tmp;
			}
		vis[u] = 0;
		return flow - rest;
	}
	int main(int &res, int &cost)
	{
		while (SPFA())
			res += dfs(S, INT_MAX, cost);
		return 0;
	}
}

void dfs(int u, std::vector<int> &ans)
{
	if (u == T) return;
	if (1 <= u && u <= n) {
		vis[u] = 1;
		ans.emplace_back(u);
	}
	for (int e = head[u]; e; e = nex[e])
		if (to[e] != S && fl[e ^ 1] && !vis[to[e]]) {
			dfs(to[e], ans);
			return;
		}
}

int main(void)
{
	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		std::cin >> cityName[i];
		mp[cityName[i]] = i;
	}
	for (int i = 1; i <= m; ++i) {
		std::string a, b;
		std::cin >> a >> b;
		int u = mp[a], v = mp[b];
		if (u > v) std::swap(u, v);
		addFlow(u + n, v, 0x3f3f3f3f, 0);
	}
	for (int i = 1; i <= n; ++i)
		addFlow(i, i + n, 1 + (i == 1 || i == n), 1);
	addFlow(S, 1, 2, 0);
	addFlow(n + n, T, 2, 0);
	int ans = 0, cost = 0;
	Dinic::main(ans, cost);
	if (ans != 2) {
		puts("No Solution!");
		return 0;
	}
	else {
		std::cout << cost - 2 << std::endl;
		std::vector<int> ans1, ans2;
		dfs(1, ans1);
		dfs(1, ans2);
		for (int v : ans1)
			std::cout << cityName[v] << std::endl;
		for (int j = ans2.size() - 1; j >= 0; --j)
			std::cout << cityName[ans2[j]] << std::endl;
	}
	return 0;
}
