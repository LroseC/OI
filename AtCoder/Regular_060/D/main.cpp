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

LL n, s;
vector<LL> num;

// n 在 b 进制下每一位的和为 s

LL f(LL b, LL n)
{
	if (n < b) return n;
	return f(b, n / b) + (n % b);
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	io >> n >> s;
	if (s > n) {
		puts("-1");
		return 0;
	}
	if (s == n) {
		io << n + 1 << endl;
		return 0;
	}
	vector<LL> nums;
	for (int b = 2; 1ll * (b - 1) * (b - 1) <= n - s; ++b)
		if ((n - s) % (b - 1) == 0) {
			nums.emplace_back((n - s) / (b - 1) + 1);
			if (f(b, n) == s) {
				io << b << endl;
				return 0;
			}
		}
	for (int i = nums.size() - 1; i >= 0; --i) {
		LL b = nums[i];
		if (f(b, n) == s) {
			io << b << endl;
			return 0;
		}
	}
	io << -1 << endl;
	return 0;
}