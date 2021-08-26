#include <cstdio>

using namespace std;

const int N = 40;

int n;
int a[N][N];

int main(void)
{
	scanf("%d", &n);
	int x = 1, y = n / 2 + 1;
	for (int i = 1; i <= n * n; ++i) {
		a[x][y] = i;
		if (x == 1 && y == n) ++x;
		else if (x == 1) ++y, x = n;
		else if (y == n) --x, y = 1;
		else if (a[x - 1][y + 1]) ++x;
		else --x, ++y;
	}
	for (int i = 1; i <= n; ++i, puts(""))
		for (int j = 1; j <= n; ++j) {
			printf("%d ", a[i][j]);
		}
	return 0;
}