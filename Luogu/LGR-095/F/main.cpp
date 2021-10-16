#include <cctype>
#include <cstdio>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10;

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

int n, x;
int a[N];

int main(void)
{
	n = read(), x = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	int q = read();
	while (q--) {
		LL res = 0;
		int l = read(), r = read();
		for (int i = l; i <= r; ++i)
			for (int j = i + 1; j <= r; ++j) {
				if ((a[i] ^ a[j]) <= x)
					++res;
			}
		write(res);
	}
	return 0;
}