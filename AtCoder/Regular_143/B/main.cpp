#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;
using vint = std::vector<int>;
using PII = std::pair<int, int>;
const int N = 500 * 500 + 10, mod = 998244353;
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

ModInt fac[N], inv[N];
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
inline ModInt C(int n, int m)
{
	if (n < m || n < 0 || m < 0) return 0;
	return fac[n] * inv[m] * inv[n - m];
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	fac[0] = 1;
	for (int i = 1; i < N; ++i)
		fac[i] = fac[i - 1] * i;
	inv[N - 1] = getInv(fac[N - 1]);
	for (int i = N - 2; i >= 0; --i)
		inv[i] = inv[i + 1] * (i + 1);

	int n; std::cin >> n;
	ModInt res;
	for (int i = 1; i <= n * n; ++i) {
		ModInt o = n * n;
		o = o * C(i - 1, n - 1) * fac[n - 1];
		o = o * C(n * n - i, n - 1) * fac[n - 1];
		o = o * fac[n * n - (n + n - 1)];
		res = res + o;
	}
	std::cout << (fac[n * n] - res).val << '\n';
	return 0;
}
