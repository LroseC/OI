#include <cctype>
#include <cstdio>

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
const int N = 2e3 + 10, mod = 998244353;
inline int Mod(int x) { return x >= mod ? x - mod : x; }

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

int n, K;
int x[N], y[N];

int main(void)
{
	read >> n >> K;
	for (int i = 1; i <= n; ++i)
		read >> x[i] >> y[i];
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		int son = 1, mom = 1;
		for (int j = 1; j <= n; ++j)
			if (i != j) {
				son = 1ll * son * Mod(K + mod - x[j]) % mod;
				mom = 1ll * mom * Mod(x[i] + mod - x[j]) % mod;
			}
		res = Mod(res + 1ll * y[i] * son % mod * qpow(mom, mod - 2) % mod);
	}
	printf("%d\n", res);
	return 0;
}
