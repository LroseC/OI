#include <cmath>
#include <cctype>
#include <cstdio>

using namespace std;

typedef long long LL;

inline LL sq(LL x) { return x * x; }
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
	if (x == '0') { putchar('0'); }
	if (x < '0') { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

signed main(void)
{
	int T = read();
	while (T--) {
		LL n = read(), m = read();
		bool seccess = 0;
		for (int i = 1; i * i <= n; ++i) {
			if (n % i) continue;
			if (2ll * (i + n / i + 2) <= m) {
				puts("Good");
				seccess = 1;
				break;
			}
		}
		if (!seccess) puts("Miss");
	}
	return 0;
}