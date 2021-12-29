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
} IO;

using LL = long long;
const int N = 1e5 + 10;
const int M = 5e5 + 10;

struct Edge
{
	int u, v, lim, w;
	bool operator<(const Edge &other)
	{
		return w < other.w;
	}
};

int n, m;
int fa[N];
Edge edge[M];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main(void)
{
	IO >> n >> m;
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1; i <= m; ++i) {
		IO >> edge[i].u >> edge[i].v >> edge[i].lim >> edge[i].w;
	}
	sort(edge + 1, edge + 1 + m);
	LL ans = 0;
	int edgecnt = 0;
	for (int i = 1; i <= m; ++i) {
		if (edgecnt == n - 1) break;
		for (int j = 0; j < edge[i].lim; ++j) {
			int u = edge[i].u + j;
			int v = edge[i].v + j;
			u = find(u), v = find(v);
			if (u != v) {
				fa[u] = v;
				ans += edge[i].w;
				++edgecnt;
			}
			if (edgecnt == n - 1) break;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
