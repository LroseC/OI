#include <cmath>
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

int a, b;
LL f[20][20];

void init(void)
{
	for (int i = 0; i < 10; ++i) f[1][i] = 1;
	for (int i = 2; i < 20; ++i)
		for (int j = 0; j < 10; ++j)
			for (int k = 0; k < 10; ++k)
				if (abs(k - j) >= 2)
					f[i][j] += f[i - 1][k];
}
LL calc(int x)
{
	static int digit[20]; int p = 0;
	while (x) { digit[++p] = x % 10; x /= 10; }
	LL res = 0;
	for (int i = 1; i < p; ++i)
		for (int j = 1; j < 10; ++j) res += f[i][j];
	for (int j = 1; j < digit[p]; ++j) res += f[p][j];
	for (int i = p - 1; i > 0; --i) {
		for (int j = 0; j < digit[i]; ++j)
			if (abs(digit[i + 1] - j) >= 2) {
				res += f[i][j];
			}
		if (abs(digit[i + 1] - digit[i]) < 2) break;
	}
	return res;
}

int main(void)
{
	init();
	io >> a >> b;
	printf("%lld\n", calc(b + 1) - calc(a));
	return 0;
}