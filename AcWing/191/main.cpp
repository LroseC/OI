#include <cstdio>
#include <cstring>

using namespace std;

const int N = 370;

int n;
int rain[N][4][4];
bool vis[N][3][3][7][7][7][7];
int gox[] = {0, 0, 0, 0, 0, 1, -1, 2, -2};
int goy[] = {0, 1, -1, 2, -2, 0, 0, 0 ,0};
int goxx[] = {0, 0, 1, 1};
int goyy[] = {0, 1, 0, 1};

bool check(int, int, int);
bool dfs(int lim, int dep, int x, int y, int s0, int s1, int s2, int s3);

int main()
{
    while (scanf("%d", &n), n) {
        memset(rain, 0, sizeof rain);
        memset(vis, 0, sizeof vis);
        for (int tmp = 1; tmp <= n; ++tmp)
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j) scanf("%d", &rain[tmp][i][j]);
        printf("%d\n", dfs(n, 1, 1, 1, 1, 1, 1, 1));
    }

    return 0;
}
bool check(int day, int x, int y)
{
    for (int k = 0; k < 4; ++k) {
        int xx = x + goxx[k];
        int yy = y + goyy[k];
        if (rain[day][xx][yy]) return 0;
    }
    return 1;
}
bool dfs(int lim, int dep, int x, int y, int s0, int s1, int s2, int s3)
{
    if (x == 0 && y == 0) s0 = 0;
    if (x == 0 && y == 2) s1 = 0;
    if (x == 2 && y == 0) s2 = 0;
    if (x == 2 && y == 2) s3 = 0;
    if (s0 >= 7 || s1 >= 7 || s2 >= 7 || s3 >= 7) return 0;
    if (!check(dep, x, y)) return 0;
    if (vis[dep][x][y][s0][s1][s2][s3]) return 0;
    if (lim == dep) return 1;
    vis[dep][x][y][s0][s1][s2][s3] = 1;

    for (int i = 0; i < 9; ++i) {
        int xx = x + gox[i];
        int yy = y + goy[i];
        if (xx < 0 || yy < 0 || xx >= 3 || yy >= 3) continue;
        if (dfs(lim, dep + 1, xx, yy, s0 + 1, s1 + 1, s2 + 1, s3 + 1)) return 1;
    }
    return 0;
}
