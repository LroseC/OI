#include <cctype>
#include <cstdio>
#include <cstdlib>

using namespace std;

/*
主要思路：容斥原理
*/

typedef long long LL;

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

int main(void)
{
	int T = read();
	while (T--) {
		LL n = read(); int p = read();
		if (p == 1) { puts("0"); continue; }
		__int128 tmp = 1;
		LL res = 0;
		for (int i = 1; tmp <= n && tmp > 0; ++i, tmp = tmp * p) {
			res += ((i & 1) ? 1 : -1) * (n / tmp);
		}
		write(res);
	}
	return 0;
}