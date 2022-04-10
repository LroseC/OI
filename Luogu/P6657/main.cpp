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
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

using i64 = long long;
const int mod = 998244353;
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
inline int getInv(int x) { return qpow(x, mod - 2); }

int n, m;
int a[110], b[110];
int matrix[110][110];
int fac[(int)2e6 + 10], inv[(int)2e6 + 10];

inline int C(int n, int m) { return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod; }

int gauss(void)
{
	int res = 1;
	for (int i = 1; i <= m; ++i) {
		for (int j = i + 1; j <= m; ++j) {
			while (matrix[j][i]) {
				int tmp = matrix[i][i] / matrix[j][i];
				res *= -1;
				for (int k = 1; k <= m; ++k) {
					std::swap(matrix[i][k], matrix[j][k]);
					matrix[j][k] = Mod(matrix[j][k] + mod - 1ll * matrix[i][k] * tmp % mod);
				}
			}
		}
	}
	for (int i = 1; i <= m; ++i)
		res = 1ll * res * matrix[i][i] % mod;
	return Mod(res + mod);
}

int main(void)
{
	int T;
	read >> T;
	fac[0] = 1;
	for (int i = 1; i <= 2e6; ++i)
		fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[(int)2e6] = getInv(fac[(int)2e6]);
	for (int i = 2e6 - 1; i >= 0; --i)
		inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
	while (T--) {
		read >> n >> m;
		for (int i = 1; i <= m; ++i)
			read >> a[i] >> b[i];
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= m; ++j) {
				if (a[i] > b[j]) matrix[i][j] = 0;
				else matrix[i][j] = C(n - 1 + b[j] - a[i], b[j] - a[i]);
			}
		printf("%d\n", gauss());
	}
	return 0;
}
