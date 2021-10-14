#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 2010;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) { putchar('0'); }
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

int n, k;
int a[N];
LL f[N][N][2];

/*
 * f[i][j][s] 表示 从 1 到 i 做了 j 次修改并且最后一次是/不是山谷点所能得到的所有方案
 * 性质: 最大值
 */

int main(void)
{
	n = read(), k = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= k; ++j) {
			if (1 < i && i < n && a[i] < a[i - 1] && a[i] < a[i + 1])
				f[i][j][1] = f[i - 1][j][0] + a[i];
			else {
				f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
				if (1 < i && i < n)
					f[i][j][1] = max(f[i][j][0], f[i - 1][j - 1][0] + min(a[i - 1], a[i + 1]) - 1);
			}
		}
	LL ans = 0;
	for (int j = 0; j <= k; ++j)
		ans = max(ans, f[n][j][0]);
	write(ans);
	return 0;
}
