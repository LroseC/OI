#include <cstdio>

using namespace std;

#define int long long
#define ll long long


void exgcd(int a, int b, int &x, int &y)
{
	if (!b) {
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
	return;
}


signed main()
{
	ll a, b, x, y;
	scanf("%lld%lld", &a, &b);
	exgcd(a, b, x, y);
	printf("%lld\n", x < 0 ? x + b : x % b);
	return 0;
}
