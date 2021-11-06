#include <vector>
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

int n, a;
vector<int> num;
LL f[60][3000];

int main(void)
{
	io >> n >> a;
	num.resize(n + 1);
	for (int i = 1; i <= n; ++i) {
		io >> num[i];
		num[i] -= a;
	}
	f[0][1500] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = -1300; j <= 1300; ++j) {
			f[i][j + 1500] += f[i - 1][j + 1500];
			f[i][j + 1500] += f[i - 1][j - num[i] + 1500];
		}
	io << f[n][1500] - 1 << endl;
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	return 0;
}