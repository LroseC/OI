#include <bits/stdc++.h>

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
} myread;

using i64 = long long;
const int N = 2e5 + 10;

int m, n;
int a[10][N];

int main(void)
{
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	myread >> m >> n;
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j)
			myread >> a[i][j];
	if (m == 2) {
		i64 res = 0;
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= n; ++j)
				res += 1ll * a[i][j] * (n + n);
		printf("%lld\n", res);
	}
	else {
		i64 res = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				int minx = INT_MAX, maxx = INT_MIN;
				for (int k = 1; k <= m; ++k) {
					minx = std::min(minx, a[k][i] + a[k][j]);
					maxx = std::max(maxx, a[k][i] + a[k][j]);
				}
				res += minx + maxx;
			}
		printf("%lld\n", res);
	}
	return 0;
}
