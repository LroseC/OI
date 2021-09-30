#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 410;

int n, m;
int G[N][N];
int sum[N][N];
int ans = 0x3f3f3f3f;

int get(int a, int b, int c, int d)
{
	return sum[c][d] - sum[a - 1][d] - sum[c][b - 1] + sum[a - 1][b - 1];
}

int main(void)
{
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		// for (int i = 1; i <= n; ++i)
		// 	for (int j = 1; j <= m; ++j) {
		// 		do G[i][j] = getchar();
		// 		while (G[i][j] != '0' && G[i][j] != '1');
		// 		G[i][j] -= '0';
		// 	}
		// for (int i = 1; i <= n; ++i)
		// 	for (int j = 1; j <= m; ++j)
		// 		sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + G[i][j];

		int cnt = 0;
		for (int r = 5; r <= n; ++r)
			for (int c = 4; c <= m; ++c)
				for (int i = 1; i + r - 1 <= n; ++i)
					for (int j = 1; j + c - 1 <= m; ++j) {
						++cnt;
						int res = 0;
						res += (c - 2) - get(i, j + 1, i, c + j - 2);
						res += (c - 2) - get(i + r - 1, j + 1, i + r - 1, c + j - 2);
						res += (r - 2) - get(i + 1, j, i + r - 2, j);
						res += (r - 2) - get(i + 1, j + c - 1, i + r - 2, j + c - 1);
						res += get(i + 1, j + 1, i + r - 2, j + c - 2);
						ans = min(ans, res);
					}
		printf("%d\n", cnt);
	}
	return 0;
}