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

const int N = 1e6;
using i64 = long long;

int n;
int A[N + 10];
i64 cnt[N];

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n;
	for (int i = 1; i <= n; ++i) {
		IO >> A[i];
		++cnt[A[i]];
	}
	for (int t = 1; t < 1e6; t = t * 10)
		for (int i = 0; i < 1e6; i += 10 * t)
			for (int j = 0; j < t; ++j)
				for (int k = 1; k < 10; ++k)
					cnt[i + j + k * t] += cnt[i + j + (k - 1) * t];

	i64 res = 0;
	for (int i = 1; i <= n; ++i) {
		int complement = 0;
		bool flag = 1;
		for (int t = 1; t < 1e6; t = t * 10) {
			int now = 9 - A[i] / t % 10;
			if (now < A[i] / t % 10) flag = 0;
			complement += t * now;
		}
		res += cnt[complement] - flag;
	}
	printf("%lld\n", res / 2);
	return 0;
}
