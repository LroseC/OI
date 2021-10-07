#include <cmath>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

const int mod = 1e9 + 7;

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

/*
 * 思路：枚举所有的斜率，然后暴力算方案数
 */

int n, X, Y, d;
int fac[(int)1e6], inv[(int)1e6];

inline int sq(int x) { return x * x; }
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
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
inline int getdis(int x1, int y1, int x2, int y2)
{
	int dx = sq(x1 - x2);
	int dy = sq(y1 - y2);
	return dx + dy;
}
inline int C(int m, int n)
{
	if (m < n) return 0;
	return 1ll * fac[m] * inv[n] % mod * inv[m - n] % mod;
}

void dfs(int x, int y, int dx, int dy, int lx, int ly, int cnt, int &ans)
{
	if (cnt == n) {
		++ans;
		return;
	}
	if (x > X || y > Y) return;
	if (getdis(lx, ly, x, y) >= sq(d)) dfs(x + dx, y + dy, dx, dy, x, y, cnt + 1, ans);
	dfs(x + dx, y + dy, dx, dy, lx, ly, cnt, ans);
}

int main(void)
{
	fac[0] = 1;
	for (int i = 1; i < 1e6; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[(int)1e6 - 1] = Getinv(fac[(int)1e6 - 1]);
	for (int i = 1e6 - 2; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;

	int T = read();
	while (T--) {
		int ans = 0;
		n = read(), X = read(), Y = read(), d = read();
		for (int dy = 1; dy <= Y; ++dy)
			for (int dx = 1; dx <= X; ++dx)
				if (gcd(dx, dy == 1)) {
					for (int i = 0; i < dx; ++i)
						for (int j = 0; j <= Y; ++j) {
							int a = ceil(sqrt(1.0 * sq(d) / (sq(dx) + sq(dy))));
							int pointcnt = (X - i) / dx;
							ans += C(pointcnt - (n - 1) * a, n);
							// dfs(i, j, dx, dy, -1000, -1000, 0, ans);
						}
					for (int i = dx; i <= X; ++i)
						for (int j = 0; j < dy; ++j) {
							dfs(i, j, dx, dy, -1000, -1000, 0, ans);
						}
				}
		ans = ans * 2;
		for (int i = 0; i <= Y; ++i)
			dfs(0, i, 1, 0, -1000, -1000, 0, ans);
		for (int i = 0; i <= X; ++i)
			dfs(i, 0, 0, 1, -1000, -1000, 0, ans);
		write(ans);
	}
	return 0;
}