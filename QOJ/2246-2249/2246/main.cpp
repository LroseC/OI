#include <set>
#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>

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
const int N = 510;

struct Edge
{
	int v, w;
	Edge(void) {}
	Edge(int _v, int _w) { v = _v, w = _w; }
};

int n, m;
int dis[N];
bool vis[N];
std::set<int> lim[N];
std::vector<Edge> G[N];

void dijkstra(int u)
{
	std::priority_queue< PII, std::vector<PII>, std::greater<PII> > heap;
	std::memset(vis, 0, sizeof vis);
	std::memset(dis, 0x3f, sizeof dis);
	dis[u] = 0;
	heap.emplace(std::make_pair(0, u));
	while (heap.size()) {
		int u = heap.top().second;
		heap.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto e : G[u])
			if (!vis[e.v] && dis[e.v] > dis[u] + e.w) {
				bool flag = lim[e.v].find(dis[u] + e.w) != lim[e.v].end();
				if (dis[e.v] > dis[u] + e.w + flag) {
					dis[e.v] = dis[u] + e.w + flag;
					heap.emplace(std::make_pair(dis[e.v], e.v));
				}
			}
	}
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		read >> u >> v >> w;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}
	for (int i = 1; i <= n; ++i) {
		int tmp; read >> tmp;
		for (int j = 0; j < tmp; ++j) {
			int t; read >> t;
			lim[i].insert(t);
		}
	}
	dijkstra(1);
	printf("%d\n", dis[n]);
	return 0;
}
