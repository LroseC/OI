#include <cctype>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;
const int N = 3e6 + 10, L = 22;

inline LL read(void)
{
	LL res = 0, f = 1; char ch = getchar();
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

/*
思路：倍增优化
f[i][j] 表示先跳过第 i 个跳棋，总共跳过 2^j 个跳棋要求在的区间
接着我发现这个方法会 MLE，而且很可能 TLE（因为最后两个点时限卡的紧）
所以我决定打完暴力不打了。。。 
*/

LL pos[N];
int ans[N];
PLL f[N][L];

int dfs(int x0, int now)
{
	if (ans[x0] != -1) return ans[x0];
	int tmp = 2 * pos[now] - x0;
	if (tmp <= pos[now - 1]) return (ans[x0] = 0);
	else return (ans[x0] = dfs(tmp, now - 1) + 1);
}

int main(void)
{
	int n = read(), m = read();
	for (int i = 1; i <= n; ++i) pos[i] = read();
	pos[0] = LLONG_MIN;
	pos[n + 1] = LLONG_MAX;
	memset(ans, -1, sizeof ans);
	while (m--) {
		if (pos[n] <= 2e5 + 10) {
			LL x0 = read();
			int now = 0;
			bool fail = 0;
			now = upper_bound(pos, pos + n + 1, x0) - pos - 1;
			if (fail) continue;
			if (x0 >= N) puts("0");
			else {
				int res = 0;
				write(dfs(x0, now));
			}
		}
		else {
			LL x0 = read();
			int now = 0;
			bool fail = 0;
			for (int i = 1; i <= n; ++i) {
				if (x0 == pos[i]) {
					puts("0");
					fail = 1;
					break;
				}
				if (x0 > pos[i] && x0 < pos[i + 1]) now = i;
			}
			if (fail) continue;
			int ans = 0;
			for (int i = now; i; --i) {
				if ((x0 = 2 * pos[i] - x0) <= pos[i - 1]) break;
				++ans;
			}
			write(ans);
		}
	}
	return 0;
}