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

const int N = 5010;
const int mod = 1e9 + 7;

int n, len;
char str[N];
/*
f[i][j] means that all the state which do i operation and there is j difference
*/
int f[N][N];

int main(void)
{
	io >> n;
	scanf("%s", str + 1);
	len = strlen(str + 1);
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= i; ++j) {
			f[i][j] = (f[i - 1][max(0, j - 1)] + f[i - 1][j + 1] * 2ll % mod) % mod;
		}
	printf("%d\n", f[n][len]);
	return 0;
}