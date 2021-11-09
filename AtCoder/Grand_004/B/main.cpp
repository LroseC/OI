#include <cctype>
#include <cstdio>
#include <algorithm>

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

const int N = 2010;

int n, X;
LL a[N];
LL w[N];

int main(void)
{
	io >> n >> X;
	for (int i = 0; i < n; ++i) {
		io >> a[i];
		w[i] = a[i];
	}
	LL ans = 0x3f3f3f3f3f3f3f3f;
	for (int i = 0; i <= n; ++i) {
		LL res = 1ll * i * X;
		for (int j = 0; j < n; ++j)
			w[j] = min(w[j], a[(j - i + n) % n]);
		for (int j = 0; j < n; ++j)
			res += w[j];
		ans = min(ans, res);
	}
	printf("%lld\n", ans);
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}