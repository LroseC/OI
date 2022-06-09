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
const int N = 1e3 + 10;

struct Edge
{
	int v, w;
	Edge(void) {}
	Edge(int _v, int _w)
	{ v = _v, w = _w; }
};

int n, m;
bool vis[N], inque[N];
int cnt[N];
i64 dis[N];
std::vector<Edge> G[N];

bool check(void)
{
	std::queue<int> q;
	vis[1] = 1;
	q.emplace(1);
	while (q.size()) {
		int u = q.front(); q.pop();
		for (auto t : G[u])
			if (!vis[t.v]) {
				vis[t.v] = 1;
				q.emplace(t.v);
			}
	}
	return vis[n];
}
int spfa(int S)
{
	std::memset(dis, 0x3f, sizeof dis);
	std::queue<int> q;
	dis[S] = 0;
	q.emplace(S);
	while (q.size()) {
		int u = q.front(); q.pop();
		inque[u] = 0;
		++cnt[u];
		if (cnt[u] > n) return -1;
		for (auto t : G[u]) {
			if (dis[t.v] > dis[u] + t.w) {
				dis[t.v] = dis[u] + t.w;
				if (!inque[t.v]) {
					inque[t.v] = 1;
					q.emplace(t.v);
				}
			}
		}
	}
	return 0;
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		read >> u >> v >> w;
		G[u].emplace_back(v, -w);
	}
	if (spfa(1) == -1 && check())
		puts("Forever love");
	else {
		printf("%lld\n", dis[n]);
	}
	return 0;
}
