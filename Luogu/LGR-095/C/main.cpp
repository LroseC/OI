#include <cctype>
#include <cstdio>

using namespace std;

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

int main(void)
{
	int n = read();
	if (n < 9) puts("-1");
	else {
		write(n);
		for (int i = 2; i <= 7; ++i) {
			write(i, ' ');
			write(i - 1);
		}
		for (int i = 8; i <= n; ++i) {
			write(i, ' ');
			write(3);
		}
	}
	return 0;
}