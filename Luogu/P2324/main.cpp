#include <cstdio>
#include <iostream>

using namespace std;

const char pur[5][5] = 
{
	{'1', '1', '1', '1', '1'},
	{'0', '1', '1', '1', '1'},
	{'0', '0', '*', '1', '1'},
	{'0', '0', '0', '0', '1'},
	{'0', '0', '0', '0', '0'}
};

int T;
int G[5][5];
int gox[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int goy[] = {1, 2, 2, 1, -1, -2, -2, -1};

int h(void)
{
	int res = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			res += (pur[i][j] != '*' && pur[i][j] != G[i][j]);
	return res;
}

bool IDA_star(int dep, int limit)
{
	int tmp = h();
	if (!tmp) return 1;
	if (dep + tmp > limit) return 0;
	int x, y;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			if (G[i][j] == '*')
				x = i, y = j;
	for (int i = 0; i < 8; ++i) {
		int xx = x + gox[i];
		int yy = y + goy[i];
		if (xx < 0 || yy < 0 || xx > 4 || yy > 4) continue;
		swap(G[x][y], G[xx][yy]);
		// for (int i = 0; i < 5; ++i, putchar('\n'))
		// 	for (int j = 0; j < 5; ++j) putchar(G[i][j]);
		if (IDA_star(dep + 1, limit)) return 1;
		swap(G[x][y], G[xx][yy]);
	}
	return 0;
}

int main(void)
{
	scanf("%d", &T);
	while (T--) {
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j) {
				do G[i][j] = getchar();
				while (G[i][j] != '0' && G[i][j] != '1' && G[i][j] != '*');
			}

		int depth = 0;
		while (depth <= 15 && !IDA_star(0, depth)) ++depth;
		printf("%d\n", depth > 15 ? -1 : depth);
	}
	return 0;
}