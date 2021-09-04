#include <cstdio>

using namespace std;

const int N = 60, T = 2510;

int n, m, t;
int f[N][T][3];
char pur[N][N];

template<typename Int> Int max(Int a, Int b) { return a > b ? a : b; }
template<typename Int> Int max(Int a, Int b, Int c) { return max(max(a, b), c); }

int main(void)
{
	scanf("%d%d%d", &n, &m, &t);
	for (int i = 1; i <= n; ++i) scanf("%s", pur[i] + 1);
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (j == 1) {
				for (int k = 1; k <= t; ++k) {
					f[j][k][0] = max(f[m][k - 1][0], f[m][k - 1][1], f[m][k - 1][2]) + (pur[i][j] == '0');
					f[j][k][1] = max(f[m][k - 1][1], f[m][k - 1][0], f[m][k - 1][2]) + (pur[i][j] == '1');
					f[j][k][2] = max(f[m][k][2], f[m][k][0], f[m][k][1]);
				}
			}
			else {
				for (int k = 1; k <= t; ++k) {
					f[j][k][0] = max(f[j - 1][k][0], f[j - 1][k - 1][1], f[j - 1][k - 1][2]) + (pur[i][j] == '0');
					f[j][k][1] = max(f[j - 1][k][1], f[j - 1][k - 1][0], f[j - 1][k - 1][2]) + (pur[i][j] == '1');
					f[j][k][2] = max(f[j - 1][k][2], f[j - 1][k][0], f[j - 1][k][1]);
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < 3; ++i) ans = max(ans, f[m][t][i]);
	printf("%d\n", ans);
	return 0;
}