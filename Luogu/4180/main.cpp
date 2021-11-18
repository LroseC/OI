#include <vector>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <functional>

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
struct PII
{
	int x, y;
	PII(void) : x(0), y(0) {}
	PII(int x, int y) : x(x), y(y) {}
};
struct Edge
{
	int v, w;
	Edge(void) : v(0), w(0) {}
	Edge(int v, int w) : v(v), w(w) {}
};
struct Edge1
{
	int u, v, w;
	Edge1(void) : u(0), v(0), w(0) {}
	Edge1(int u, int v, int w) : u(u), v(v), w(w) {}
	bool operator<(const Edge1 &other) const
	{
		return w < other.w;
	}
};

using LL = long long;
const int N = 1e5 + 10, M = 3e5 + 10, S = 20;

int n, m;
Edge1 alledge[M];
bool used[M];
int dep[N];
int fa[N][S];
PII val[N][S];
vector<Edge> G[N];
LL tot, ans = 0x3f3f3f3f3f3f3f3f;
namespace UnionFind
{
	int fa[N];
	void init(int n)
	{
		for (int i = 1; i <= n; ++i)
			fa[i] = i;
	}
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	void merge(int x, int y) { fa[find(x)] = find(y); }
}

PII merge(PII a, PII b)
{
	if (a.x < b.x) swap(a, b);
	if (a.x == b.x) return PII(a.x, max(a.y, b.y));
	else return PII(a.x, max(a.y, b.x));
}
void GetFa(int u, int fath, int depth)
{
	dep[u] = depth;
	for (int k = 1; k < S; ++k) {
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
		val[u][k] = merge(val[u][k - 1], val[fa[u][k - 1]][k - 1]);
	}
	for (auto e : G[u]) {
		if (e.v == fath) continue;
		fa[e.v][0] = u;
		val[e.v][0] = {e.w, -1};
		GetFa(e.v, u, depth + 1);
	}
}
PII LCA(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	PII res(-1, -1);
	for (int k = S - 1; k >= 0; --k)
		if (dep[fa[u][k]] >= dep[v]) {
			res = merge(res, val[u][k]);
			u = fa[u][k];
		}
	for (int k = S - 1; k >= 0; --k)
		if (fa[u][k] != fa[v][k]) {
			res = merge(res, val[u][k]);
			res = merge(res, val[v][k]);
			u = fa[u][k];
			v = fa[v][k];
		}
	if (u != v) {
		res = merge(res, val[u][0]);
		res = merge(res, val[v][0]);
	}
	return res;
}

int main(void)
{
	io >> n >> m;
	UnionFind::init(n);
	for (int i = 1; i <= m; ++i) {
		int u, v, w; io >> u >> v >> w;
		alledge[i] = Edge1(u, v, w);
	}
	sort(alledge + 1, alledge + 1 + m);
	for (int i = 1; i <= m; ++i) {
		int u = alledge[i].u, v = alledge[i].v, w = alledge[i].w;
		if (UnionFind::find(u) != UnionFind::find(v)) {
			tot += w;
			used[i] = 1;
			UnionFind::merge(u, v);
			G[u].emplace_back(v, w);
			G[v].emplace_back(u, w);
		}
	}
	GetFa(1, 0, 1);
	for (int i = 1; i <= m; ++i)
		if (!used[i]) {
			int u = alledge[i].u, v = alledge[i].v, w = alledge[i].w;
			if (u == v) continue;
			auto t = LCA(u, v);
			if (t.x != w)
				ans = min(ans, tot - t.x + w);
			else if (t.y != -1)
				ans = min(ans, tot - t.y + w);
		}
	printf("%lld\n", ans);
	return 0;
}