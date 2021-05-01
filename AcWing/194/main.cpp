#include <cstdio>
#include <cstring>

using namespace std;

#define reg register
#define ll long long
const int N = 10;

int n;
int g[N][N];
int vis[N][N];
int unvis[N];
int gox[] = {+1, -1, +0, -0};
int goy[] = {-0, +0, -1, +1};

void draw(int x, int y, int c);
bool fill(int);
int f(void);
bool dfs(int lim, int dep);

int main()
{
	while (scanf("%d", &n), n) {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) scanf("%d", &g[i][j]);

		memset(vis, 0, sizeof vis);
		draw(0, 0, g[0][0]);
		int dep = 0;
		while (!dfs(dep, 0)) ++dep;
		printf("%d\n", dep);
	}

	return 0;
}
int f(void)
{
	memset(unvis, 0, sizeof unvis);
	int ans = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (vis[i][j] != 1)
				ans += unvis[g[i][j]] ^ 1, unvis[g[i][j]] = 1;
	return ans;
}
void draw(int x, int y, int c)
{
	vis[x][y] = 1;
	for (int i = 0; i < 4; ++i) {
		int xx = x + gox[i], yy = y + goy[i];
		if (!vis[xx][yy] && (xx >= 0 && yy >= 0 && xx < n && yy < n)) {
//			printf("xx:%d,yy:%d,gxxyy:%d,c:%d\n", xx, yy, g[xx][yy], c);
			if (g[xx][yy] == c) draw(xx, yy, c);
			else vis[xx][yy] = 2;
		}
	}
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j)
//			printf("%d ", vis[i][j]);
//		putchar('\n');
//	}
}
bool fill(int c)
{
	bool flag = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (g[i][j] == c && vis[i][j] == 2) draw(i, j, c), flag = 1;
	return flag;
}
bool dfs(int lim, int dep)
{
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j)
//			printf("%d ", vis[i][j]);
//		putchar('\n');
//	}
//	printf("%d!\n", f());
	if (lim == dep && f() == 0) return 1;
	if (f() + dep > lim) return 0;
	int bvis[N][N];
	memcpy(bvis, vis, sizeof bvis);
	for (int c = 0; c < 6; ++c) {
		if (fill(c) && dfs(lim, dep + 1)) return 1;
		memcpy(vis, bvis, sizeof vis);
	}
	return 0;
}
