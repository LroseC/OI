#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
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
const int N = 2e5 + 10;

struct PIII
{
	i64 dis;
	int u, e;
	PIII(void) {}
	PIII(i64 _d, int _u, int _e)
	{ dis = _d, u = _u, e = _e; }

	bool operator<(const PIII &other) const
	{ return dis > other.dis; }
};
struct Edge
{
	int v, w, id;
	Edge(void) {}
	Edge(int _v, int _w, int _id)
	{ v = _v, w = _w, id = _id; }
};
int n, m;
i64 dis[N];
bool vis[N];
std::vector<Edge> G[N];

void dijkstra(int S)
{
	std::priority_queue<PIII> heap;
	std::memset(dis, 0x3f ,sizeof dis);
	dis[S] = 0;
	heap.emplace(dis[S], S, -1);
	while (heap.size()) {
		int u = heap.top().u;
		if (vis[u]) {
			heap.pop();
			continue;
		}
		vis[u] = 1;
		if (heap.top().e != -1) printf("%d ", heap.top().e);
		heap.pop();
		for (auto e : G[u]) {
			if (dis[e.v] > dis[u] + e.w) {
				dis[e.v] = dis[u] + e.w;
				heap.emplace(dis[e.v], e.v, e.id);
			}
		}
	}
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int fir = i * 2 - 1, sec = i * 2;
		int u, v, w;
		read >> u >> v >> w;
		G[u].emplace_back(v, w, i);
		G[v].emplace_back(u, w, i);
	}
	dijkstra(1);
	puts("");
	return 0;
}
