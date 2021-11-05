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
LL a[N];
LL f[N];
LL c[N];
LL minx[N];
vector<LL> len;
vector<LL> na;

void Solve(LL x, LL times)
{
	if (x <= na[0]) {
		c[0] += times;
		c[x + 1] -= times;
	}
	else {
		int t = upper_bound(na.begin(), na.end(), x) - na.begin() - 1;
		f[t] += x / na[t] * times;
		Solve(x % na[t], times);
	}
}

int main(void)
{
	int on;
	io >> n >> q;
	on = n;
	int start = 1;
	for (int i = 1; i <= q; ++i) {
		io >> a[i];
		if (a[i] < n) {
			n = a[i];
			start = i + 1;
		}
	}
	minx[q] = q;
	for (int i = q - 1; i >= 1; --i) {
		if (a[i] < a[minx[i + 1]])
			minx[i] = i;
		else minx[i] = minx[i + 1];
	}
	na.emplace_back(n);
	for (int i = start, j; i <= q; i = j + 1) {
		j = minx[i];
		na.emplace_back(a[j]);
	}
	f[na.size() - 1] = 1;
	for (int i = na.size() - 1; i >= 1; --i) {
		f[i - 1] += na[i] / na[i - 1] * f[i];
		Solve(na[i] % na[i - 1], f[i]);
	}
	c[0] += f[0]; c[n + 1] -= f[0];
	for (int i = 1; i <= on; ++i) {
		c[i] += c[i - 1];
		io << c[i] << endl;
	}
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}