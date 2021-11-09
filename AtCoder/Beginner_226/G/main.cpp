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

int T;
LL a[10], b[10];

void carry(int y, int x)
{
	LL c = min(a[x], b[y]);
	a[x] -= c;
	b[y] -= c;
	b[y - x] += c;
}

int main(void)
{
	io >> T;
	while (T--) {
		for (int i = 1; i <= 5; ++i) io >> a[i];
		for (int i = 1; i <= 5; ++i) io >> b[i];
		carry(5, 5);
		carry(4, 4);
		carry(5, 4);
		carry(3, 3);
		carry(5, 3);
		carry(4, 3);
		carry(5, 2);
		carry(4, 2);
		carry(3, 2);
		carry(2, 2);
		carry(5, 1);
		carry(4, 1);
		carry(3, 1);
		carry(2, 1);
		carry(1, 1);
		bool fail = 0;
		for (int i = 1; i <= 5; ++i)
			if (a[i] > 0) {
				puts("No");
				fail = 1; break;
			}
		if (!fail) puts("Yes");
	}
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}