#include <bits/stdc++.h>

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

const int N = 1e5 + 10;

int n;
int a[N];

bool check(int x, int y)
{
	if (x == n)
		return (a[x] - y) & 1;
	if (a[x + 1] > y)
		return check(x + 1, y + 1);
	if (a[x + 1] <= y) {
		if ((a[x] - y) & 1) return 1;
		if ((a[x + 1] >= y) && !check(x + 1, y)) return 1;
		return 0;
	}
}

int main(void)
{
	io >> n;
	for (int i = 1; i <= n; ++i) io >> a[i];
	sort(a + 1, a + 1 + n, greater<int>());
	puts(check(1, 1) ? "First" : "Second");
	return 0;
}