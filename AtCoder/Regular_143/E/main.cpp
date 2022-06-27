#include <queue>
#include <vector>
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

int n, totSz;
char str[N];
int inEdge[N], sz[N];
vint e[N], G[N];

void getSz(int u, int fa)
{
	sz[u] = str[u] == 'W';
	for (int v : G[u])
		if (v != fa) {
			getSz(v, u);
			sz[u] += sz[v];
		}
}
void dfs(int u, int fa)
{
	for (int v : G[u])
		if (v != fa) {
			dfs(v, u);
			if (sz[v] & 1) {
				++inEdge[u];
				e[v].emplace_back(u);
			}
		}
	if ((totSz - sz[u]) & 1) {
		++inEdge[u];
		e[fa].emplace_back(u);
	}
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	std::cin >> str + 1;
	for (int i = 1; i <= n; ++i) {
		if (str[i] == 'W') ++totSz;
	}
	if ((totSz & 1) == 0) {
		puts("-1");
		return 0;
	}
	getSz(1, 0);
	dfs(1, 0);
	std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
	for (int i = 1; i <= n; ++i)
		if (!inEdge[i]) heap.emplace(i);
	while (heap.size()) {
		int u = heap.top(); heap.pop();
		printf("%d ", u);
		for (int v : e[u]) {
			--inEdge[v];
			if (inEdge[v] == 0) heap.emplace(v);
		}
	}
	puts("");
	return 0;
}
