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

int n, k;

int main(void)
{
	io >> n >> k;
	LL res = 0;
	for (int i = 1, j; i <= min(n, k); i = j + 1) {
		j = min(min(n, k), k / (k / i));
		res = res + 1ll * (j - i + 1) * k - 1ll * (i + j) * (j - i + 1) / 2 * (k / i);
	}
	if (n > k)
		res = res + 1ll * (n - k) * k;
	printf("%lld\n", res);
	return 0;
}
