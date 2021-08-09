#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 180000, M = N * 2 + 7, MOD = 20110520;

int n, m, end_x, end_y;
int g[110][110], q[2][N], cnt[2];
int h[2][M], v[2][M];

int find(int cur, int x)
{
	int t = x % M;
	while (h[cur][t] != -1 && h[cur][t] != x)
		if ( ++ t == M)
			t = 0;
	return t;
}

void insert(int cur, int x, int w)
{
	int t = find(cur, x);
	if (h[cur][t] == -1)
	{
		h[cur][t] = x, v[cur][t] = w;
		q[cur][ ++ cnt[cur]] = t;
	}
	else v[cur][t] = (v[cur][t] + w) % MOD;
}

int get(int state, int k)
{
	return state >> k * 2 & 3;
}

int set(int k, int v)
{
	return v * (1 << k * 2);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ )
	{
		char str[110];
		scanf("%s", str + 1);
		for (int j = 1; j <= m; j ++ )
			if (str[j] == '_')
			{
				g[i][j] = 1;
				end_x = i, end_y = j;
			}
	}

	if (n < m)
	{
		swap(n, m);
		swap(end_x, end_y);
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j < i; j ++ )
				swap(g[i][j], g[j][i]);
	}

	int res = 0;
	memset(h, -1, sizeof h);
	int cur = 0;
	insert(cur, 0, 1);

	for (int i = 1; i <= n; i ++ )
	{
		for (int j = 1; j <= cnt[cur]; j ++ )
			h[cur][q[cur][j]] <<= 2;
		for (int j = 1; j <= m; j ++ )
		{
			int last = cur;
			cur ^= 1, cnt[cur] = 0;
			memset(h[cur], -1, sizeof h[cur]);
			for (int k = 1; k <= cnt[last]; k ++ )
			{
				int state = h[last][q[last][k]], w = v[last][q[last][k]];

				int x = get(state, j - 1), y = get(state, j);
				if (!g[i][j] && (!x && !y)) insert(cur, state, w);
				else if (!x && !y)
				{
					if (g[i][j + 1] && g[i + 1][j]) insert(cur, state + set(j - 1, 2) + set(j, 2), w);
					if (g[i][j + 1]) insert(cur, state + set(j, 1), w);
					if (g[i + 1][j]) insert(cur, state + set(j - 1, 1), w);
				}
				else if (x == 1 && !y)
				{
					if (g[i + 1][j]) insert(cur, state + set(j - 1, 1), w);
					if (g[i][j + 1]) insert(cur, state - set(j - 1, 1) + set(j, 1), w);
				}
				else if (!x && y == 1)
				{
					if (g[i][j + 1]) insert(cur, state + set(j, 1), w);
					if (g[i + 1][j]) insert(cur, state + set(j - 1, 1) - set(j, 1), w);
				}
				else if (x == 1 && y == 1)
				{
					if (i == end_x && j == end_y) res = (res + w) % MOD;
					insert(cur, state - set(j - 1, x) - set(j, y), w);
				}
				else if (x == 2 && !y)
				{
					if (i == end_x && j == end_y) res = (res + w) % MOD;
					insert(cur, state - set(j - 1, x), w);
					if (g[i][j + 1]) insert(cur, state - set(j - 1, x) + set(j, x), w);
				}
				else if (!x && y == 2)
				{
					if (i == end_x && j == end_y) res = (res + w) % MOD;
					insert(cur, state - set(j, y), w);
					if (g[i + 1][j]) insert(cur, state + set(j - 1, y) - set(j, y), w);
				}
			}
		}
	}

	printf("%d\n", res);

	return 0;
}