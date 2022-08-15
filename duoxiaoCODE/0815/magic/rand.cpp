#include <cstdio>
#include <random>

int n = 300, m = 18;

int main(void)
{
	printf("%d %d\n", n, m);
	for (int i = 0; i < n; ++i) putchar((rand() & 1) + '0');
	putchar('\n');
	return 0;
}
