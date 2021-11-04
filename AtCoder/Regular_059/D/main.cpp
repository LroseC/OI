#include <cctype>
#include <cstdio>
#include <cstring>
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

char a[(int)1e5 + 10];

int main(void)
{
	scanf("%s", a + 1);
	int n = strlen(a + 1);
	for (int i = 2; i <= n; ++i) {
		if (a[i] == a[i - 1]) {
			io << i - 1 << ' ' << i << endl;
			return 0;
		}
		if (i > 2 && a[i] == a[i - 2]) {
			io << i - 2 << ' ' << i << endl;
			return 0;
		}
	}
	puts("-1 -1");
	return 0;
}