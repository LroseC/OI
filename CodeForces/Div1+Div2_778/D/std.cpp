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

int v[N], prime[N], invPrime[N], idx;
std::vector<std::pair<int, PII>> G[N];
ModInt inv[N];

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
inline void minx(int &a, int b)
{ a = std::min(a, b); }
void getPrime(int n)
{
	idx = 0;
	std::fill(v + 1, v + 1 + n, 0);
	for (int i = 2; i <= n; ++i) {
		if (!v[i]) {
			v[i] = i;
			invPrime[i] = idx;
			prime[idx++] = i;
		}
		for (int j = 0; j < idx && i * prime[j] <= n; ++i) {
			v[i * prime[j]] = prime[j];
			if (v[i] == prime[j]) break;
		}
	}
}
void dfs(int u, int fa, ModInt mul, ModInt &sum, vint &t, vint &index)
{
	sum = sum + mul;
	for (auto e : G[u])
		if (e.first != fa) {
			ModInt tomul = mul * e.second.first * inv[e.second.second];
			for (int x = e.second.first; x != 1; x /= v[x]) {
				++t[invPrime[v[x]]];
			}
			for (int x = e.second.second; x != 1; x /= v[x]) {
				--t[invPrime[v[x]]];
				minx(index[invPrime[v[x]]], t[invPrime[v[x]]]);
			}
			dfs(e.first, u, tomul, sum, t, index);
			for (int x = e.second.first; x != 1; x /= v[x]) {
				--t[invPrime[v[x]]];
			}
			for (int x = e.second.second; x != 1; x /= v[x]) {
				++t[invPrime[v[x]]];
			}
		}
}
int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	int tt; std::cin >> tt;
	while (tt--) {
		int n; std::cin >> n;
		getPrime(n);
		vint a(n);
		for (int i = 1; i <= n; ++i) G[i].clear();
		for (int i = 1; i <= n; ++i) inv[i] = getInv(i);
		for (int i = 1; i < n; ++i) {
			int u, v, x, y;
			std::cin >> u >> v >> x >> y;
			G[u].emplace_back(v, std::make_pair(y, x));
			G[v].emplace_back(u, std::make_pair(x, y));
		}
		ModInt mul = 1, sum = 0;
		vint index(idx), t(idx);
		dfs(1, 1, mul, sum, t, index);
		for (int i = 0; i < index.size(); ++i) {
			if (index[i]) sum = sum * qpow(prime[i], -index[i]);
		}
		std::cout << sum.val << '\n';
	}
	return 0;
}
