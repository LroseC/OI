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
const int N = 1e5 + 10, mod = 998244353;
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
};

int n;
std::vector<int> G[N];
ModInt f[N], g[N], ans;

void initF(int u, int fa)
{
	f[u] = G[u].size();
	for (int v : G[u])
		if (v != fa) {
			initF(v, u);
			f[u] = f[u] + f[v];
		}
}
int initG(int u, int fa)
{
	int sz = 1;
	for (int v : G[u])
		if (v != fa) {
			g[v] = f[u] - f[v] + g[u];
			sz += initG(v, u);
		}
	ans = ans + (f[u] + g[u]) * sz * (n - sz);
	return sz;
}
inline ModInt qpow(ModInt base, int k)
{
	ModInt res = 1;
	while (k) {
		if (k & 1) res = res * base;
		k >>= 1;
		base = base * base;
	}
	return res;
}
inline ModInt getInv(ModInt x) { return qpow(x, mod - 2); }

int main(void)
{
	read >> n;
	for (int i = 1, u, v; i < n; ++i) {
		read >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	initF(1, 0);
	initG(1, 0);
	printf("%d\n", (ans * getInv(1ll * n * n % mod)).val);
	return 0;
}
