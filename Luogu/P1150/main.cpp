#include <cstdio>
using namespace std;
typedef long long LL;
int main(void)
{
	LL ans = 0;
	int n, k; scanf("%d%d", &n, &k);
	ans += n;
	while (n >= k) {
		ans += n / k;
		n = n % k + n / k;
	}
	printf("%lld\n", ans);
	return 0;
}