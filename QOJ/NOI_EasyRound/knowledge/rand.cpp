#include <cstdio>

int main(void)
{
	printf("%d\n", int(3e3));
	for (int i = 1; i <= 3e3; ++i)
		printf("%d ", int(3e3));
	puts("");
	return 0;
}
