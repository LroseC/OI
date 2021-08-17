#include <cstdio>

using namespace std;

typedef long long LL;

int phi(int x)
{
	int ans = x;
	for (int i = 2; 1ll * i * i <= x; ++i)
		if (x % i == 0) {
			ans = ans / i * (i - 1);
			while (x % i == 0) x /= i;
		}
	if (x != 1) ans = ans / x * (x - 1);
	return ans;
}

int main(void)
{
	int n;
	scanf("%d", &n);
	LL res = 0;
	for (int d = 1; 1ll * d * d <= n; ++d)
		if (n % d == 0) {
			res += 1ll * d * phi(n / d);
			if (d * d != n) res += 1ll * (n / d) * phi(d);
		}
	printf("%lld\n", res);
	return 0;
}