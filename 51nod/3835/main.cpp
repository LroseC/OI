#include <cctype>
#include <cstdio>
#include <algorithm>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

int qpow(int base, int k, int mod)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % mod;
		k >>= 1;
		base = 1ll * base * base % mod;
	}
	return res % mod;
}

int main(void)
{
	int T; read >> T;
	while (T--) {
		int a, n;
		read >> a >> n;
		int phi = n;
		int x = n;
		for (int i = 2; i * i <= x; ++i)
			if (x % i == 0) {
				phi = phi / i * (i - 1);
				while (x % i == 0)
					x /= i;
			}
		if (x > 1)
			phi = phi / x * (x - 1);
		int res = phi;
		for (int i = 2; i * i <= phi; ++i)
			if (phi % i == 0) {
				while (res % i == 0 && qpow(a, res / i, n) == 1)
					res /= i;
				while (phi % i == 0)
					phi /= i;
			}
		if (phi > 1 && qpow(a, res / phi, n) == 1)
			res /= phi;
		printf("%d\n", res);
	}
	return 0;
}
