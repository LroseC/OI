#include <cctype>
#include <cstdio>

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

const int N = 1e7 + 10;
const int mod = 998244353;

int fac[N];
int inv[N];

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
int Getinv(int x)
{
	return qpow(x, mod - 2);
}

int main(void)
{
	fac[0] = 1;
	for (int i = 1; i < N; ++i)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = Getinv(fac[N - 1]);
	for (int i = N - 2; i >= 1; --i)
		inv[i] = 1ll * inv[i + 1] * i % mod;
	inv[0] = inv[1];
	for (int i = 1; i <= 10; ++i)
		printf("inv[%d] = %d\n", i, Getinv(i));

	while (1) {
		int m; IO >> m;
		int res = 0;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < m - i; ++j) {
				int k = m - i - j;
				res += 1ll * inv[i] * inv[j] % mod * inv[k] % mod;
				res = res >= mod ? res - mod : res;
			}
		printf("%d\n", res);
	}
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}
