#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 2e5 + 10;

int n, m;
i64 K;
int a[N];
vint G[N];

bool check(int mid)
{
	vint inEdge(n + 1);
	vint dis(n + 1);
	for (int i = 1; i <= n; ++i)
		if (a[i] <= mid)
			for (int v : G[i])
				if (a[v] <= mid)
					++inEdge[v];
	std::queue<int> q;
	for (int i = 1; i <= n; ++i)
		if (a[i] <= mid && !inEdge[i]) {
			dis[i] = 0;
			q.emplace(i);
		}
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int v : G[u])
			if (a[v] <= mid) {
				--inEdge[v];
				dis[v] = std::max(dis[v], dis[u] + 1);
				if (inEdge[v] == 0) q.emplace(v);
			}
	}
	for (int i = 1; i <= n; ++i)
		if (a[i] <= mid) {
			if (dis[i] >= K - 1) return 1;
			if (inEdge[i]) return 1;
		}
	return 0;
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin >> n >> m >> K;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= m; ++i) {
		int u, v;
		std::cin >> u >> v;
		G[u].emplace_back(v);
	}
	int l = 1, r = 1e9, mid;
	while (l < r) {
		mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	if (!check(l)) std::cout << "-1\n";
	else std::cout << l << '\n';
	return 0;
}
