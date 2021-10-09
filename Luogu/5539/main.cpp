#include <cctype>
#include <cstdio>
#include <cstring>

using namespace std;

typedef unsigned long long ULL;
const int N = 1e9 + 10;
inline ULL lowbit(ULL x) { return x & -x; }

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
	static char buf[100]; int p = -1;
	if (x == 0) putchar('0');
	if (x < 0) { putchar('-'); x = -x; }
	while (x) { buf[++p] = x % 10; x /= 10; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}
template<typename T>
inline void write2(T x, char end = '\n')
{
	static char buf[130]; int p = -1;
	while (x) { buf[++p] = x & 1; x >>= 1; }
	while (~p) { putchar(buf[p] + '0'); --p; } putchar(end);
}

inline int count(ULL x)
{
	int res = 0;
	while (x) {
		++res;
		x -= lowbit(x);
	}
	return res;
}

int n, m, S;
ULL val[(N >> 6) + 10];

void insert(int x)
{
	if (x < 64) {
	static ULL tmp[70];
		memset(tmp, 0, sizeof tmp);
		for (int i = 0; i < (x << 6); i += x)
			tmp[i >> 6] |= 1ull << (i & 63);
		for (int i = 0; i <= m; i += x)
			for (int j = 0; j < x && i + j <= m; ++j)
				val[i + j] |= tmp[j];
	}
	else {
		for (int i = 0; i <= n; i += x)
			val[i >> 6] |= 1ull << (i & 63);
	}
}
int query(void)
{
	--m; int res = 0;
	if ((n & 63) != 63) val[m] &= (1ull << (n + 1 - (m << 6))) - 1;
	val[0] &= -2ull;
	for (int i = 0; i <= m; ++i) res += count(val[i] & (val[i] << 1) & (val[i] << 2));
	for (int i = 1; i <= m; ++i) res += count(val[i] & (val[i - 1] >> 62) & ((val[i - 1] >> 63) | (val[i] << 1)));
	return res;
}

int main(void)
{
	n = read(), S = read();
	m = (n >> 6) + 1;
	while (S--) insert(read());
	write(query());
	return 0;
}