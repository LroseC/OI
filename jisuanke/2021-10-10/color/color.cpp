#include <cctype>
#include <cstdio>

using namespace std;

const int mod = 1145140019;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-'); f = -1; ch = getchar(); }
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

inline int init(void)
{
	return 0;
}
inline int work(void)
{
	int n = read(), m = read(), lp = read(), lq = read(), rp = read(), rq = read();
	if (!lp && rp == rq) {
		write(1);
		return 0;
	}
	else if (1ll * lp * rq == 1ll * lq * rp) {
		write(0);
		return 0;
	}
	else {
		int l = 1ll * lp * Getinv(lq) % mod, r = 1ll * rp * Getinv(rq) % mod;
		if (m == n) {
			int d = ((qpow(r, n + 1) - qpow(l, n + 1)) % mod + mod) % mod;
			write(d);
			return 0;
		}
		else {
			l = (1ll - l + mod) % mod, r = (1ll - r + mod) % mod;
			int d = ((qpow(r, n + 1) - qpow(l, n + 1)) % mod + mod) % mod;
			write((-d + mod) % mod);
			return 0;
		}
	}
	return 0;
}
int main(void)
{
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	int T = read();
	while (T--) {
		init();
		work();
	}
	return 0;
}