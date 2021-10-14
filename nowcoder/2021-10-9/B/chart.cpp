#include <cstdio>

using namespace std;

int n;

int xishu[200][200];

int main(void)
{
	scanf("%d", &n);
	xishu[1][1] = 1;
	for (int i = 1; i <= n; ++i) {
		printf("i = %d\n", i);
		for (int j = 1; j <= i; ++j) printf("xishu[%d] = %d\n", j, xishu[i][j]);
		puts("");
		for (int j = 1; j <= i; ++j) {
			if (i & 1) {
				xishu[i + 1][j] += xishu[i][j];
				xishu[i + 1][j + 1] += xishu[i][j];
			}
			else {
				xishu[i + 1][j] += xishu[i][j];
				xishu[i + 1][j + 1] -= xishu[i][j];
			}
		}
	}
	return 0;
}
