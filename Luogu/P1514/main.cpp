#include <cstring>
#include <iostream>

using namespace std;

const int N = 510;

int n, m;
int h[N][N];
bool vis[N][N];
int l[N][N], r[N][N];
int gox[] = {-1, 0, 1, 0};
int goy[] = {0, 1, 0, -1};

void dfs(int x, int y)
{
	vis[x][y] = 1;
	for (int i = 0; i < 4; ++i) {
		int xx = x + gox[i];
		int yy = y + goy[i];
		if (xx < 1 || yy < 1 || xx > n || yy > m) continue;
		if (h[xx][yy] >= h[x][y]) continue;
		if (!vis[xx][yy]) dfs(xx, yy);
		l[x][y] = min(l[x][y], l[xx][yy]);
		r[x][y] = max(r[x][y], r[xx][yy]);
	}
}

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> h[i][j];

	memset(l, 0x3f, sizeof l);
	for (int i = 1; i <= m; ++i)
		l[n][i] = r[n][i] = i;
	for (int i = 1; i <= m; ++i)
		if (!vis[1][i])
			dfs(1, i);
	// for (int i = 1; i <= n; ++i, cout << '\n')
		// for (int j = 1; j <= m; ++j) cout << l[i][j] << ',' << r[i][j] << ' ';
	int cnt = 0;
	for (int i = 1; i <= m; ++i) {
		if (!vis[n][i])
			++cnt;
	}
	if (cnt) cout << 0 << '\n' << cnt << '\n';
	else {
		cnt = 0;
		int left = 1;
		while (left <= m) {
			int maxr = 0;
			for (int i = 1; i <= m; ++i)
				if (l[1][i] <= left)
					maxr = max(maxr, r[1][i]);
			++cnt;
			left = maxr + 1;
		}
		cout << 1 << '\n' << cnt << '\n';
	}
	return 0;
}