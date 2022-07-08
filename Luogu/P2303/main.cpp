#include <cctype>
#include <cstdio>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

i64 calc(i64 x)
{
	i64 res = x;
	for (int i = 2; 1ll * i * i <= x; ++i)
		if (x % i == 0) {
			res = res / i * (i - 1);
			while (x % i == 0) x /= i;
		}
	if (x != 1) res = res / x * (x - 1);
	return res;
}

int main(void)
{
	i64 n;
	read >> n;
	i64 res = 0;
	for (int i = 1; 1ll * i * i <= n; ++i) {
		if (n % i == 0) {
			res += 1ll * i * calc(n / i);
			if (1ll * i * i != n)
				res += 1ll * (n / i) * calc(i);
		}
	}
	printf("%lld\n", res);
	return 0;
}
