#include <cctype>
#include <cstdio>

using namespace std;

typedef long long LL;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
void write(T x, char end = '\n')
{
	static char buf[50]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

int s[50];

LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if (!b) { x = 1, y = 0; return a; }
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x; return d;
}

int main(void)
{
	int n = read(), m = read();
	for (int i = 1; i <= m; ++i) s[i] = read();
	int p[10];
	int a[4] = {0, 0, 1, 2};
	LL ans = 0;
	for (p[1] = 1; p[1] <= m; ++p[1])
		for (p[2] = 1; p[2] <= m; ++p[2])
			for (p[3] = 1; p[3] <= m; ++p[3]) {
				bool fail = 0;
				LL t = 0, M = 1;
				for (int i = 1; i <= 3; ++i) {
					LL x, y;
					LL d = exgcd(M, p[i], x, y);
					if ((a[i] - t) % d) { fail = 1; break; }
					t += 1ll * x * M;
					M = 1ll * M * (p[i] / d);
					t = (t % M + M) % M;
				}
				if (fail) continue;
				ans += ((n - t) / M) - ((3 - t - 1) / M + 1) + 1;
			}
	printf("%lld\n", ans);
	return 0;
}