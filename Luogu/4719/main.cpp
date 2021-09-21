#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
int w[N];
vector<int> G[N];
int idx, sz[N], son[N], dfn[N], fa[N], end[N];

void GetF(int u, int fa)
{
	f[u][0] = 0;
	f[u][1] = w[u];
	for (int v : G[u])
		if (v != fa) {
			GetF(v, u);
			f[u][0] += max(f[v][0], f[v][1]);
			f[u][1] += f[v][0];
		}
}
void GetG(int u, int fa)
{
	for (int v : G[u])
		if (v != fa) {
			g[v][1] = g[u][0] + f[u][0] - max(f[v][0], f[v][1]);
			g[v][0] = max(g[v][1], g[u][1] + f[u][1] - f[v][0]);
			GetG(v, u);
		}
}
void GetSon(int u, int fa)
{
	sz[u] = 1;
	for (int v : G[u])
		if (v != fa) {
			GetSon(v, u);
			sz[u] += sz[v];
			if (sz[v] > sz[son[u]])
				son[u] = v;
		}
}
void GetDFN(int u, int father, int rt)
{
	fa[u] = rt;
	dfn[u] = ++idx;
	if (!son[u]) end[rt] = u;
	else GetDFN(son[u], u, rt);
	for (int v : G[u])
		if (v != fa && v != son[u]) {
			GetDFN(v, u, v);
		}
}

int main(void)
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) w[i] = read();
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	GetF(1, -1);
	GetG(1, -1);
	GetSon(1, -1);
	GetDFN(1, -1);
	Build();
	while (m--) {
		int u = read(), v = read();
	}
}