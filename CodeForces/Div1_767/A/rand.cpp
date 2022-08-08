#include <cstdio>
#include <random>

using i32 = int;

int main(void)
{
	puts("1");
	i32 n = 2e5;
	printf("%d\n", n);
	for (int i = n - 1; i >= 0; --i)
		printf("%d ", 1);
	puts("");
}
