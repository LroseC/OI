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

const int N = 3e5 + 10;
struct PII
{
	int x, y;
	PII(void) { x = y = 0; }
	PII (int _x, int _y) : x(_x), y(_y) {}
};

int n, m;
int TYPE;
int dep[N];
int st[N][30];
vector<int> G[N];

int GetDis(int u, int v)
{
	int res = 0;
	if (dep[u] < dep[v]) swap(u, v);
	for (int k = 29; k >= 0; --k) {
		if (dep[st[u][k]] >= dep[v])
			u = st[u][k], res += 1 << k;
	}
	for (int k = 29; k >= 0; --k) {
		if (st[u][k] != st[v][k])
			u = st[u][k], v = st[v][k], res += 1 << k + 1;
	}
	return res + (u == v ? 0 : 2);
}
namespace UnionFind
{
	int fa[N], sz[N];
	PII diam[N];

	void init(int n)
	{
		for (int i = 1; i <= n; ++i)
			fa[i] = i, sz[i] = 1, diam[i] = PII(i, i);
	}
	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
	int getsz(int x) { return sz[find(x)]; }
	void merge(int x, int y)
	{
		x = find(x), y = find(y);
		if (sz[x] > sz[y]) swap(x, y);
		static int tmp[10];
		tmp[1] = diam[x].x; tmp[2] = diam[x].y;
		tmp[3] = diam[y].x; tmp[4] = diam[y].y;
		for (int i = 1; i <= 4; ++i)
			for (int j = i; j <= 4; ++j) {
				if (GetDis(tmp[i], tmp[j]) > GetDis(diam[y].x, diam[y].y)) {
					diam[y].x = tmp[i];
					diam[y].y = tmp[j];
				}
			}
		fa[x] = y; sz[y] += sz[x];
	}
}
int Get(int x)
{
	int u = UnionFind::find(x);
	auto t = UnionFind::diam[u];
	return max(GetDis(x, t.x), GetDis(x, t.y));
}
void dfs(int u, int fa)
{
	st[u][0] = fa;
	dep[u] = dep[fa] + 1;
	for (int k = 1; k < 30; ++k)
		st[u][k] = st[st[u][k - 1]][k - 1];
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
	}
}
//void Update(int x, int y)
//{
//	static int tmp[10];
//	int u = UnionFind::find(x);
//	int v = UnionFind::find(y);
//	auto t1 = UnionFind::diam[u];
//	auto t2 = UnionFind::diam[v];
//	tmp[1] = t1.x; tmp[2] = t1.y;
//	tmp[3] = t2.x; tmp[4] = t2.y;
//	auto &t = UnionFind::diam[u];
//	int ans = GetDis(t.x, t.y);
//	for (int i = 1; i <= 4; ++i)
//		for (int j = i + 1; j <= 4; ++j)
//			if (GetDis(tmp[i], tmp[j]) > ans) {
//				ans = GetDis(tmp[i], tmp[j]);
//				t = PII(tmp[i], tmp[j]);
//			}
//	UnionFind::diam[v] = t;
//}

int main(void)
{
	io >> TYPE;
	io >> n >> m;
	UnionFind::init(n);
	for (int i = 1; i <= n; ++i)
		dep[i] = 1;
	int lastans = 0;
	while (m--) {
		static int op, x, y;
		io >> op >> x;
		if (TYPE) x ^= lastans;
		if (op == 1) {
			io >> y;
			if (TYPE) y ^= lastans;
			if (UnionFind::getsz(x) > UnionFind::getsz(y)) swap(x, y);
			G[x].emplace_back(y);
			G[y].emplace_back(x);
			dfs(x, y);
			UnionFind::merge(x, y);
		}
		else {
			int u = UnionFind::find(x);
			printf("%d\n", lastans = Get(x));
		}
	}
	return 0;
}
