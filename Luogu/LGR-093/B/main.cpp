#include <cstdio>
#include <cctype>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}
template <typename T>
inline void write(T x, char end = '\n')
{
	static char buf[20];
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	int p = -1;
	while (x) { buf[++p] = x % 10 + '0'; x /= 10; }
	while (~p) { putchar(buf[p]); --p; }
	putchar(end);
}

int main(void)
{
	int T = read();
	while (T--) {
		int n = read(), m = read(), k = read();
		if (1ll * n * m % k) puts("NO");
		else {
			puts("YES");
			for (int i = 0; i < n; ++i, puts("")) {
				if (i & 1)
					for (int j = 0; j < m; ++j)
						write((i * m + j) / k + 1, ' ');
				else
					for (int j = m - 1; j >= 0; --j)
						write((i * m + j) / k + 1, ' ');
			}
		}
	}
	return 0;
}