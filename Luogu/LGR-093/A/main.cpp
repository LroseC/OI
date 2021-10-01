#include <cctype>
#include <cstdio>
#include <cstdlib>

using namespace std;
typedef long long LL;

inline LL read(void)
{
	LL res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template<typename T>
inline void write(T x)
{
	static char buf[50];
	int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; }
}
inline void swap(LL &a, LL &b) { LL t = b; b = a; a = t; }
inline LL min(LL a, LL b) { return a < b ? a : b; }
inline LL abst(LL x) { return x < 0 ? -x : x; }

int gox[] = {0, 0, 1, -1};
int goy[] = {1, -1, 0, 0};

LL solve(LL a, LL b, LL c, LL d)
{
	LL dx = abst(a - c), dy = abst(b - d);
	if (dx < dy) swap(dx, dy);
	LL res = dy;
	dx -= dy;
	res += dx;
	return res * 2;
}

signed main(void)
{
	int T = read();
	while (T--) {
		LL a = read(), b = read(), c = read(), d = read();
		LL dx = abst(a - c), dy = abst(b - d);
		LL ans = 0x3f3f3f3f3f3f3f3f;
		if ((dx & 1) != (dy & 1))
			for (int i = 0; i < 4; ++i)
				ans = min(ans, solve(a, b, c + gox[i], d + goy[i]) + 1);
		else ans = solve(a, b, c, d);
		write(ans);
		putchar('\n');
	}
	return 0;
}