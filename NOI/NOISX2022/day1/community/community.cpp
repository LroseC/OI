#include <set>
#include <queue>
#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10, M = 2e6 + 10;

int n, m, S = N - 1, T = N - 2;
int idx = 1, head[N], nex[M], to[M], fl[M], w[M];
int name[N];
std::vector<int> point[N];
set<string> Set;
std::vector<string> names;
string s1[M], s2[M], s3[M];

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
	int now[N], dis[N];
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
		for (int i = 1; i <= n << 1; ++i)
			printf("dis[%d] = %d\n", i, dis[i]);
		printf("dis[S] = %d, dis[T] = %d\n", dis[S], dis[T]);
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
				int tmp = dfs(to[e], std::min(rest, fl[e]), cost);
				if (!tmp)
					dis[to[e]] = 0xcfcfcfcf;
				rest -= tmp;
				fl[e] -= tmp;
				fl[e ^ 1] += tmp;
			}
		vis[u] = 0;
		return flow - rest;
	}
	void main(int &res, int &cost)
	{
		while (SPFA())
			res += dfs(S, INT_MAX, cost);
	}
}

bool dfs(int u)
{
	return 0;
}

void work(void)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		string t;
		cin >> t;
		Set.insert(t);
		names.emplace_back(t);
	}
	for (int i = 1; i <= m; ++i)
		cin >> s1[i] >> s2[i] >> s3[i];
	std::sort(names.begin(), names.end());
	names.erase(std::unique(names.begin(), names.end()), names.end());
	for (int i = 1; i <= m; ++i) {
		name[i] = std::lower_bound(names.begin(), names.end(), s1[i]) - names.begin();
		point[name[i]].emplace_back(i);
	}
	for (int i = 1; i <= m; ++i) {
		addFlow(S, i << 1, 1, 0);
		addFlow(i << 1, i << 1 | 1, 1, 0);
		addFlow(i << 1 | 1, T, 1, 0);
		if (s3[i] == "loushang" && Set.count(s2[i])) {
			int n2 = std::lower_bound(names.begin(), names.end(), s2[i]) - names.begin();
			for (int v : point[n2]) {
				cout << i << ' ' << v << endl;
				addFlow(i << 1 | 1, v << 1, 1, 1);
			}
		}
		if (s3[i] == "louxia" && Set.count(s2[i])) {
			int n2 = std::lower_bound(names.begin(), names.end(), s2[i]) - names.begin();
			for (int v : point[n2]) {
				cout << i << ' ' << v << endl;
				addFlow(v << 1 | 1, i << 1, 1, 1);
			}
		}
	}
	int flow = 0, cost = 0;
	puts("???");
	dinic::main(flow, cost);
	std::cout << flow << ',' << cost << '\n';
	while (dfs(S));

	idx = 1;
	for (int i = 1; i <= n; ++i)
		point[i].clear();
	std::memset(head, 0, sizeof head);
	Set.clear();
	names.clear();
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		work();
	}
	return 0;
}
