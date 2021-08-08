#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 510;

struct PII
{
	int x, y;
};

int n, m, cur;
char map[N][N];
int f[N][N];
queue<PII> q[2];
int gox[] = {1, -1, 0, 0};
int goy[] = {0, 0, 1, -1};

void bfs(void)
{
//	puts("???");
//	for (int i = 1; i <= n; ++i)
//		for (int j = 1; j <= m; ++j)
//			printf("%2d%c", f[i][j], j == m ? '\n' : ' ');
//	puts("...");
	while (q[cur ^ 1].size()) q[cur ^ 1].pop();
	while (q[cur].size()) {
		PII now = q[cur].front(); q[cur].pop();
		int x = now.x, y = now.y;
		for (int i = 0; i < 4; ++i) {
			int xx = x + gox[i], yy = y + goy[i];
//			printf("x = %d, y = %d : xx = %d, yy = %d\n", x, y, xx, yy);
			if (xx <= 0 || yy <= 0 || xx > n || yy > m) continue;
			if (f[xx][yy] <= f[x][y] && f[xx][yy] != -1) continue;
			if (map[xx][yy] == '#')
				for (int dx = -1; dx <= 1; ++dx)
					for (int dy = -1; dy <= 1; ++dy) {
						int xxx = xx + dx, yyy = yy + dy;
						if (xxx <= 0 || yyy <= 0 || xxx > n || yyy > m) continue;
						if (f[xxx][yyy] <= f[x][y] + 1 && f[xxx][yyy] != -1) continue;
						q[cur ^ 1].push({xxx, yyy}), f[xxx][yyy] = f[x][y] + 1;
					}
			if (map[xx][yy] == '.') f[xx][yy] = f[x][y], q[cur].push({xx, yy});
		}
	}
	cur ^= 1;
}

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%s", map[i] + 1);
	memset(f, -1, sizeof f);
	q[0].push({1, 1});
	f[1][1] = 0;
	while (f[n][m] == -1) bfs();
//	for (int i = 1; i <= n; ++i)
//		for (int j = 1; j <= m; ++j)
//			printf("%2d%c", f[i][j], j == m ? '\n' : ' ');
	printf("%d\n", f[n][m]);
	return 0;
}
