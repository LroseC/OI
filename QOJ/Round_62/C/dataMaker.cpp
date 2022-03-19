#include <cstdio>
#include <random>

int n = 300, m = 1000;

int G[310][310];

int myrand(int l, int r) { return rand() % (r - l + 1) + l; }

int main(void)
{
	printf("%d %d\n", n, m);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		do u = myrand(1, n), v = myrand(1, n);
		while (G[u][v]);
		G[u][v] = G[v][u] = 1;
		printf("%d %d\n", u, v);
	}
	return 0;
}
