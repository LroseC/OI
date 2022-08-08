#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <climits>
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

using i32 = int;
using i64 = long long;
using PII = std::pair<i32, i32>;
using PLI = std::pair<i64, i32>;
using PLL = std::pair<i64, i64>;
const int N = 1e5 + 10;

struct Edge
{
	i32 v, w;
	Edge(i32 _v, i32 _w)
	{ v = _v, w = _w; }
};
struct Edge2
{
	i32 u, v, w;
	Edge2(i32 _u, i32 _v, i32 _w)
	{ u = _u, v = _v, w = _w; }
};

i32 n, m, K;
std::vector<Edge> G[N];
std::vector<Edge2> edge;
bool vis[N];
i32 pos[100];
i64 dis[30][N];
std::priority_queue<PLI, std::vector<PLI>, std::greater<PLI>> heap;

void dij(i64 dis[])
{
	std::memset(vis, 0, sizeof vis);
	while (heap.size()) {
		i32 u = heap.top().second;
		heap.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto e : G[u])
			if (!vis[e.v] && dis[e.v] > dis[u] + e.w) {
				dis[e.v] = dis[u] + e.w;
				heap.emplace(dis[e.v], e.v);
			}
	}
}

int main(void)
{
	//Think twice, code once.
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		i32 u, v, w;
		read >> u >> v >> w;
		w *= 2;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
		edge.emplace_back(u, v, w);
	}
	read >> K;
	for (int i = 1; i <= K; ++i)
		read >> pos[i];
	K += 1;
	pos[K] = 1;
	std::memset(dis, 0x3f, sizeof dis);
	for (int k = 1; k <= K; ++k) {
		dis[k][pos[k]] = 0;
		heap.emplace(0, pos[k]);
		dij(dis[k]);
	}
	i64 res = LLONG_MAX;
	for (int i = 1; i <= n; ++i) {
		i64 t = LLONG_MIN;
		for (int k = 1; k <= K; ++k)
			t = std::max(t, dis[k][i]);
		res = std::min(res, t);
	}
	for (auto e : edge) {
		std::vector<PLL> d(K);
		std::vector<i64> max;
		for (int k = 1; k <= K; ++k) {
			d[k - 1] = std::make_pair(dis[k][e.u], dis[k][e.v]);
		}
		std::sort(d.begin(), d.end());
		max.resize(d.size());
		for (int i = K - 1; i >= 0; --i) {
			if (i == K - 1) max[i] = d[i].second;
			else {
				i64 ds = (e.w + d[i].first + max[i + 1]) / 2;
				ds = std::max(ds, d[i].first);
				ds = std::max(ds, max[i + 1]);
				res = std::min(res, ds);
				max[i] = std::max(max[i + 1], d[i].second);
			}
		}
	}
	printf("%lld\n", res);
	return 0;
}
