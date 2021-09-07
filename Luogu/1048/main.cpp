#include <vector>
#include <cctype>
#include <cstdio>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
int f[1010][1010];

int main(void)
{
	m = read(), n = read();
	for (int i = 1; i <= n; ++i) {
		int t = read(); int v = read();
		for (int j = t; j <= m; ++j)
			f[i][j] = max(f[i][j], f[i - 1][j - t] + v);
		for (int j = 1; j <= m; ++j)
			f[i][j] = max(f[i][j], f[i - 1][j]);
	}
	int ans = 0;
	printf("%d\n", f[n][m]);
	return 0;
}