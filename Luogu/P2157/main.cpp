#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;
const int INF = 0x3f3f3f3f;

int n;
int type[N], b[N];
int f[1010][256][17];

int main(void)
{
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d%d", &type[i], &b[i]);

		memset(f, 0x3f, sizeof f);
		f[1][0][7] = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < 1 << 8; ++j)
				for (int k = -8; k <= 7; ++k)
					if (f[i][j][k + 8] != INF) {
						if (j & 1) f[i + 1][j >> 1][k + 7] = min(f[i + 1][j >> 1][k + 7], f[i][j][k + 8]);
						else {
							int lim = INF;
							for (int l = 0; l < 8; ++l) {
								if (!(j >> l & 1)) {
									if (i + l > lim) break;
									lim = min(lim, b[i + l] + i + l);
									f[i][j | (1 << l)][l + 8] = min(f[i][j | (1 << l)][l + 8], f[i][j][k + 8] + (i + k > 0 ? (type[i + k] ^ type[i + l]) : 0));
								}
							}
						}
					}
		int ans = INF;
		for (int i = 0; i < 8; ++i)
			ans = min(ans, f[n + 1][0][i]);
		printf("%d\n" ,ans);
	}
}