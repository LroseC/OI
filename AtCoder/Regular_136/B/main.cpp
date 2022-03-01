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
} IO;

const int N = 5010;

int n;
int a[N], b[N];

void Operate(int pos)
{
	int x = a[pos], y = a[pos + 1], z = a[pos + 2];
	a[pos] = z, a[pos + 1] = x, a[pos + 2] = y;
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n;
	for (int i = 1; i <= n; ++i)
		IO >> a[i];
	for (int i = 1; i <= n; ++i)
		IO >> b[i];
	for (int i = 1; i <= n - 2; ++i) {
		int pos = 0;
		for (int j = i; j <= n; ++j)
			if (b[i] == b[j]) {
				pos = j;
				break;
			}
		if (!pos) {
			puts("No");
			return 0;
		}
		while (pos - i > 2)
			Operate(pos - 2);
		for (int k = 0; k < 3; ++k)
			if (a[i] != b[i]) Operate(i);
		if (a[i] != b[i]) {
			puts("No");
			return 0;
		}
	}
	if (b[n] != a[n] || b[n - 1] != a[n - 1]) {
		puts("No");
		return 0;
	}
	puts("Yes");
	return 0;
}
