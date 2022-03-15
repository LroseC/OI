#include <cctype>
#include <cstdio>

using namespace std;

const int N = 1e8 + 10;

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

int n, q;
bool vis[N];
int prime[N], idx;

inline void shai(void)
{
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) prime[++idx] = i;
		for (int j = 1; j <= idx && i * prime[j] <= n; ++j) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

int main(void)
{
	n = read(), q = read();
	shai();
	while (q--) write(prime[read()]);
	return 0;
}