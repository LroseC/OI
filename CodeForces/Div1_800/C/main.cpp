#include <queue>
#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using vi32 = std::vector<i32>;
using vi64 = std::vector<i64>;
using PII = std::pair<int, int>;
const int N = 2e5 + 10;

i32 n, m;
vi32 G[N], invG[N];
i32 dis[N], sz[N];
bool vis[N];

void Dijkstra(int S)
{
	std::memset(dis, 0x3f, sizeof dis);
	dis[S] = 0;
	std::priority_queue<PII, std::vector<PII>, std::greater<PII>> heap;
	heap.emplace(0, S);
	for (int i = 1; i <= n; ++i) {
		sz[i] = G[i].size();
	}
	while (heap.size()) {
		int u = heap.top().second; heap.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int v : invG[u]) {
			--sz[v];
			dis[v] = std::min(dis[v], dis[u] + sz[v] + 1);
			heap.emplace(dis[v], v);
		}
	}
}

int main(void)
{
	//Think twice, code once.
#ifndef DEBUG
	std::ios::sync_with_stdio(false);
#endif
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v; read >> u >> v;
		G[u].emplace_back(v);
		invG[v].emplace_back(u);
	}
	Dijkstra(n);
	printf("%d\n", dis[1]);
	return 0;
}
