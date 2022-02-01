#include <cctype>
#include <cstdio>

#define int long long
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
} IO;

const int N = 1e5 + 10, mod = 998244353;

int n, K, inv;
int a[N];

int calc(int x)
{
	if (x < 0) return 0;
	int res = 1;
	for (int i = x + 1; i <= x + K - 1; ++i)
		res = 1ll * res * (i % mod) % mod;
	res = 1ll * res * inv % mod;
	return res;
}

int qpow(int base, int k)
{
	int res = 1;
	base %= mod;
	while (k) { 
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res;
}

signed main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	scanf("%lld%lld\n", &n, &K);
	inv = 1;
	for (int i = 1; i <= K - 1; ++i)
		inv = 1ll * inv * i % mod;
	inv = qpow(inv, mod - 2);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", &a[i]);
	for (int i = 2; i <= n; ++i)
		a[1] -= a[i];
	a[1] -= K;
	int ans = 1;
	for (int i = 1; i <= n; ++i)
		ans = 1ll * ans * calc(a[i]) % mod;
	printf("%lld\n", ans);
	return 0;
}
/*
   简单组合数: 把除 1 之外每种球划分成 K 份的方案乘在一起, 然后乘上 1 的数量减去总球数再减去 K 后剩余数量分成 K 份的方案.
*/
