#include <cstring>
#include <iostream>

using namespace std;

const int N = 351, M = 41;

int n, m;
int cnt[5];
int a[N];
int f[N][M][M][M];

int dp(int i, int c1, int c2, int c3)
{
	int &x = f[i][c1][c2][c3];
	int c4 = (i - 1 - c1 - c2 * 2 - c3 * 3) / 4;
	if (~x) return x;
	if (i - 1 >= 1 && c1)
		x = max(x, dp(i - 1, c1 - 1, c2, c3) + a[i]);
	if (i - 2 >= 1 && c2)
		x = max(x, dp(i - 2, c1, c2 - 1, c3) + a[i]);
	if (i - 3 >= 1 && c3)
		x = max(x, dp(i - 3, c1, c2, c3 - 1) + a[i]);
	if (i - 4 >= 1 && c4)
		x = max(x, dp(i - 4, c1, c2, c3) + a[i]);
	return x;
}

int main(void)
{
	cin >> n >> m;
	memset(f, -1, sizeof f);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= m; ++i) { int x; cin >> x; ++cnt[x]; }
	f[1][0][0][0] = a[1];
	printf("%d\n", dp(n, cnt[1], cnt[2], cnt[3]));
	return 0;
}