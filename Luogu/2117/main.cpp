#include <cstdio>

using namespace std;

int n, q;
int res;

int main(void)
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			int x; scanf("%d", &x);
			if (i == j) res ^= x;
		}
	for (int i = 1; i <= q; ++i) {
		int op, x;
		scanf("%d", &op);
		if (op == 1 || op == 2) {
			scanf("%d", &x);
			res ^= 1;
		}
		else printf("%d", res);
	}
	return 0;
}