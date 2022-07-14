#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 1e5 + 10, LG = 30;

struct Edge
{
	int u, v, w;
	Edge(void) {}
	Edge(int _u, int _v, int _w)
	{ u = _u, v = _v, w = _w; }
};

int n, m;
int fa[LG][N], flag[LG][N];

int find(int id, int u)
{ return fa[id][u] == u ? u : fa[id][u] = find(id, fa[id][u]); }
void merge(int id, int u, int v)
{
	u = find(id, u);
	v = find(id, v);
	if (u != v) fa[id][u] = v;
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin >> n >> m;
	for (int i = 0; i < 30; ++i)
		for (int j = 1; j <= n; ++j)
			fa[i][j] = j;
	std::vector<Edge> edge;
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		edge.emplace_back(u, v, w);
		for (int i = 0; i < 30; ++i)
			if (w >> i & 1) merge(i, u, v);
	}
	for (auto e : edge) {
		if (!(e.w & 1)) {
			for (int i = 1; i < 30; ++i) {
				flag[i][find(i, e.u)] = 1;
				flag[i][find(i, e.v)] = 1;
			}
		}
	}
	int Q; std::cin >> Q;
	while (Q--) {
		int u, v; std::cin >> u >> v;
		int ans = 2;
		for (int i = 0; i < 30; ++i) {
			if (find(i, u) == find(i, v)) {
				ans = 0;
			}
			if (flag[i][find(i, u)]) {
				ans = std::min(ans, 1);
			}
		}
		std::cout << ans << '\n';
	}
	return 0;
}
