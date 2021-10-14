#include <cctype>
#include <cstdio>

using namespace std;

const int N = 5e5 + 10, mod = 998244353;

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
int ans;
int a[N];
int fac[N];

int main(void)
{
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	n = read(), k = read();
	if (k == 1) {
		write(1);
		return 0;
	}
	fac[0] = 1;
	for (int i = 1; i <= k; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1, j = 1; j <= n; ++j) {
		if (j > 1 && a[j - 1] > a[j]) i = j;
		if (j - i + 1 == k)
			ans = (ans + fac[k]) % mod;
		else if (j - i + 1 > k)
			ans = ((ans + fac[k] - fac[k - 1]) % mod + mod) % mod;
	}
	write(ans);
	return 0;
}