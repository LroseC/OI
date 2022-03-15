#include <queue>
#include <cctype>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 5010;

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

int n, m;
int G[N][N];

inline void Prim(void)
{
	dis[1] = 0;
	for (int i = 1; i < n; ++i) {
		
	}
}

int main(void)
{
	n = read(), m = read();
	memset(G, 0x3f, sizeof G);
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		G[u][v] = min(G[u][v], w);
	}
	Prim();
	printf("%lld\n", ans);
	return 0;
}