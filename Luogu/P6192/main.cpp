#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

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

using i64 = long long;
using PII = std::pair<int, int>;
const int N = 110;

int n, m, K;
int key[10];
int G[N][N];
bool vis[N];
int f[110][1 << 10];
std::priority_queue< PII, std::vector<PII>, std::greater<PII> > q;

void dijkstra(int id)
{
	while (q.size()) {
		auto t = q.top(); q.pop();
		int u = t.second;
		if (vis[u]) continue;
		vis[u] = 1;
		for (int v = 1; v <= n; ++v)
			if (!vis[v] && f[v][id] > f[u][id] + G[u][v]) {
				f[v][id] = f[u][id] + G[u][v];
				q.emplace(f[v][id], v);
			}
	}
	std::memset(vis, 0, sizeof vis);
}

int main(void)
{
	read >> n >> m >> K;
	std::memset(G, 0x3f, sizeof G);
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		read >> u >> v >> w;
		G[u][v] = G[v][u] = std::min(G[u][v], w);
	}
	std::memset(f, 0x3f, sizeof f);
	for (int i = 0; i < K; ++i) {
		read >> key[i];
		f[key[i]][1 << i] = 0;
	}
	for (int s = 1; s < 1 << K; ++s) {
		for (int i = 1; i <= n; ++i) {
			for (int sp = (s - 1) & s; sp; sp = (sp - 1) & s)
				f[i][s] = std::min(f[i][s], f[i][sp] + f[i][s ^ sp]);
			if (f[i][s] != 0x3f3f3f3f)
				q.emplace(f[i][s], i);
		}
		dijkstra(s);
	}
	printf("%d\n", f[key[0]][(1 << K) - 1]);
	return 0;
}