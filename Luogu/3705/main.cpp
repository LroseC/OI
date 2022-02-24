#include <queue>
#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cstdlib>

using namespace std;

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
} read;

const int N = 210, M = 2 * N * N;

int n, S, T;
int a[N][N], b[N][N];
int idx, head[N], nex[M], to[M], c[M];
double w[M];

void addEdge(int u, int v, double wi, int ci)
{
	nex[++idx] = head[u];
	head[u] = idx;
	to[idx] = v, w[idx] = wi, c[idx] = ci;
}
void add(int u, int v, double w)
{
	addEdge(u, v, w, 1);
	addEdge(v, u, -w, 0);
}

namespace Dinic
{
	int now[N];
	bool vis[N];
	double dis[N];

	bool spfa(void)
	{
		queue<int> q;
		dis[T] = -1e20;
		for (int i = 1; i <= n << 1; ++i)
			dis[i] = -1e20;
		memcpy(now, head, sizeof head);
		memset(vis, 0, sizeof vis);
		q.emplace(S); dis[S] = 0;
		while (q.size()) {
			int u = q.front(); q.pop();
			vis[u] = 0;
			for (int e = head[u]; e; e = nex[e])
				if (c[e] && dis[to[e]] < dis[u] + w[e]) {
					int v = to[e];
					dis[v] = dis[u] + w[e];
					if (!vis[v]) {
						vis[v] = 1;
						q.emplace(v);
					}
				}
		}
		return dis[T] != -1e20;
	}
	int dfs(int u, int flow, double &cost)
	{
		if (u == T) {
			cost += flow * dis[T];
			return flow;
		}
		vis[u] = 1;
		int rest = flow;
		for (int e = now[u]; e && rest; e = nex[e])
			if (c[e] && dis[to[e]] == dis[u] + w[e]) {
				if (vis[to[e]]) continue;
				now[u] = e;
				int tmp = dfs(to[e], min(rest, c[e]), cost);
				if (!tmp) dis[to[e]] = -1e20;
				else {
					rest -= tmp;
					c[e] -= tmp;
					c[e ^ 1] += tmp;
				}
			}
		vis[u] = 0;
		return flow - rest;
	}
	pair<int, double> main(void)
	{
		int res = 0; double cost = 0;
		while (spfa())
			res += dfs(S, INT_MAX, cost);
		return make_pair(res, cost);
	}
}

bool check(double res)
{
	idx = 1; S = N - 1, T = N - 2;
	memset(head, 0, sizeof head);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			add(i, j + n, a[i][j] - res * b[i][j]);
	for (int i = 1; i <= n; ++i) {
		add(S, i, 0);
		add(i + n, T, 0);
	}
	auto t = Dinic::main();
	return t.second >= 0;
}

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			read >> a[i][j];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			read >> b[i][j];
	double l = 0, r = 1e9;
	while (r - l >= 1e-8) {
		double mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%.6lf\n", l);
	return 0;
}
