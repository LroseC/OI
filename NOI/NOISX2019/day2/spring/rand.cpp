#include <bits/stdc++.h>

int n = 2e5;

inline int myrand(int l, int r)
{
	return rand() % (r - l + 1) + l;
}

int main(void)
{
	printf("%d\n", n);
	for (int i = 1; i <= n; ++i)
		printf("%d ", rand());
	puts("");
	for (int i = 2; i <= n; ++i)
		printf("%d ",  i - 1);
	puts("");
	return 0;
}
