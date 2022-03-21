#include <cctype>
#include <cstdio>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int N = 1e6 + 10;

int n, x, mod, m;
int a[N];
int C[1010][1010];

inline int Mod(int x) { return x >= mod ? x - mod : x; }
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
int f(int x)
{
	int res = 0;
	for (int i = 0; i <= m; ++i)
		res = Mod(res + 1ll * a[i] * qpow(x, i) % mod);
	return res;
}

int main(void)
{
//	freopen("problem.in", "r", stdin);
//	freopen("problem.out", "w", stdout);
	read >> n >> x >> mod >> m;
	if (m == 0) {
		int a;
		read >> a;
		printf("%d\n", 1ll * qpow(x + 1, n) * a % mod);
	}
	else if (n <= 1000) {
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= i; ++j) {
				C[i][j] = j == 0 ? 1 : Mod(C[i - 1][j - 1] + C[i - 1][j]);
			}
		for (int i = 0; i <= m; ++i) {
			read >> a[i];
			a[i] %= mod;
		}
		int res = 0;
		for (int k = 0; k <= n; ++k)
			res = Mod(res + 1ll * f(k) * qpow(x, k) % mod * C[n][k] % mod);
		printf("%d\n", res);
	}
	return 0;
}
