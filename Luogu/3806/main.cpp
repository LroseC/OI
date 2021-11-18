#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>

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
} io;

const int N = 1e4 + 10;

struct Edge
{
	int v, w;
	Edge(void) : v(0), w(0) {}
	Edge(int v, int w) : v(v), w(w) {}
};

int n, m, allnode;
int cnt[N];
int sz[N], K[N];
bool del[N], exist[N];
vector<Edge> G[N];

void get_root(int u, int fa, int &root, int &minsize)
{
	sz[u] = 1; int maxsize = 0;
	for (auto e : G[u]) {
		if (e.v == fa || del[e.v]) continue;
		get_root(e.v, u, root, minsize);
		sz[u] += sz[e.v];
		maxsize = max(maxsize, sz[e.v]);
	}
	maxsize = max(maxsize, allnode - sz[u]);
	if (maxsize < minsize) {
		root = u;
		minsize = maxsize;
	}
}
int stk[N], top;
void get_dis(int u, int fa, int dis)
{
	stk[++top] = dis;
	for (auto e : G[u]) {
		if (e.v == fa || del[e.v]) continue;
		get_dis(e.v, u, dis + e.w);
	}
}
void calc(int u, int d, int f)
{
	top = 0;
	get_dis(u, u, d);
	sort(stk + 1, stk + 1 + top);
	for (int id = 1; id <= m; ++id) {
		if (exist[id]) continue;
		for (int i = 1, j = top; i < j; ++i) {
			while (i < j && stk[i] + stk[j] > K[id]) --j;
			while (i < j && stk[i] + stk[j] == K[id]) {
				--j;
				cnt[id] += f;
			}
		}
	}
}
void dfs(int u)
{
	del[u] = 1;
	calc(u, 0, 1);
	for (auto e : G[u]) {
		if (del[e.v]) continue;
		calc(e.v, e.w, -1);
	}
	for (int i = 1; i <= m; ++i) {
		if (cnt[i]) exist[i] = 1;
	}
	for (auto e : G[u]) {
		if (del[e.v]) continue;
		allnode = sz[e.v];
		int root, minsize = 0x3f3f3f3f;
		get_root(e.v, u, root, minsize);
		dfs(root);
	}
}

int main(void)
{
	io >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v, w; io >> u >> v >> w;
		G[u].emplace_back(Edge(v, w));
		G[v].emplace_back(Edge(u, w));
	}
	for (int i = 1; i <= m; ++i) {
		io >> K[i];
	}
	allnode = n;
	int root, minsize = 0x3f3f3f3f;
	get_root(1, 1, root, minsize);
	dfs(root);
	for (int i = 1; i <= m; ++i) {
		if (exist[i]) puts("AYE");
		else puts("NAY");
	}
	return 0;
}