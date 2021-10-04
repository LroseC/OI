#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1510;

int n, m, k;
int cnt = 0;
int vis[110];
int a[N][N];
int ans = 0;

int main(void)
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			scanf("%d", &a[i][j]);

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			int tmp = min(n - i + 1, m - j + 1);
			for (int d = 1; d <= tmp; ++d) {
				cnt = 0;
				memset(vis, 0, sizeof vis);
				int dx = i + d - 1, dy = j + d - 1;
				for (int x = i; x <= dx; ++x)
					for (int y = j; y <= dy; ++y) {
						if (!vis[a[x][y]]) ++cnt;
						vis[a[x][y]] = 1;
					}
				if (cnt > k) break;
				if (cnt == k) ++ans;
			}
		}
	printf("%d\n", ans);
	return 0;
}
