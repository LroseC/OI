#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int mod = 998244353, N = 2e5 + 10;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct ModInt
{
	int val;
	ModInt(void) { val = 0; }
	ModInt(int x) { val = x; }
	ModInt operator+(const ModInt &other) const
	{ return Mod(val + other.val); }
	ModInt operator-(const ModInt &other) const
	{ return Mod(val + mod - other.val); }
	ModInt operator*(const ModInt &other) const
	{ return 1ll * val * other.val % mod; }
};
struct Edge
{
	int v, id;
	Edge(void) {}
	Edge(int _v, int _id) { v = _v, id = _id; }
};

bool vis[N];
int ans[N];
std::vector<Edge> G[N];

void dfs(int u)
{
	vis[u] = 1;
	for (auto e : G[u]) {
		if (ans[e.id >> 1] == -1) {
			ans[e.id >> 1] = e.id & 1;
		}
		if (!vis[e.v])
			dfs(e.v);
	}
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::memset(ans, -1, sizeof ans);
	int n, m;
	std::cin >> n >> m;
	vint a(m), b(m);
	for (int i = 0; i < m; ++i) {
		std::cin >> a[i];
	}
	for (int i = 0; i < m; ++i) {
		std::cin >> b[i];
	}
	for (int i = 0; i < m; ++i) {
		G[a[i]].emplace_back(b[i], i << 1);
		G[b[i]].emplace_back(a[i], i << 1 | 1);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) dfs(i);
	for (int i = 0; i < m; ++i)
		printf("%d", ans[i]);
	puts("");
	return 0;
}
