#include <cctype>
#include <cstdio>

using namespace std;

const int N = 1e6 + 10, mod = 998244353;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

int n, k;
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
inline int Getinv(int x) { return qpow(x, mod - 2); }
inline int C(int m, int n)
{
	if (m < n) return 0;
	return 1ll * fac[m] * inv[n] % mod * inv[m - n] % mod;
}

int main(void)
{
	freopen("mex.in", "r", stdin);
	freopen("mex.out", "w", stdout);
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = Getinv(fac[N - 1]);
	for (int i = N - 2; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;

	n = read(), k = read();
	int ans = 0;
	for (int i = 1; i <= k; ++i) ans = (ans + 1ll * i * C(n - i - 1, k - i) % mod) % mod;
	ans = 1ll * ans * Getinv(C(n ,k)) % mod;
	write(ans);
	return 0;
}