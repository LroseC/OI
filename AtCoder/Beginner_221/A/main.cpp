#include <cstdio>

using namespace std;

typedef long long LL;

int main(void)
{
	int a, b;
	scanf("%d%d", &a, &b);
	LL res = 1;
	for (int i = 1; i <= (a - b); ++i) res = res * 32;
	printf("%lld\n", res);
	return 0;
}