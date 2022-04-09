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
const int N = 610;

int n, mod;
int a[N][N];

int main(void)
{
	read >> n >> mod;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			read >> a[i][j];
	int res = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			while (a[i][i]) {
				int tmp = a[j][i] / a[i][i];
				res *= -1;
				for (int k = 1; k <= n; ++k) {
					std::swap(a[i][k], a[j][k]);
					a[i][k] = ((a[i][k] - 1ll * tmp * a[j][k]) % mod + mod) % mod;
				}
			}
			res *= -1;
			for (int k = 1; k <= n; ++k)
				std::swap(a[i][k], a[j][k]);
		}
	}
	for (int i = 1; i <= n; ++i)
		res = 1ll * res * a[i][i] % mod;
	printf("%d\n", (res + mod) % mod);
	return 0;
}
