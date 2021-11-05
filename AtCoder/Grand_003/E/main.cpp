#include <vector>
#include <cctype>
#include <cstdio>
#include <cstdlib>
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

const int N = 1e5 + 10, M = 17;

int n, q;
LL a[N], top = 1;
LL c[N];
LL f[N];

void Solve(LL x, LL times)
{
	int t = upper_bound(a + 1, a + 1 + top, x) - a - 1;
	if (t == 0) c[0] += times, c[x + 1] -= times;
	else {
		f[t] += x / a[t] * times;
		Solve(x % a[t], times);
	}
}

int main(void)
{
	io >> n >> q;
	a[1] = n;
	while (q--) {
		LL x; io >> x;
		while (top && x <= a[top]) --top;
		a[++top] = x;
	}
	f[top] = 1;
	for (int i = top; i >= 2; --i) {
		f[i - 1] = a[i] / a[i - 1] * f[i];
		Solve(a[i] % a[i - 1], f[i]);
	}
	c[0] += f[1]; c[a[1] + 1] -= f[1];
	for (int i = 1; i <= n; ++i) {
		c[i] += c[i - 1];
		io << c[i] << endl;
	}
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}