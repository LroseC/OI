#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;
using LL = long long;
using PII = pair<int, int>;
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

int n;
int base[20], w[20];

void insert(int num, int weight)
{
	for (int i = n - 1; i >= 0; --i)
		if (num >> i & 1) {
			if (!base[i]) {
				base[i] = num;
				w[i] = weight;
				return;
			}
			if (weight <= w[i]) {
				swap(num, base[i]);
				swap(weight, w[i]);
			}
			num ^= base[i];
		}
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	IO >> n;
	for (int i = 1; i < 1 << n; ++i) {
		int w;
		IO >> w;
		insert(i, w);
	}
	LL ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += w[i];
	}
	printf("%lld\n", ans);
	return 0;
}
