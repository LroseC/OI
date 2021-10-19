#include <cctype>
#include <cstdio>

using namespace std;

typedef long long LL;

template<typename T = int>
inline T read(void)
{
	T res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

struct Query
{
	LL l, r;
};

int T;
Query q[(int)5e4 + 10];

namespace pts30
{
	int fib[] = {1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903};
	int val[(int)1e7 + 10];
	inline bool check(void)
	{
		for (int i = 1; i <= T; ++i)
			if (q[i].l > 1e7 || q[i].r > 1e7)
				return 0;
		return 1;
	}
	int Getval(int x)
	{
		int res = 0;
		for (int i = 45; i; --i) {
			if (x >= fib[i]) {
				x -= fib[i];
				res ^= fib[i];
			}
		}
		return res;
	}
	inline int main(void)
	{
		for (int i = 1; i <= 1e7; ++i)
			val[i] = Getval(i);
		for (int i = 1; i <= 1e7; ++i)
			val[i] ^= val[i - 1];
		for (int i = 1; i <= T; ++i)
			write(val[q[i].r] ^ val[q[i].l - 1]);
		return 0;
	}
}

int main(void)
{
	T = read();
	for (int i = 1; i <= T; ++i)
		q[i].l = read<LL>(), q[i].r = read<LL>();
	if (pts30::check()) pts30::main();
	return 0;
}