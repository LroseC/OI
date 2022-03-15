#include <cstdio>
#include <cstdlib>

using namespace std;

#define int __int128

int n;
int a1, m1, a2, m2;
int x, lcm, t, k, d;

inline int abst(int a) { return a < 0 ? -a : a; }
inline int mod(int a, int b) { int t = a % b; return t < 0 ? t + b : t; }
int exgcd(int, int, int&, int&);

signed main()
{
	scanf("%lld", &n);
	scanf("%lld%lld", &a1, &m1);
	x = m1;
	lcm = a1;
	for (int i = 1; i < n; ++i) {
		scanf("%lld%lld", &a2, &m2);
		d = exgcd(lcm, a2, t, k);
		if ((m2 - x) % d) {
			puts("-1");
			return 0;
		}
		t = mod(t * (m2 - x) / d, abst(a2 / d));
		x = x + t * lcm;
		lcm = lcm * a2 / d;
		x = (x % lcm + lcm) % lcm;
	}
	printf("%lld\n", (long long) ((x % lcm + lcm) % lcm));

	return 0;
}
int exgcd(int a, int b, int &x, int &y)
{
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, x, y);
	int z = x; x = y; y = z - y * (a / b);
	return d;
}