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
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;
const int mod = 998244353, N = 5010;;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

struct ModInt
{
	int val;

	ModInt(void) {}
	ModInt(int x) { val = x; }
	ModInt operator+(const ModInt &other) const
	{ return Mod(val + other.val); }
	ModInt operator-(const ModInt &other) const
	{ return Mod(val + mod - other.val); }
	ModInt operator*(const ModInt &other) const
	{ return 1ll * val * other.val % mod; }
	int operator()(void) { return val; }
};

int n, m;
ModInt fArray[N];
ModInt *f[N];
ModInt g[N];
ModInt *now = fArray;
std::vector<int> G[N];
int maxDep[N], son[N];

void initCut(int u, int fa)
{
	for (int v : G[u])
		if (v != fa) {
			initCut(v, u);
			if (maxDep[v] > maxDep[son[u]])
				son[u] = v;
			maxDep[u] = std::max(maxDep[u], maxDep[v]);
		}
	++maxDep[u];
}
void dp(int u, int fa)
{
	f[u] = ++now;
	if (son[u]) {
		dp(son[u], u);
		f[u][0] = 0;
		for (int j = 0; j < maxDep[son[u]] && j <= m; ++j)
			f[u][0] = f[u][0] + f[son[u]][j];
	}
	else f[u][0] = 1;
	for (int v : G[u])
		if (v != son[u] && v != fa) {
			dp(v, u);
			for (int i = 0; i < maxDep[u] && i <= m; ++i) {
				g[i] = f[u][i];
				f[u][i] = 0;
			}
			for (int i = 0; i < maxDep[u] && i <= m; ++i) {
				for (int j = 0; j < maxDep[v] && j <= m; ++j) {
					f[u][i] = f[u][i] + g[i] * f[v][j];
					if (i + j + 1 <= m)
						f[u][std::max(i, j + 1)] = f[u][std::max(i, j + 1)] + g[i] * f[v][j];
				}
			}
		}
}

int main(void)
{
	read >> n >> m;
	for (int i = 1, u, v; i < n; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	initCut(1, 0);
	dp(1, 0);
	ModInt res = 0;
	for (int i = 0; i <= m && i < maxDep[1]; ++i)
		res = res + f[1][i];
	printf("%d\n", res());
	return 0;
}
