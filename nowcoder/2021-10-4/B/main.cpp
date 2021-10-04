#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2010, mod = 998244353;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
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
inline int Getinv(int x)
{
	return qpow(x, mod - 2);
}

int n;
int a[N];
int fac[(int)1e5 + 10];
int inv[(int)1e5 + 10];
int f[N][N];
int Max[N][N];
bool vis[N][N];
int cost[N][N];

inline int C(int m, int n)
{
	return 1ll * fac[m] * inv[n] % mod * inv[m - n] % mod;
}

int dp(int l, int r)
{
	if (vis[l][r]) return f[l][r];
	vis[l][r] = 1;
	if (r - l == 1) {
		cost[l][r] = 0;
		return f[l][r] = 1;
	}
	for (int k = l + 1; k <= r - 1; ++k) {
		int get = C(max(k - l - 1, r - k - 1) + min(k - l - 1, r - k - 1), min(k - l - 1, r - k - 1));
		int time = 1ll * dp(l, k) * dp(k, r) % mod * get % mod;
		int c = cost[l][k] + cost[k][r] + Max[l + 1][k - 1] + Max[k + 1][r - 1];
		if (c < cost[l][r]) {
			cost[l][r] = c;
			f[l][r] = time;
		}
		else if (c == cost[l][r]) f[l][r] = (f[l][r] + time) % mod;
	}
	return f[l][r];
}

int main(void)
{
	fac[0] = 1;
	for (int i = 1; i <= 1e5; ++i) fac[i] = 1ll * i * fac[i - 1] % mod;
	inv[(int)1e5] = Getinv(fac[(int)1e5]);
	for (int i = 1e5 - 1; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;

	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; ++j)
			Max[i][j] = max(Max[i][j - 1], a[j]);
	memset(cost, 0x3f, sizeof cost);
	printf("%d\n", dp(0, n + 1));
	return 0;
}
