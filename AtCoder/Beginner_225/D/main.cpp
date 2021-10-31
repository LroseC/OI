#include <cstdio>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int pre[N], nex[N];

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		pre[i] = nex[i] = 0;
	}
	for (int i = 1; i <= m; ++i) {
		int op, x, y, res;
		scanf("%d", &op);
		switch (op) {
			case 1:
				scanf("%d%d", &x, &y);
				nex[x] = y;
				pre[y] = x;
				break;
			case 2:
				scanf("%d%d", &x, &y);
				nex[x] = 0;
				pre[y] = 0;
				break;
			case 3:
				scanf("%d", &x);
				res = 1;
				while (pre[x]) x = pre[x];
				y = x;
				while (nex[y]) {
					++res;
					y = nex[y];
				}
				printf("%d ", res);
				while (nex[x]) {
					printf("%d ", x);
					x = nex[x];
				}
				printf("%d\n", x);
				break;
		}
	}
	return 0;
}