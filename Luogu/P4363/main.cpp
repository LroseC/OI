#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

// #define DEBUG
const int INF = 0x3f3f3f3f;
inline int lowbit(int x) { return x & -x; }
inline int get_cnt(int x)
{
	int res = 0;
	while (x) { ++res; x -= lowbit(x); }
	return res;
}

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n, m;
int f[1 << 20];
bool vis[1 << 20];
int g[1 << 20];
int a[12][12];
int b[12][12];

void Print(int x)
{
	for (int i = 0; i < n + m; ++i)
		if (x >> i & 1) putchar('1');
		else putchar('0');
}

int dp(int state)
{
	if (vis[state]) return f[state];
	vis[state] = 1;
	int tot = 0;
	for (int i = 0, h = n; i < n + m; ++i) {
		if (state >> i & 1) --h;
		else tot += h;
	}
	g[state] = tot;

	if (tot & 1) f[state] = INF;
	else f[state] = -INF;

	for (int i = 0, r = n, c = -1, last = 2; i < n + m; ++i) {
		if (state >> i & 1) {
			last = 1;
			--r;
		}
		else {
			++c;
			if (last == 1) {
				int statep = state ^ (1 << i) ^ (1 << i - 1);
				dp(statep);
				if (tot & 1) f[state] = min(f[state], f[statep] - b[r][c]);
				else f[state] = max(f[state], f[statep] + a[r][c]);
				#ifdef DEBUG
				if (state == 20) {
					printf("f["), Print(state), printf("] = %d\n", f[state]);
					printf("statep = "), Print(statep), putchar('\n');
					printf("f["), Print(statep), printf("] = %d\n", f[statep]);
					printf("tot = %d\n", tot);
				}
				#endif
			}
			last = 0;
		}
	}
	return f[state];
}

int main(void)
{
	n = read(), m = read();
	memset(f, -1, sizeof f);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			a[i][j] = read();
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			b[i][j] = read();

	f[((1 << n) - 1) << m] = 0;
	vis[((1 << n) - 1) << m] = 1;
	printf("%d\n", dp((1 << n) - 1));

	#ifdef DEBUG
	for (int i = 0; i < 1 << n + m; ++i) {
		if (get_cnt(i) == n) printf("f["), Print(i), printf("] = %d\n", f[i]);
	}
	#endif
	return 0;
}