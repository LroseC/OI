#include <cmath>
#include <vector>
#include <cctype>
#include <cstdio>
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

using i64 = long long;
const int N = 50, M = 10010, mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct Edge
{
	int u, v, w;
};

int n, m, ans;
Edge edge[M];
bool tmpVis[N];
std::vector<int> tmpG[N], G[N];
int stk[N];
int rt[N];
int id[N][N];
std::vector<int> Circle;

namespace UnionFind
{
	void init(int n)
	{
		for (int i = 1; i <= n; ++i)
			rt[i] = i;
	}
}
int find(int x)
{
	using namespace UnionFind;
	return rt[x] == x ? x : rt[x] = find(rt[x]);
}

void tmpDfs(int u);
bool check(void);
void dfs(int id);

bool instk[N];
int top, nstk[N];
bool getCircle(int u, int fa)
{
	if (instk[u]) {
		int bak = u;
		do {
			Circle.emplace_back(id[nstk[top]][u]);
			u = nstk[top];
			--top;
		} while (u != bak);
		return 1;
	}
	nstk[++top] = u;
	instk[u] = 1;
	for (int v : G[u])
		if (v != fa)
			if (getCircle(v, u)) return 1;
	return 0;
}

int main(void)
{
//	freopen("count.in", "r", stdin);
//	freopne("count.out", "w", stdout);
	read >> n >> m;
	if (m < n - 1) {
		puts("0");
		return 0;
	}
	for (int i = 1; i <= m; ++i)
		read >> edge[i].u >> edge[i].v >> edge[i].w;
	if (!check()) {
		puts("0");
		return 0;
	}
	if (m <= 15) {
		dfs(1);
		printf("%d\n", ans);
	}
	else if (m == n - 1) {
		int sumw = 0;
		for (int i = 1; i <= m; ++i)
			sumw = Mod(sumw + edge[i].w);
		int d = edge[1].w;
		for (int i = 2; i <= m; ++i)
			d = std::__gcd(d, edge[i].w);
		printf("%lld\n", 1ll * sumw * d % mod);
	}
	else if (m == n) {
		for (int i = 1; i <= m; ++i) {
			int u = edge[i].u, v = edge[i].v;
			G[u].emplace_back(v);
			G[v].emplace_back(u);
			id[u][v] = id[v][u] = i;
		}
		getCircle(1, 0);
		for (int nowId : Circle) {
			int sumw = 0;
			for (int i = 1; i <= m; ++i)
				if (i != nowId)
					sumw = Mod(sumw + edge[i].w);
			int d = 0;
			for (int i = 1; i <= m; ++i)
				if (i != nowId)
					d = (d == 0 ? edge[i].w : std::__gcd(d, edge[i].w));
			ans = (ans + 1ll * sumw * d) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}




void tmpDfs(int u)
{
	tmpVis[u] = 1;
	for (int v : tmpG[u])
		if (!tmpVis[v]) tmpDfs(v);
}
bool check(void)
{
	for (int i = 1; i <= m; ++i) {
		tmpG[edge[i].u].emplace_back(edge[i].v);
		tmpG[edge[i].v].emplace_back(edge[i].u);
	}
	tmpDfs(1);
	for (int i = 1; i <= n; ++i)
		if (!tmpVis[i]) return 0;
	return 1;
}
void dfs(int id)
{
	if (id == n) {
		UnionFind::init(n);
		for (int i = 1; i < n; ++i) {
			int u = edge[stk[i]].u;
			int v = edge[stk[i]].v;
			if (find(u) == find(v))
				return;
			else
				rt[find(u)] = find(v);
		}
		int sumw = 0;
		for (int i = 1; i < n; ++i)
			sumw = Mod(sumw + edge[stk[i]].w);
		int d = edge[stk[1]].w;
		for (int i = 2; i < n; ++i)
			d = std::__gcd(d, edge[stk[i]].w);
		ans = (ans + 1ll * sumw * d) % mod;
		return;
	}
	for (int i = stk[id - 1] + 1; i <= m - n + id + 1; ++i) {
		stk[id] = i;
		dfs(id + 1);
	}
}
