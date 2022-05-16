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

int n, K;
int a[N];
int fac[N], inv[N];

inline int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}
inline int getInv(int x) { return qpow(x, mod - 2); }
inline int C(int n, int m)
{
	if (n < m || n < 0 || m < 0) return 0;
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main(void)
{
	fac[0] = 1;
	for (int i = 1; i < N; ++i)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = getInv(fac[N - 1]);
	for (int i = N - 2; i >= 0; --i)
		inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;

	read >> n >> K;
	for (int i = 1; i <= n; ++i)
		read >> a[i];
	int res = 0;
	for (int bit = 0, tmp = 1; bit < 31; ++bit, tmp <<= 1) {
		int cnt0 = 0, cnt1 = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i] >> bit & 1) ++cnt1;
			else ++cnt0;
		}
		for (int i = 1; i <= cnt1 && i <= K; i += 2)
			res = Mod(res + 1ll * tmp * C(cnt1, i) % mod * C(cnt0, K - i) % mod);
	}
	printf("%d\n", res);
	return 0;
}
