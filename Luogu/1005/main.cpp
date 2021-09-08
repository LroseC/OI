#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

template<typename INT> void write(INT x)
{
	static char buf[50]; int p = -1;
	if (x == 0) { putchar('0'); return; }
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; }
}

typedef __int128 LL;

int n, m;
int a[100];
LL f[100][100];

int main(void)
{
	LL ans = 0;
	n = read(), m = read();
	for (int i = 0; i < n; ++i) {
		memset(f, 0, sizeof f);
		for (int j = 1; j <= m; ++j) a[j] = read();
		LL p = 2;
		LL maxn = 0;
		for (int len = m - 1; len >= 1; --len, p <<= 1)
			for (int l = 1, r; l + len - 1 <= m; ++l) {
				r = l + len - 1;
				if (l != 1) f[l][r] = max(f[l][r], f[l - 1][r] + a[l - 1] * p);
				if (r != m) f[l][r] = max(f[l][r], f[l][r + 1] + a[r + 1] * p);
			}
		for (int i = 1; i <= m; ++i)
			maxn = max(maxn, f[i][i] + a[i] * p);
		ans += maxn;
		// write(f[1][2]), putchar('\n');
	}
	write(ans); putchar('\n');
	return 0;
}