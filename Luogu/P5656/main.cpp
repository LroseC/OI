#include <cctype>
#include <cstdio>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
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

int T;

int exgcd(int a, int b, int &x, int &y)
{
	if (!b) { x = 1, y = 0; return a; }
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x; return d;
}

int main(void)
{
	T = read();
	while (T--) {
		int minx, miny, maxx, maxy;
		int a = read(), b = read(), c = read();
		int x, y; int d = exgcd(a, b, x, y);
		if (c % d) puts("-1");
		else {
			printf("x = %d, y = %d\n", x, y);
			int minx, miny, maxx, maxy;
			int dx = b / d, dy = a / d;
			int timex = -x / dx + 1;
			int timey = -y / dy + 1;
			minx = (x + dx * timex) * (c / d); maxy = (y - dy * timex) * (c / d);
			miny = (y + dy * timey) * (c / d); maxx = (x - dx * timey) * (c / d);
			if (maxy <= 0 || maxx <= 0) {
				write(minx, ' ');
				write(miny);
			}
			else {
				write(minx, ' ');
				write(miny, ' ');
				write(maxx, ' ');
				write(maxy);
			}
		}
	}
	return 0;
}