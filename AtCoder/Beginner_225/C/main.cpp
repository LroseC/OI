#include <cstdio>

using namespace std;

int n, m;

int tmp[100];

int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int t;
			scanf("%d", &t);
			if (i != 1 && t != tmp[j] + 7) {
				puts("No");
				return 0;
			}
			tmp[j] = t;
			if (j != 1 && (tmp[j] - 1) % 7 != (tmp[j - 1] - 1) % 7 + 1) {
				puts("No");
				return 0;
			}
		}
	}
	puts("Yes");
	return 0;
}