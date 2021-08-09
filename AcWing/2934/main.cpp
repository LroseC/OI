#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 5e4, M = N * 2 + 19;

int n, m, edx, edy;
int g[50][50];
int h[2][M], q[2][M], cnt[2];
LL v[2][M];

int find(int cur, int state)
{
	int i = state % M;
	while (h[cur][i] != -1 && h[cur][i] != state) {
		++i;
		if (i == M) i = 0;
	}
	return i;
}
void insert(int cur, int state, LL w)
{
	int t = find(cur, state);
	if (h[cur][t] == -1) {
		q[cur][++cnt[cur]] = t;
		h[cur][t] = state;
		v[cur][t] = w;
	}
	else v[cur][t] += w;
}

int get(int state, int k)
{
	return state >> k * 2 & 3;
}
int set(int v, int k)
{
	return (v << k * 2);
}

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		char str[20];
		scanf("%s", str + 1);
		for (int j = 1; j <= m; ++j)
			if (str[j] == '.') {
				g[i][j] = 1;
				edx = i, edy = j;
			}
	}

	LL res = 0;	
	memset(h, -1, sizeof h);
	int cur = 0;
	insert(cur, 0, 1);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= cnt[cur]; ++j)
			h[cur][q[cur][j]] <<= 2;
		for (int j = 1; j <= m; ++j) {
			int last = cur;
			cur ^= 1;
			cnt[cur] = 0;
			memset(h[cur], -1, sizeof h[cur]);
			for (int k = 1; k <= cnt[last]; ++k) {
				int state = h[last][q[last][k]];
				LL w = v[last][q[last][k]];
				int a = get(state, j - 1), b = get(state, j);
				if (!g[i][j] && (!a && !b)) {
					insert(cur, state, w);
				}
				else if (!a && !b) {
					if (g[i + 1][j] && g[i][j + 1])
						insert(cur, state + set(1, j - 1) + set(2, j), w);
				}
				else if (!a && b) {
					if (g[i + 1][j]) insert(cur, state - set(b, j) + set(b, j - 1), w);
					if (g[i][j + 1]) insert(cur, state, w);
				}
				else if (a && !b) {
					if (g[i + 1][j]) insert(cur, state, w);
					if (g[i][j + 1]) insert(cur, state - set(a, j - 1) + set(a, j), w);
				}
				else if (a == 1 && b == 1) {
					for (int s = 1, l = j + 1; ; ++l) {
						int tmp = get(state, l);
						if (tmp == 2) {
							if (--s == 0) {
								insert(cur, state - set(1, l) - set(a, j - 1) - set(b, j), w);
								break;
							}
						}
						else if (tmp == 1) ++s;
					}
				}
				else if (a == 2 && b == 2) {
					for (int s = 1, r = j - 2; ; --r) {
						int tmp = get(state, r);
						if (tmp == 1) {
							if (--s == 0) {
								insert(cur, state + set(1, r) - set(a, j - 1) - set(b, j), w);
								break;
							}
						}
						else if (tmp == 2) ++s;
					}
				}
				else if (a == 2 && b == 1) {
					insert(cur, state - set(a, j - 1) - set(b, j), w);
				}
				else if (i == edx && j == edy) {
					res += w;
				}
			}
		}
	}
	printf("%lld\n", res);
}