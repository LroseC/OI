#include <set>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int N = 1e5 + 10;
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

int n, m;
LL maxx;
LL h[N], p[N], a[N], sword[N];

LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }
LL lcm(LL a, LL b) { return a * (b / gcd(a, b)); }
LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if (!b) { x = 1; y = 0; return a; }
	LL d = exgcd(b, a % b, y, x);
	y -= (a / b * x); return d;
}
LL ExCRT(void)
{
	LL t = 0, M = 1, x, y, d;
	for (int i = 1; i <= n; ++i) {
		d = exgcd(a[i] * M, p[i], x, y);
		if ((h[i] - a[i] * t) % d) return -1;
		x = x * (h[i] - a[i] * t) / d;
		t += x * M; M = lcm(M, (p[i] / gcd(p[i], a[i])));
		t = (t % M + M) % M;
	}
	return t < maxx ? t + M * ((maxx - t - 1) / M + 1) : t;
}

int main(void)
{
	int T = read();
	while (T--) {
		n = read(), m = read(), maxx = 0;

		for (int i = 1; i <= n; ++i) h[i] = read();
		for (int i = 1; i <= n; ++i) p[i] = read();
		for (int i = 1; i <= n; ++i) sword[i] = read();

		multiset<LL> tmp;
		for (int i = 1; i <= m; ++i) tmp.insert(read());
		for (int i = 1; i <= n; ++i) {
			auto it = tmp.upper_bound(h[i]);
			if (it != tmp.begin()) --it;
			a[i] = *it; tmp.erase(it); tmp.insert(sword[i]);
			maxx = max(maxx, ((h[i] - 1) / a[i] + 1)); h[i] %= p[i];
		}

		write(ExCRT());
	}
	return 0;
}