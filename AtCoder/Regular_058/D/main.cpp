#include <cctype>
#include <cstdio>

using namespace std;

struct FastStreamInput
{
	using FSI = FastStreamInput;
	template<typename T>
	FSI& operator >> (T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
} cin;

const int N = 3e5 + 10;
const int mod = 1e9 + 7;

int n, m, a, b;
int fac[N];
int inv[N];

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
inline int C(int n, int m)
{
	if (n > m) return 0;
	return 1ll * fac[m] * inv[n] % mod * inv[m - n] % mod;
}

int main(void)
{
	fac[0] = 1;
	for (int i = 1; i < N ; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = Getinv(fac[N - 1]);
	for (int i = N - 2; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
	cin >> n >> m >> a >> b;
	int ans = 0;
	for (int i = 0; i < n - a; ++i) {
		int tmp = C(i, i + (b - 1));
		tmp = 1ll * tmp * C((n - 1 - i), (n - 1 - i) + (m - b - 1)) % mod;
		ans = (ans + tmp) % mod;
	}
	printf("%d\n", ans);
	return 0;
}