#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <functional>

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
const int N = 1e5 + 10;

struct Edge
{
	int v, w;
	Edge(void) {}
	Edge(int _v, int _w) { v = _v, w = _w; }
};
struct PLI
{
	i64 first;
	int second;
	PLI (void) {}
	PLI (i64 _f, int _s) { first = _f, second = _s; }
	bool operator<(const PLI &other) const
	{ return first > other.first; }
};

int n, m, K;
int a[N];
i64 ans = LLONG_MAX;
bool vis[N], isKey[N];
i64 dis[N];
std::vector<Edge> G[N];

void solve(int k)
{
	std::memset(vis, 0, sizeof vis);
	std::memset(dis, 0x3f, sizeof dis);
	std::priority_queue<PLI> heap;
	for (int i = 1; i <= n; ++i)
		if (((i >> k) & 1) && isKey[i]) {
			dis[i] = 0;
			heap.emplace(0, i);
		}
	while (heap.size()) {
		int u = heap.top().second; heap.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto t : G[u])
			if (!vis[t.v] && dis[t.v] > dis[u] + t.w) {
				dis[t.v] = dis[u] + t.w;
				PLI tmp(dis[t.v], t.v);
				heap.emplace(dis[t.v], t.v);
			}
	}
	for (int i = 1; i <= n; ++i)
		if (dis[i] && isKey[i]) {
			ans = std::min(ans, dis[i]);
		}
	std::memset(vis, 0, sizeof vis);
	std::memset(dis, 0x3f, sizeof dis);
	for (int i = 1; i <= n; ++i)
		if ((i >> k & 1) == 0 && isKey[i]) {
			dis[i] = 0;
			heap.emplace(0, i);
		}
	while (heap.size()) {
		int u = heap.top().second; heap.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto t : G[u])
			if (!vis[t.v] && dis[t.v] > dis[u] + t.w) {
				dis[t.v] = dis[u] + t.w;
				PLI tmp(dis[t.v], t.v);
				heap.emplace(dis[t.v], t.v);
			}
	}
	for (int i = 1; i <= n; ++i)
		if (dis[i] && isKey[i]) ans = std::min(ans, dis[i]);
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		read >> n >> m >> K;
		for (int i = 1, u, v, w; i <= m; ++i) {
			read >> u >> v >> w;
			G[u].emplace_back(v, w);
		}
		for (int i = 1; i <= K; ++i) {
			read >> a[i];
			isKey[a[i]] = 1;
		}
		for (int i = 0; i < 17; ++i)
			solve(i);
		printf("%lld\n", ans);
		ans = LLONG_MAX;
		for (int i = 1; i <= n; ++i)
			G[i].clear();
		for (int i = 1; i <= K; ++i)
			isKey[a[i]] = 0;
	}
	return 0;
}
