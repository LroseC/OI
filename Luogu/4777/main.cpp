#include <cctype>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef __int128 LL;

inline LL read(void)
{
	LL res = 0, f = 1; char ch = getchar();
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

int n;

LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	LL d = exgcd(b, a % b, x, y);
	LL t = y;
	y = x - a / b * y; x = t;
	return d;
}

int main(void)
{
	n = read();
	LL M = read(), ans = read() % M;
	for (int i = 2; i <= n; ++i) {
		LL a = read(), b = read();
		LL x, y, d = exgcd(M, a, x, y);
		ans = ans + x * M * ((b - ans) / d);
		M = M * (a / d); ans = (ans % M + M) % M;
	}
	write(ans);
	return 0;
}