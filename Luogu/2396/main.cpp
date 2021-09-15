/*
要开 O2 多交几发就过了
*/
#include <cctype>
#include <cstdio>
#include <iostream>

using namespace std;

#define reg register
const int mod = 1e9 + 7;
inline int lowbit(int x) { return x & -x; }

inline int read(void)
{
	reg int res = 0, f = 1; reg char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n, m;
int endstate;
int a[100];
int stop[20];
int f[1 << 24];
int dis[1 << 24];
int d[1 << 24];

void Print(int x)
{
	for (int i = 0; i < n; ++i)
		if (x >> i & 1) putchar('1');
		else putchar('0');
}

int main(void)
{
	n = read();
	for (reg int i = 0; i < n; ++i)
		d[1 << i] = read();
	m = read();
	for (reg int i = 0; i < m; ++i)
		stop[i] = read();
	endstate = (1 << n) - 1;

	f[0] = 1;

	for (reg int state = 1; state < 1 << n; ++state) {
		// printf("state = "), Print(x), putchar('\n');
		for (reg int k = state, t; k; k -= t) {
			bool fail = 0;
			t = lowbit(k);
			if (!dis[state]) dis[state] = dis[state ^ t] + d[t];
			for (int i = 0; i < m; ++i)
				if (dis[state] == stop[i]) {
					fail = 1;
					break;
				}
			if (fail == 1) break;
			f[state] += f[state ^ t];
			f[state] %= mod;
		}
	}
	printf("%d\n", f[endstate]);
	return 0;
}