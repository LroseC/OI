#include <cctype>
#include <cstdio>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInputOutput
{
	using FSIO = FastStreamInputOutput;
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
	FSIO& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FSIO& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FSIO& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} io;

LL n;

LL getsum(LL a, LL b)
{
	return (a + b) * (b - a + 1) / 2;
}

int main(void)
{
	io >> n;
	LL ans = 0;
	for (int a = 1; 1ll * a * a * a <= n; ++a) {
		LL t = n / a;
		for (int l = a, r; 1ll * l * l <= t; l = r + 1) {
			r = t / (t / l);
			while (1ll * r * r > t) --r;
			ans += 1ll * (r - l + 1) * (t / l) - getsum(l - 1, r - 1);
		}
	}
	io << ans << endl;
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}