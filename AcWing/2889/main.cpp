#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5010;

int n;
int w[N], s[N];
int f[N][N], p[N][N];

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &w[i]), s[i] = s[i - 1] + w[i];
	for (int i = 1; i <= n; ++i) p[i][i] = i;
	for (int len = 2; len <= n; ++len)
		for (int l = 1; l + len - 1 <= n; ++l) {
			int r = l + len - 1;
			f[l][r] = 1e9;
			for (int k = p[l][r - 1]; k <= p[l + 1][r]; ++k) {
				int t = f[l][k] + f[k + 1][r] + s[r] - s[l - 1];
				if (f[l][r] > t) {
					f[l][r] = t;
					p[l][r] = k;
				}
			}
		}
	printf("%d\n", f[1][n]);
}