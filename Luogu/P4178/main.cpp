#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

using LL = long long;

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

const int N = 4e4 + 10;
struct Edge
{
	int v, w;
	Edge(void) { v = w = 0; }
	Edge(int _v, int _w) : v(_v), w(_w) {}
};

LL ans;
int n, K, allnode;
int sz[N], dis[N], top;
bool del[N];
vector<Edge> G[N];

void Getroot(int u, int fa, int &root, int &minsize)
{
	sz[u] = 1;
	int sonsize = 0;
	for (auto t : G[u])
		if (t.v != fa && !del[t.v]) {
			Getroot(t.v, u, root, minsize);
			sonsize = max(sonsize, sz[t.v]);
			sz[u] += sz[t.v];
		}
	sonsize = max(sonsize, allnode - sz[u]);
	if (sonsize < minsize) {
		root = u;
		minsize = sonsize;
	}
}
void Getdis(int u, int fa, int dist)
{
	dis[++top] = dist;
	for (auto t : G[u])
		if (!del[t.v] && t.v != fa)
			Getdis(t.v, u, dist + t.w);
}
void calc(int u, int dist, int f, LL &res)
{
	top = 0; Getdis(u, u, dist);
	sort(dis + 1, dis + top + 1);
	for (int i = 1, j = top; i < j; ++i) {
		while (i < j && dis[i] + dis[j] > K)
			--j;
		res += (j - i) * f;
	}
}
void dfs(int u)
{
	LL res = 0;
	del[u] = 1;
	calc(u, 0, 1, res);
	for (auto t : G[u])
		if (!del[t.v]) calc(t.v, t.w, -1, res);
	ans += res;
	for (auto t : G[u])
		if (!del[t.v]) {
			allnode = sz[t.v];
			int root, minsize = 0x3f3f3f3f;
			Getroot(t.v, u, root, minsize);
			dfs(root);
		}
}

int main(void)
{
	read >> n;
	for (int i = 1; i < n; ++i) {
		int u, v, w; read >> u >> v >> w;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}
	read >> K;
	allnode = n;
	int root = 0, minsize = 0x3f3f3f3f;
	Getroot(1, 1, root, minsize);
	dfs(root);
	printf("%lld\n", ans);
	return 0;
}
