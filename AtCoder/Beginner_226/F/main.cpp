#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInputOutput
{
	using FSIO = FastStreamInputOutput;
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
	FSIO& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FSIO& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FSIO& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} io;

const int mod = 998244353;

int n;
int k;
int ans;
int cnt[100];
int stk[100];
int fac[100], inv[100];
int tinv[100];

inline int qpow(int base, int kk)
{
	int res = 1;
	while (kk) {
		if (kk & 1) res = 1ll * res * base % mod;
		kk >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return 1ll * a * b / gcd(a, b); }
inline int C(int n, int m)
{
	if (n > m) return 0;
	return 1ll * fac[m] * inv[n] % mod * inv[m - n] % mod;
}

void dfs(int now, int mintot, int dep)
{
	if (now > n) {
		int res = 1;
		for (int i = 1; i < dep; ++i)
			res = 1ll * res * fac[stk[i] - 1] % mod;
		int tmp = n;
		for (int i = 1; i < dep; ++i) {
			res = 1ll * res * C(stk[i], tmp) % mod;
			tmp -= stk[i];
		}
		tmp = 1;
		for (int i = 2; i < dep; ++i) {
			if (stk[i] == stk[i - 1]) ++tmp;
			else {
				res = 1ll * res * inv[tmp] % mod;
				tmp = 1;
			}
		}
		res = 1ll * res * inv[tmp] % mod;

		int M = stk[1];
		for (int i = 2; i < dep; ++i) M = lcm(M, stk[i]);
		M = qpow(M, k);
		ans = (ans + 1ll * M * res % mod) % mod;
		return;
	}
	for (int i = min(n - now + 1, mintot); i >= 1; --i) {
		stk[dep] = i;
		dfs(now + i, i, dep + 1);
	}
}

signed main(void)
{
	fac[0] = 1;
	for (int i = 1; i <= 60; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	for (int i = 0; i <= 60; ++i) inv[i] = qpow(fac[i], mod - 2);
	for (int i = 0; i <= 60; ++i) tinv[i] = qpow(i, mod - 2);
	io >> n >> k;
	dfs(1, n, 1);
	io << ans << endl;
	return 0;
}