#include <vector>
#include <cctype>
#include <cstdio>
#include <utility>
#include <algorithm>

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

const int N = 3e5 + 10, LG = 20;

struct LineNode
{
	int u, v, len;

	LineNode (int _u, int _v, int _len) { u = _u, v = _v, len = _len; }
	bool operator<(const LineNode &other) const
	{ return len < other.len; }
};
struct Edge
{
	int v, w;
	Edge(int _v, int _w) { v = _v, w = _w; }
};

int n, m;
std::vector<Edge> G[N];
int dep[N], dis[N], fa[N][LG];
std::vector<LineNode> Line;

void getFa(int u)
{
	dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (auto t : G[u])
		if (t.v != fa[u][0]) {
			fa[t.v][0] = u;
			dis[t.v] = dis[u] + t.w;
			getFa(t.v);
		}
}
int LCA(int u, int v)
{
	if (dep[u] < dep[v])
		std::swap(u, v);
	for (int i = LG - 1; i >= 0; --i)
		if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if (u == v) return u;
	for (int i = LG - 1; i >= 0; --i)
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}
int getLen(int u, int v) { return dis[u] + dis[v] - 2 * dis[LCA(u, v)]; }
std::pair<int, int> getIntersection(std::pair<int, int> a, std::pair<int, int> b)
{
	std::vector<int> tmp(4);
	tmp[0] = LCA(a.first, b.first);
	tmp[1] = LCA(a.first, b.second);
	tmp[2] = LCA(a.second, b.first);
	tmp[3] = LCA(a.second, b.second);
	auto cmp = [](int a, int b) { return dep[a] > dep[b]; };
	std::sort(tmp.begin(), tmp.end(), cmp);
	return std::make_pair(tmp[0], tmp[1]);
}
bool check(int x)
{
	int i = Line.size() - 1;
	int maxLen = Line[i].len;
	std::pair<int, int> now = std::make_pair(Line[i].u, Line[i].v);
	--i;
	while (i >= 0 && Line[i].len > x) {
		now = getIntersection(now, std::make_pair(Line[i].u, Line[i].v));
		--i;
	}
	int u = now.first, v = now.second;
	int maxW = 0;
	while (u != v) {
		if (dep[u] < dep[v])
			std::swap(u, v);
		maxW = std::max(maxW, dis[u] - dis[fa[u][0]]);
		u = fa[u][0];
	}
	return maxLen - maxW <= x;
}

int main(void)
{
	read >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		read >> u >> v >> w;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}
	getFa(1);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		read >> u >> v;
		Line.emplace_back(u, v, getLen(u, v));
	}
	std::sort(Line.begin(), Line.end());

	int l = 0, r = 1e9;
	while (l < r) {
		int mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}
