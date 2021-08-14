#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int T;
int n, m;
char str[1000010];

int main(void)
{
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		scanf("%s", str + 1);
		if (n >= m || n == 1) puts("-1");
		else {
			for (int i = 1; i < n; ++i) putchar('0');
			putchar('1');
			putchar('0');
			for (int i = n + 2; i <= m; ++i) putchar('1');
			putchar('\n');
		}
	}
}