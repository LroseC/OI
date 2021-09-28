#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

#define int long long
const int N = 1e4 + 10, M = 510;

inline int lowbit(int x) { return x & -x; }
inline int read(void)
{
	int res = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
	return res * f;
}

int n, m;
int ans = 0;
int h[N];
int f[N][M];
int tr[M][5010];

void add(int k, int x, int j)
{
	for (int i = k; i < 5010; i += lowbit(i)) tr[j][i] = max(tr[j][i], x);
}
int query(int k, int j)
{
	int res = 0;
	for (int i = k; i; i -= lowbit(i)) res = max(res, tr[j][i]);
	return res;
}

/*
状态表示：f[j][i] 表示以第 i 个玉米为终点，操作 j 次能获得的最长上升子序列长度
*/

void Solve(void)
{
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= m; ++j) {
			f[i][j] = query(h[i], j) + 1;
			if (j != 0)
				f[i][j] = max(f[i][j], query(h[i] + 1, j - 1) + 1);
			add(h[i], f[i][j], j);
			ans = max(ans, f[i][j]);
		}
}

signed main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) h[i] = read();
	int tmp = 0;
	for (int i = 1; i < n; ++i)
		tmp += max(0ll, h[i] - h[i + 1]);
	if (tmp <= m) {
		printf("%lld\n", n);
		return 0;
	}
	Solve();
	printf("%lld\n", ans);
	return 0;
}