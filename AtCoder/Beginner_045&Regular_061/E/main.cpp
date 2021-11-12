#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;
#define int long long

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
} io;

const int N = 1e6 + 10;
struct Edge
{
	int v, val;
	Edge(void) : v(0), val(0) {}
	Edge(int _v, int _val) : v(_v), val(_val) {}
	bool operator<(const Edge &other) const
	{
		return v < other.v;
	}
};
struct node
{
	Edge state; int dis;
	node(void) : state(0, 0), dis(0) {}
	node(int _u, int _val, int _dis) : state(_u, _val), dis(_dis) {}
	bool operator<(const node &other) const
	{
		return dis > other.dis;
	}
};

int n, m;
int ans = 0x3f3f3f3f;
map<Edge, bool> vis;
map<Edge, int> dis;
vector<Edge> G[N];
int DIS[N];

int Dij(void)
{
	priority_queue<node> heap;
	heap.emplace(node(1, -1, 0));
	while (heap.size()) {
		auto t = heap.top(); heap.pop();
		if (vis[t.state]) continue;
		vis[t.state] = 1;
		for (auto e : G[t.state.v]) {
			int val = e.val != t.state.val;
			DIS[e.v] = min(DIS[e.v], dis[t.state] + val);
			if (!dis.count(e) || dis[t.state] + val < dis[e]) {
				dis[e] = dis[t.state] + val;
				heap.emplace(node(e.v, e.val, dis[t.state] + val));
			}
		}
	}
	return 0;
}

namespace other
{
	int dis[N];
	bool vis[N];
	set<int> c[N];
	inline void Dijkstra() {
		priority_queue< pair < int, int > > q;
		memset(dis, 0x3f, sizeof(dis));
		memset(vis, 0, sizeof(vis));
		dis[1] = 0;
		q.push(make_pair(0, 1));
		while(!q.empty()) {
			int x = q.top().second; q.pop();
			if(vis[x])	continue;
			vis[x] = 1;
			for (auto e : G[x]) {
				int y = e.v, v = c[x].count(e.val) ? 0 : 1;
				if(dis[y] > dis[x] + v) {
					dis[y] = dis[x] + v;
					q.push(make_pair(-dis[y], y));
					c[y].clear();
					c[y].insert(e.val);
				} else if(dis[y] == dis[x] + v)	c[y].insert(e.val);
			}
		}
	}
}

signed main(void)
{
	io >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, val; io >> u >> v >> val;
		G[u].emplace_back(Edge(v, val));
		G[v].emplace_back(Edge(u, val));
	}
	memset(DIS, 0x3f, sizeof DIS);
	Dij();
	printf("%lld\n", DIS[n] >= 0x3f3f3f3f3f3f ? -1 : DIS[n]);
	return 0;
}