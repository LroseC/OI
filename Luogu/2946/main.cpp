#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

typedef long long LL;
const int N = 2010, M = 1010, Mod = 1e8;

int n, m;
LL f[N][M];

int main(void)
{
	n = read(), m = read();
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		int x = read();
		x %= m;
		for (int j = 0; j < m; ++j) f[i][j] = f[i - 1][j];
		for (int j = 0; j < m; ++j)
			f[i][(j + x) % m] = (f[i][(j + x) % m] + f[i - 1][j]) % Mod;
	}
	// for (int i = 1; i <= n; ++i, puts(""))
	// 	for (int j = 0; j <= m; ++j)
	// 		printf("%d ", f[i][j]);
	printf("%lld\n", f[n][0] - 1);
	return 0;
}