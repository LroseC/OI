#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 180000, M = N * 2 + 7, MOD = 20110520;

int n, m;
int q[2][N], cnt[2];
int h[2][M], v[2][M];
int g[120][120], edx, edy;

int find(int cur, int x)
{
	int t = x % M;
	while (h[cur][t] != -1 && h[cur][t] != x)
		if (++t == M)
			t =  0;
	return t;
}
void insert(int cur, int x, int w)
{
	int t = find(cur, x);
	if (h[cur][t] == -1) {
		h[cur][t] = x, v[cur][t] = w;
		q[cur][++cnt[cur]] = t;
	}
	else v[cur][t] = (v[cur][t] + w) % MOD;
}

int get(int state, int k)
{
	return state >> k * 2 & 3;
}
int set(int v, int k)
{
	return v << k * 2;
}

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		char str[110];
		scanf("%s", str + 1);
		for (int j = 1; j <= m; ++j)
			if (str[j] == '_') {
				g[i][j] = 1;
				edx = i, edy = j;
			}
	}

	if (n < m) {
		swap(n, m);
		swap(edx, edy);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j < i; ++j)
				swap(g[i][j], g[j][i]);
	}

	int cur = 0, res = 0;
	memset(h, -1, sizeof h);
	insert(cur, 0, 1);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= cnt[cur]; ++j)
			h[cur][q[cur][j]] <<= 2;
		
		for (int j = 1; j <= m; ++j) {
			int last = cur;
			cur ^= 1; cnt[cur] = 0;
			memset(h[cur], -1, sizeof h[cur]);
			for (int k = 1; k <= cnt[last]; ++k) {
				int state = h[last][q[last][k]], w = v[last][q[last][k]];
				int x = get(state, j - 1), y = get(state, j);
				if (!g[i][j] && (!x && !y)) insert(cur, state, w);
				else if (!x && !y) {
					if (g[i][j + 1] && g[i + 1][j]) insert(cur, state + set(2, j - 1) + set(2, j), w);
					if (g[i][j + 1]) insert(cur, state + set(1, j), w);
					if (g[i + 1][j]) insert(cur, state + set(1, j - 1), w);
				}
				else if (x == 1 && !y) {
					if (g[i + 1][j]) insert(cur, state + set(1, j - 1), w);
					if (g[i][j + 1]) insert(cur, state - set(1, j - 1) + set(1, j), w);
				}
				else if (!x && y == 1) {
					if (g[i][j + 1]) insert(cur, state + set(1, j), w);
					if (g[i + 1][j]) insert(cur, state - set(1, j) + set(1, j - 1), w);
				}
				else if (x == 1 && y == 1) {
					if (i == edx && j == edy) res = (res + w) % MOD;
					insert(cur, state - set(x, j - 1) - set(y, j), w);
				}
				else if (x == 2 && !y) {
					if (i == edx && j == edy) res = (res + w) % MOD;
					insert(cur, state - set(x, j - 1), w);
					if(g[i][j + 1]) insert(cur, state - set(x, j - 1) + set(x, j), w);
				}
				else if (!x && y == 2) {
					if (i == edx && j == edy) res = (res + w) % MOD;
					insert(cur, state - set(y , j), w);
					if (g[i + 1][j]) insert(cur, state - set(y, j) + set(y, j - 1), w);
				}
			}
		}
	}
	printf("%d\n", res);
	return 0;
}