#include <cmath>
#include <cctype>
#include <cstdio>

using namespace std;


#define int long long

const int N = 2e5 + 10, mod = 1e9 + 7;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template <typename T>
inline void write(T x, char end = '\n')
{
	static char buf[20]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10 + '0'; x /= 10; }
	while (~p) { putchar(buf[p]); --p; } putchar(end);
}

int n;
int a[N];
int x[N], y[N], z[N];

int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}
int getinv(int x)
{
	return qpow(x, mod - 2);
}
int exgcd(int a, int b, int &x, int &y)
{
	if (!b) { x = 1, y = 0; return a; }
	int d = exgcd(b, a % b, x, y);
	int t = y;
	y = x - (a / b * y); x = t;
	return d;
}

signed main(void)
{
	int T = read();
	while (T--) {
		bool issub3 = 1;
		n = read();
		for (int i = 1; i <= n; ++i) {
			x[i] = read(), y[i] = read(), z[i] = read();
			if (x[i] != 1 || y[i] != 1) issub3 = 0;
		}
		if (n == 1) {
			int ans1, ans2;
			int gcd = exgcd(x[1] + y[1], mod, ans1, ans2);
			if (z[1] % gcd) write(0);
			else {
				int k = z[1] / gcd;
				ans1 *= k, ans2 *= k;
				ans1 = (ans1 % mod + mod) % mod;
				write(1);
				write(ans1);
			}
		}
		else if (issub3) {
			int totz = 0;
			for (int i = 1; i <= n; ++i) totz = (totz + z[i]) % mod;
			int sum = 1ll * getinv(n + 1) * totz % mod;
			write(1);
			for (int i = 1; i <= n; ++i) {
				write((z[i] - sum + mod) % mod, ' ');
			}
			puts("");
		}
	}
	return 0;
}