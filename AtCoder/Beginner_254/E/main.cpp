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
const int N = 2e5 + 10;

int n, m;
int dis[N];
int stk[N], top;
std::vector<int> G[N];

int bfs(int u, int lim)
{
	std::queue<int> q;
	dis[u] = 0;
	q.emplace(u);
	int res = 0;
	while (q.size()) {
		int u = q.front(); q.pop();
		res += u;
		for (int v : G[u])
			if (dis[v] == -1 && dis[u] < lim) {
				dis[v] = dis[u] + 1;
				stk[++top] = v;
				q.emplace(v);
			}
	}
	dis[u] = -1;
	while (top) {
		dis[stk[top--]] = -1;
	}
	return res;
}

int main(void)
{
	std::memset(dis, -1, sizeof dis);
	read >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	int q; read >> q;
	while (q--) {
		int u, lim;
		read >> u >> lim;
		printf("%d\n", bfs(u, lim));
	}
	return 0;
}
