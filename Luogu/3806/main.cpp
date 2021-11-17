#include <cctype>
#include <cstdio>

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

int n, m;
int sz[N];

void get_root(int u, int fa, int &root, int &minsize)
{
	sz[u] = 1; int maxsize = 0;
	for (auto e : G[u]) {
		get_root(e.v, u, root, minsize);
		sz[u] += sz[e.v];
		maxsize = max(maxsize, sz[v]);
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
		io >> K;
		int ans;
		allnode = n;
		int root, minsize = 0x3f3f3f3f;
		get_root(1, 1, root, minsize);
		dfs(root);
		puts(ans ? "AYE" : "NAY");
	}
	return 0;
}