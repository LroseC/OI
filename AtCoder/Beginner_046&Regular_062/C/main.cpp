#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} io;

using LL = long long;

int n;
LL a = 1, b = 1;

LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) {
		int x, y; io >> x >> y;
		if (a % x != 0)
			a = a + x - a % x;
		if (a / x * y < b) {
			if (b % y != 0)
				b = b + y - b % y;
			a = b / y * x;
		}
		else {
			b = a / x * y;
		}
	}
	printf("%lld\n", a + b);
	return 0;
}