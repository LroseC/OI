#include <cstdio>
using namespace std;

typedef long long LL;

int main(void)
{
	LL n; scanf("%lld", &n);
	for (int i = 1; 1ll * i * i <= n; ++i) {
		printf("%lld ", 1ll * i * i);
	}
	return 0;
}