#include <cstdio>
#include <iostream>

using namespace std;

const int N = 5;

int T;
char g[N][N];
char pur[N][N] = 
{
	{1, 1, 1, 1, 1},
	{0, 1, 1, 1, 1},
	{0, 0, '*' - '0', 1, 1},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0}
};
int gox[] = {-2, -1, 1, 2, 2, -1, 1, -2};
int goy[] = {1, 2, 2, 1, -1, -2, -2, -1};

inline void swap(char &a, char &b) { char t = a; a = b; b = t; }
int f(void);
bool dfs(int lim, int dep, int x, int y);

int main()
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) pur[i][j] += '0';

	scanf("%d\n", &T);
	while (T--) {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j) cin >> g[i][j];

		int x, y;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (g[i][j] == '*') {
					x = i, y = j;
					break;
				}

//		printf("%d\n", f());
		int dep = 0;
		while (dep <= 15 && !dfs(dep, 0, x, y)) ++dep;
		printf("%d\n", dep > 15 ? -1 : dep);
	}

	return 0;
}
int f(void)
{
	int res = 0;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) res += (i == 2 && j == 2) ? 0 : pur[i][j] != g[i][j];

	return res;
}
bool dfs(int lim, int dep, int x, int y)
{
//	for (int i = 0; i < N; ++i)
//		for (int j = 0; j < N; ++j) printf("%c%c", g[i][j], j == 4 ? '\n' : ' ');
//	putchar('\n');
	int ff = f();
	if (lim == dep && !ff) return 1;
	if (dep + ff > lim) return 0;
	for (int i = 0; i < 8; ++i) {
		int xx = x + gox[i], yy = y + goy[i];
		if (xx < 0 || yy < 0 || x >= N || y >= N) continue;
		swap(g[xx][yy], g[x][y]);
		if (dfs(lim, dep + 1, xx, yy)) return 1;
		swap(g[x][y], g[xx][yy]);
	}

	return 0;
}
/*
2
10110
01*11
10111
01001
00000

01011
110*1
01110
01010
00100
*/
