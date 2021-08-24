#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 11, Mod = 9973;

int T;
int m;

struct Matrix
{
	#define Ma Matrix

	int a[N][N];
	Ma() { memset(a, 0, sizeof a); }

	Ma operator*(const Ma &b) const
	{
		Matrix c;
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= m; ++j)
				for (int k = 1; k <= m; ++k)
					c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j] % Mod) % Mod;
		return c;
	}

	#undef Ma
};

int phi(int x)
{
	int res = x;
	for (int d = 2; d * d <= x; ++d)
		if (!(x % d)) {
			res = res / d * (d - 1);
			while (!(x % d)) x /= d;
		}
	if (x > 1) res = res / x * (x - 1);
	return res;
}
int qpow(Matrix base, int k)
{
	Matrix res;
	for (int i = 1; i <= m; ++i) res.a[i][i] = 1;
	while (k) {
		if (k & 1) res = res * base;
		base = base * base;
		k >>= 1;
	}
	int sum = 0;
	for (int i = 1; i <= m; ++i) sum = (sum + res.a[i][i]) % Mod;
	return sum;
}
int qpow(int base, int k)
{
	int res = 1;
	while (k) {
		if (k & 1) res = 1ll * res * base % Mod;
		base = 1ll * base * base % Mod;
		k >>= 1;
	}
	return res;
}

int main(void)
{
	scanf("%d", &T);
	while (T--) {
		int n, k;
		cin >> n >> m >> k;
		Matrix M;
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= m; ++j) {
				M.a[i][j] = 1;
			}
		for (int i = 1; i <= k; ++i) {
			int u, v; scanf("%d%d", &u, &v);
			M.a[u][v] = M.a[v][u] = 0;
		}
		int res = 0;
		for (int d = 1; d * d <= n; ++d)
			if (n % d == 0) {
				res = (res + (1ll * phi(n / d) * qpow(M, d) % Mod)) % Mod;
				if (d * d != n) {
					res = (res + (1ll * phi(d) * qpow(M, n / d) % Mod)) % Mod;
				}
			}
		printf("%d\n", res * qpow(n, Mod - 2) % Mod);
	}
	return 0;
}