#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
const int M = 1 << 16;
typedef long long LL;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int k;
int n;
int coin[20];
int c[N];
LL sumc[N];
int f[M];
LL g[M];

inline void Print(int x)
{
	for (int i = 0; i < k; ++i)
		if (x >> i & 1) putchar('1');
		else putchar('0');
}

LL getval(int x)
{
	LL res = 0;
	for (int i = 0; i < k; ++i)
		if (x >> i & 1) res += coin[i];
	return res;
}

void dp(int state)
{
	if (~f[state]) return;
	f[state] = 0;
	for (int t = 0; t < k; ++t) {
		if (state >> t & 1) {
			int j = state ^ (1 << t);
			dp(j);
			LL val = coin[t];

			int l = f[j], r = n, mid;
			while (l < r) {
				mid = l + r + 1 >> 1;
				if (sumc[mid] - sumc[f[j]] <= val) l = mid;
				else r = mid - 1;
			}


			if (l > f[state]) {
				f[state] = l;
				g[state] = g[j] + (l == f[j]) * val;
			}
			if (l == f[state]) g[state] = max(g[state], g[j] + (l == f[j]) * val);
		}
	}
}

int main(void)
{
	memset(f, -1, sizeof f);
	k = read(), n = read();
	for (int i = 0; i < k; ++i) coin[i] = read();
	for (int i = 1; i <= n; ++i) {
		c[i] = read();
		sumc[i] = sumc[i - 1] + c[i];
	}
	f[0] = g[0] = 0;
	dp((1 << k) - 1);
	#ifdef DEBUG
	int all_state = (1 << k) - 1;
	for (int state = all_state, flag = 1; flag; state = (state - 1) & all_state) {
		if (!state) flag = 0;
		printf("f["); Print(state); printf("] = %d\n", f[state]);
	}
	#endif
	printf("%lld\n", f[(1 << k) - 1] == n ? g[(1 << k) - 1] : -1);
	return 0;
}