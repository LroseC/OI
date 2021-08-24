#include <cstdio>
#include <cctype>

using namespace std;

const int N = 351, M = 41;
inline int max(int a, int b) { return a > b ? a : b; }

int n, m;
int cnt[5];
int a[N];
int f[M][M][M][M];

inline int read(void)
{
	register char ch = getchar();
	register int res = 0;
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) {
		res = res * 10 + (ch ^ '0');
		ch = getchar();
	}
	return res;
}

int dp(int c1, int c2, int c3, int c4)
{
	f[c1][c2][c3][c4];
	register int res = a[c1 * 1 + c2 * 2 + c3 * 3 + c4 * 4 + 1];
	if (f[c1][c2][c3][c4]) return f[c1][c2][c3][c4];
	if (c1)
		f[c1][c2][c3][c4] = max(f[c1][c2][c3][c4], dp(c1 - 1, c2, c3, c4) + res);
	if (c2)
		f[c1][c2][c3][c4] = max(f[c1][c2][c3][c4], dp(c1, c2 - 1, c3, c4) + res);
	if (c3)
		f[c1][c2][c3][c4] = max(f[c1][c2][c3][c4], dp(c1, c2, c3 - 1, c4) + res);
	if (c4)
		f[c1][c2][c3][c4] = max(f[c1][c2][c3][c4], dp(c1, c2, c3, c4 - 1) + res);
	return f[c1][c2][c3][c4];
}

int main(void)
{
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= m; ++i) ++cnt[read()];
	f[0][0][0][0] = a[1];
	for (register int c1 = 0; c1 <= cnt[1]; ++c1)
		for (register int c2 = 0; c2 <= cnt[2]; ++c2)
			for (register int c3 = 0; c3 <= cnt[3]; ++c3)
				for (register int c4 = 0; c4 <= cnt[4]; ++c4) {
					register int res = a[c1 * 1 + c2 * 2 + c3 * 3 + c4 * 4 + 1];
					if (c1)
						f[c1][c2][c3][c4] = max(f[c1][c2][c3][c4], f[c1 - 1][c2][c3][c4] + res);
					if (c2)
						f[c1][c2][c3][c4] = max(f[c1][c2][c3][c4], f[c1][c2 - 1][c3][c4] + res);
					if (c3)
						f[c1][c2][c3][c4] = max(f[c1][c2][c3][c4], f[c1][c2][c3 - 1][c4] + res);
					if (c4)
						f[c1][c2][c3][c4] = max(f[c1][c2][c3][c4], f[c1][c2][c3][c4 - 1] + res);
				}
	printf("%d\n", f[cnt[1]][cnt[2]][cnt[3]][cnt[4]]);
	return 0;
}