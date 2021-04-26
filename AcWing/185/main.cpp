#include <cstdio>
#include <cstring>

using namespace std;

int n;
int g[5][7], bg[5][5][7];
int cnt[11], bcnt[5][11];
bool st[5][7];
struct PII
{
	int x, y, opt;
}path[10];

inline void swap(int &a, int &b) { int t = a; a = b; b = t; }
void move(int, int, int);
bool dfs(int);

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < 5; ++i) {
		int t, y = 0;
		while (scanf("%d", &t), t) {
			g[i][y++] = t;
			++cnt[t];
			++cnt[0];
		}
	}

	if (dfs(0)) {
		for (int i = 0; i < n; ++i) printf("%d %d %d\n", path[i].x, path[i].y, path[i].opt);
	} else puts("-1");

	return 0;
}
bool dfs(int dep)
{
	if (dep == n) return !cnt[0];
	for (int i = 1; i <= 10; ++i)
		if (cnt[i] == 1 || cnt[i] == 2) return 0;

	memcpy(bg[dep], g, sizeof bg[dep]);
	memcpy(bcnt[dep], cnt, sizeof bcnt[dep]);
	for (int x = 0; x < 5; ++x)
		for (int y = 0; y < 7; ++y)
			if (g[x][y]) {
				int nx = x + 1;
				if (nx < 5) {
					path[dep] = {x, y, 1};
					move(x, y, nx);
					if (dfs(dep + 1)) return 1;
					memcpy(g, bg[dep], sizeof g);
					memcpy(cnt, bcnt[dep], sizeof cnt);
				}
				nx = x - 1;
				if (!g[nx][y] && nx >= 0) {
					path[dep] = {x, y, - 1};
					move(x, y, nx);
					if (dfs(dep + 1)) return 1;
					memcpy(g, bg[dep], sizeof g);
					memcpy(cnt, bcnt[dep], sizeof cnt);
				}
			}
	return 0;
}
void move(int a, int b, int c)
{
	swap(g[a][b], g[c][b]);
	
	while (1) {
		for (int x = 0; x < 5; ++x) {
			int z = 0;
			for (int y = 0; y < 7; ++y)
				if (g[x][y]) g[x][z++] = g[x][y];
			while (z < 7) g[x][z++] = 0;
		}
	
		memset(st, 0, sizeof st);
		bool flag = 1;
		for (int x = 0; x < 5; ++x)
			for (int y = 0; y < 7; ++y)
				if (!st[x][y] && g[x][y]) {
					int l, r; l = r = y;
					while (l - 1 >= 0 && g[x][l - 1] == g[x][y]) --l;
					while (r + 1 < 7 && g[x][r + 1] == g[x][y]) ++r;
					if (r - l + 1 >= 3) {
						st[x][y] = 1;
						flag = 0;
						continue;
					}
	
					l = r = x;
					while (l - 1 >= 0 && g[l - 1][y] == g[x][y]) --l;
					while (r + 1 < 5 && g[r + 1][y] == g[x][y]) ++r;
					if (r - l + 1 >= 3) {
						st[x][y] = 1;
						flag = 0;
					}
				}
		if (flag) return;
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 7; ++j)
				if (st[i][j]) {
					--cnt[0];
					--cnt[g[i][j]];
					g[i][j] = 0;
				}
	}
}
