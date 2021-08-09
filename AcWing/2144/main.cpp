#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 130, M = 307;

int n, m;
int g[N][N], q[2][M];
int h[2][M], v[2][M], cnt[2];

int find(int cur, int state)
{
	int t = state % M;
	while (h[cur][t] != -1 && h[cur][t] != state)
		if (++t == M)
			t = 0;
	return t;
}
void insert(int cur, int state, int val)
{
	int t = find(cur, state);
	if (h[cur][t] == -1) {
		h[cur][t] = state, v[cur][t] = val;
		q[cur][++cnt[cur]] = t;
	}
	else v[cur][t] = max(v[cur][t], val);
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
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> g[i][j];

	memset(h, -1, sizeof h);
	int cur = 0, res = -1e8;
	insert(cur, 0, 0);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= cnt[cur]; ++j)
			h[cur][q[cur][j]] <<= 2;
		for (int j = 1; j <= m; ++j) {
			int last = cur;
			cur ^= 1, cnt[cur] = 0;
			memset(h[cur], -1, sizeof h[cur]);
			for (int k = 1; k <= cnt[last]; ++k) {
				int state = h[last][q[last][k]], w = v[last][q[last][k]];
				int x = get(state, j - 1), y = get(state, j);
				if (!x && !y) {
					insert(cur, state, w);
					if (i < n && j < m)
						insert(cur, state + set(1, j - 1) + set(2, j), w + g[i][j]);
				}
				if (!x && y) {
					if (j < m) insert(cur, state, w + g[i][j]);
					if (i < n) insert(cur, state + set(y, j - 1) - set(y, j), w + g[i][j]);
				}
				if (x && !y) {
					if (i < n) insert(cur, state, w + g[i][j]);
					if (j < m) insert(cur, state - set(x, j - 1) + set(x, j), w + g[i][j]);
				}
				if (x == 1 && y == 1) {
					for (int s = 1, l = j + 1; ; ++l) {
						int t = get(state, l);
						if (t == 1) ++s;
						else if (t == 2)
							if (--s == 0) {
								insert(cur, state - set(x, j - 1) - set(y, j) - set(1, l), w + g[i][j]);
								break;
							}
					}
				}
				if (x == 2 && y == 2) {
					for (int s = 1, r = j - 2; ; --r) {
						int t = get(state, r);
						if (t == 2) ++s;
						else if (t == 1)
							if (--s == 0) {
								insert(cur, state - set(x, j - 1) - set(y, j) + set(1, r), w + g[i][j]);
								break;
							}
					}
				}
				if (x == 2 && y == 1) insert(cur, state - set(x, j - 1) - set(y, j), w + g[i][j]);
				if (x == 1 && y == 2)
					res = max(res, w + g[i][j]);
			}
		}
	}
	printf("%d\n", res);
	return 0;
}