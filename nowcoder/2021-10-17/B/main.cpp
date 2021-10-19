#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e6 + 10, mod = 998244353;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch))  { res = res * 10 + ch - '0'; ch = getchar(); }
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

int n;
int ans = 0;
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
inline int A(int n, int m)
{
	if (m < n) return 0;
	return 1ll * fac[m] * inv[m - n] % mod;
}
inline int C(int n, int m)
{
	if (m < n) return 0;
	return 1ll * fac[m] * inv[n] % mod * inv[m - n] % mod;
}

bool vis[10];
int tmp[10];
void dfs(int dep)
{
	if (dep > n) {
		int res = n + 1;
		for (int i = 1; i <= n; ++i)
			if (i > tmp[i]) {
				res = i;
				break;
			}
		ans = (ans + res) % mod;
		return;
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) {
			vis[i] = 1;
			tmp[dep] = i;
			dfs(dep + 1);
			tmp[dep] = 0;
			vis[i] = 0;
		}
}

int main(void)
{
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = Getinv(fac[N - 1]);
	for (int i = N - 2; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;

	n = read();
	// if (n <= 5) {
		// dfs(1);
		// write(ans);
		// write(1ll * ans * Getinv(A(n, n)) % mod);
	// }
	// else {
	ans = n + 1;
	for (int i = 2; i <= n; ++i) {
		int a = i - 1, b = n - i;
		for (int j = 1; j < i; ++j) {
			int tmp = i;
			tmp = 1ll * tmp * qpow(b + 1, j - 1) % mod;
			tmp = 1ll * tmp * qpow(b + 2, a - j) % mod;
			tmp = 1ll * tmp * fac[b + 1] % mod;
			ans = (ans + tmp) % mod;
		}
	}
	write(1ll * ans * inv[n] % mod);
	return 0;
}