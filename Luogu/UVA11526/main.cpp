#include <cctype>
#include <cstdio>

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

LL f(int x)
{
	LL res = 0;
	for (LL i = 1, j; i <= x; i = j + 1) {
		j = x / (x / i);
		res += 1ll * (j - i + 1) * (x / i);
	}
	return res;
}

int main(void)
{
	int T; io >> T;
	while (T--) {
		int x; io >> x;
		printf("%lld\n", f(x));
	}
	return 0;
}
