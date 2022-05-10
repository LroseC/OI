#include <cstdio>
#include <random>

int n = 70, V = 800;

inline int myrand(int l, int r)
{ return rand() % (r - l + 1) + l; }

int main(void)
{
	printf("%d %d\n", n, V);
	for (int i = 1; i <= n; ++i)
		printf("%d ", myrand(1, V));
	puts("");
}
