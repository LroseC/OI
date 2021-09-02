#include <cstring>
#include <iostream>

using namespace std;

#define x first
#define y second
const int N = 110, M = 16;
typedef pair<int, int> PII;

int n, m, t;
char G[N][N];
int f[N][N][M];
PII S, T;
int gox[] = {-1, 0, 1, 0};
int goy[] = {0, 1, 0, -1};

inline int read(void)
{
	int res = 0; char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) {
		res = res * 10 + (ch ^ '0');
		ch = getchar();
	}
	return res;
}
inline void write(int x)
{
	if (!x) putchar('0');
	static char buf[20];
	int p = -1;
	while (x) { buf[++p] = x % 10 ^ '0'; x /= 10; }
	while (p >= 0) putchar(buf[p]), --p;
}

int dp(int x, int y, int t)
{
	if (t < 0) return 0;
	if (~f[x][y][t]) return f[x][y][t];
	f[x][y][t] = 0;
	for (int i = 0; i < 4; ++i) {
		int xx = x + gox[i];
		int yy = y + goy[i];
		if (xx < 1 || yy < 1 || xx > n || yy > m) continue;
		if (G[xx][yy] == '*') continue;
		f[x][y][t] += dp(xx, yy, t - 1);
	}
	return f[x][y][t];
}

int main(void)
{
	memset(f, -1, sizeof f);
	n = read(), m = read(), t = read();
	for (int i = 1; i <= n; ++i)
		scanf("%s", G[i] + 1);
	S.x = read(), S.y = read();
	T.x = read(), T.y = read();
	f[T.x][T.y][0] = 1;
	write(dp(S.x, S.y, t));
	putchar('\n');
	return 0;
}