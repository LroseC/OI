#include <cctype>
#include <cstdio>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInput
{
	template<typename T>
	FastStreamInput& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f;
		return *this;
	}
} cin;
struct FastStreamOutput
{
	FastStreamOutput& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FastStreamOutput& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FastStreamOutput& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} cout;

LL n, x;

LL calc(LL a, LL b)
{
	if (!a) return -b;
	if (!b) return -a;
	if (a > b) {
		LL k = a / b;
		return 2 * k * b + calc(b, a % b);
	}
	else {
		LL k = b / a;
		return 2 * k * a + calc(a, b % a);
	}
}

int main(void)
{
	cin >> n >> x;
	LL res = n;
	cout << res + calc(n - x, x) << endl;
	return 0;
}