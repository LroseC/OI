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

const int N = 2e3 + 10;
const int mod = 924844033;

int n, k;
int fac[N];

int main(void)
{
	io >> n >> k;
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	return 0;
}