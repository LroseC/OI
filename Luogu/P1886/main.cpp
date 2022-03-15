#include <cctype>
#include <cstdio>

using namespace std;

const int N = 1e6 + 10;

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

int n, k;
int a[N];
int q[N];

int main(void)
{
	n = read(), k = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	int hh = 0, tt = -1;
	for (int i = 1; i <= n; ++i) {
		while (hh <= tt && i - q[hh] >= k) ++hh;
		while (hh <= tt && a[q[tt]] >= a[i]) --tt;
		q[++tt] = i;
		if (i >= k) write(a[q[hh]], i == n ? '\n' : ' ');
	}
	hh = 0, tt = -1;
	for (int i = 1; i <= n; ++i) {
		while (hh <= tt && i - q[hh] >= k) ++hh;
		while (hh <= tt && a[q[tt]] <= a[i]) --tt;
		q[++tt] = i;
		if (i >= k) write(a[q[hh]], i == n ? '\n' : ' ');
	}
	return 0;
}