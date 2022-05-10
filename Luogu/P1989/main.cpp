#include <vector>
#include <cctype>
#include <cstdio>

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
const int N = 1e5 + 10;

int n, m;
int inEdge[N], tim[N];
std::vector<int> G[N];
std::vector< std::pair<int, int> > edge;

int main(void)
{
	read >> n >> m;
	for (int i = 1, u, v; i <= m; ++i) {
		read >> u >> v;
		edge.emplace_back(u, v);
		++inEdge[u];
		++inEdge[v];
	}
	auto cmp = [](int u, int v)
	{ return inEdge[u] != inEdge[v] ? inEdge[u] < inEdge[v] : u < v; };
	for (auto t : edge) {
		if (cmp(t.first, t.second))
			G[t.first].emplace_back(t.second);
		else
			G[t.second].emplace_back(t.first);
	}
	int res = 0;
	for (int u = 1; u <= n; ++u) {
		for (int v : G[u]) tim[v] = u;
		for (int v : G[u])
			for (int k : G[v])
				if (tim[k] == u) ++res;
	}
	printf("%d\n", res);
	return 0;
}
