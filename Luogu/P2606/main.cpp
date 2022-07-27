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

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using vi32 = std::vector<i32>;
using vi64 = std::vector<i64>;
using PII = std::pair<i32, i32>;
const int N = 1e6 + 10;
i32 mod;
inline i32 Mod(i32 x) { return x >= mod ? x - mod : x; }

struct ModInt
{
	i32 val;
	ModInt(int x = 0) { val = x; }
	ModInt operator+(const ModInt &other) const
	{ return Mod(val + other.val); }
	ModInt operator-(const ModInt &other) const
	{ return Mod(val + mod - other.val); }
	ModInt operator*(const ModInt &other) const
	{ return 1ll * val * other.val % mod; }
	void operator+=(const ModInt &other)
	{ val = Mod(val + other.val); }
	void operator*=(const ModInt &other)
	{ val = 1ll * val * other.val % mod; }
};

i32 n;
i32 sz[N];
ModInt f[N], fac[N], inv[N];
i32 cnt[N], fcnt[N];
u32 pwmod[N];

inline ModInt qpow(ModInt base, i32 k)
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

void dp(int u)
{
	f[u] = 1;
	for (int v = u * 2; v <= u * 2 + 1; ++v) {
		if (v > n) break;
		dp(v);
		sz[u] += sz[v];
		f[u] *= f[v] * inv[sz[v]];
		fcnt[u] += fcnt[v] - cnt[sz[v]];
	}
	f[u] *= fac[sz[u]];
	fcnt[u] += cnt[sz[u]];
	sz[u] += 1;
}

int main(void)
{
	//Think twice, code once.
	read >> n >> mod;
	fac[0] = 1;
	for (int i = mod; i < N; i *= mod) {
		for (int k = i; k < N; k += i) cnt[k] += 1;
	}
	pwmod[0] = 1;
	for (int i = 1; i < N; ++i) pwmod[i] = pwmod[i - 1] * mod;
	for (int i = 1; i < N; ++i) {
		if (i % mod)
			fac[i] = fac[i - 1] * i;
		else {
			fac[i] = fac[i - 1] * (i / pwmod[cnt[i]]);
		}
	}
	inv[N - 1] = getInv(fac[N - 1]);
	for (int i = N - 2; i >= 0; --i) {
		if ((i + 1) % mod)
			inv[i] = inv[i + 1] * (i + 1);
		else
			inv[i] = inv[i + 1] * ((i + 1) / pwmod[cnt[i + 1]]);
	}
	for (int i = 1; i < N; ++i) cnt[i] += cnt[i - 1];
	dp(1);
	printf("%d\n", fcnt[1] ? 0: f[1].val);
	return 0;
}
