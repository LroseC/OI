#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

using LL = long long;
const int N = 310, S = 1 << 8;

int n, k;
int digit[N];
int score[S], M[S];
LL f[N][N][S], inf_min;

int main(void)
{
	ios::sync_with_stdio(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> digit[i];
	for (int i = 0; i < 1 << k; ++i)
		cin >> M[i] >> score[i];

	memset(f, 0xcf, sizeof f);
	memset(&inf_min, 0xcf, sizeof inf_min);
	for (int i = 1; i <= n; ++i)
		f[i][i][digit[i]] = 0;
	for (int len = 2; len <= n; ++len)
		for (int l = 1, r = len; r <= n; ++l, ++r) {
			int x = (len - 1) % (k - 1) + 1;
			if (x == 1) x = k;
			for (int mid = r - 1; mid >= l; mid -= k - 1)
				for (int state = 0; state < 1 << x - 1; ++state) {
					if (x != k) {
						f[l][r][state << 1] = max(f[l][r][state << 1], f[l][mid][state] + f[mid + 1][r][0]);
						f[l][r][state << 1 | 1] = max(f[l][r][state << 1 | 1], f[l][mid][state] + f[mid + 1][r][1]);
					}
					else {
						f[l][r][M[state << 1]] = max(f[l][r][M[state << 1]], f[l][mid][state] + f[mid + 1][r][0] + score[state << 1]);
						f[l][r][M[state << 1 | 1]] = max(f[l][r][M[state << 1 | 1]], f[l][mid][state] + f[mid + 1][r][1] + score[state << 1 | 1]);
					}
				}
		}
	LL ans = inf_min;
	for (int i = 0; i < 1 << k; ++i)
		ans = max(ans, f[1][n][i]);
	printf("%lld\n", ans);
	return 0;
}