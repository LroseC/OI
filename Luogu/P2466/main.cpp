#include <vector>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define int long long

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 1010;

struct Egg
{
	int x, y, v;
	bool operator<(const Egg &b) const
	{
		return x < b.x;
	}
};

int n;
int x0;
Egg a[N];
int f[N][N][2];

signed main(void)
{
	n = read(), x0 = read();
	for (int i = 1; i <= n; ++i) a[i].x = read();
	for (int i = 1; i <= n; ++i) a[i].y = read();
	for (int i = 1; i <= n; ++i) a[i].v = read();
	a[++n] = {x0, 0, 0};
	a[0] = {(int)0xcfcfcfcf, 0, 0};
	sort(a + 1, a + 1 + n);
	int ans = 0;
	for (int i = 1; i <= n; ++i) a[i].v += a[i - 1].v;
	for (int i = 1; i <= n; ++i) ans += a[i].y;
	memset(f, 0x3f, sizeof f);
	for (int i = 1; i <= n; ++i)
		if (a[i].x == x0)
			f[i][i][0] = f[i][i][1] = 0;
	for (int len = 2; len <= n; ++len)
		for (int l = 1, r = l + len - 1; r <= n; ++l, ++r) {
			f[l][r][0] = min(f[l][r][0], f[l + 1][r][0] + (a[l + 1].x - a[l].x) * (a[l].v + a[n].v - a[r].v));
			f[l][r][0] = min(f[l][r][0], f[l + 1][r][1] + (a[r].x - a[l].x) * (a[l].v + a[n].v - a[r].v));
			f[l][r][1] = min(f[l][r][1], f[l][r - 1][0] + (a[r].x - a[l].x) * (a[l - 1].v + a[n].v - a[r - 1].v));
			f[l][r][1] = min(f[l][r][1], f[l][r - 1][1] + (a[r].x - a[r - 1].x) * (a[l - 1].v + (a[n].v - a[r - 1].v)));
		}
	printf("%.3lf\n", (ans - min(f[1][n][0], f[1][n][1])) / 1000.0);
	return 0;
}