#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

#define violent
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
int tr[M][5510];

void add(int x, int y, int val)
{
	for (int i = x; i < M; i += lowbit(i))
		for (int j = y; j < 5510; j += lowbit(j)) tr[i][j] = max(tr[i][j], val);
}
int query(int x, int y)
{
	int res = 0;
	for (int i = x; i; i -= lowbit(i))
		for (int j = y; j; j -= lowbit(j)) res = max(res, tr[i][j]);
	return res;
}
/*
状态表示: f[j][i] 表示以第 i 个玉米为终点，操作 j 次能获得的最长上升子序列长度
状态计算: f[i][j] =
for (int ni = 1; ni < i; ++i) {
	if (h[ni] <= h[i])
		f[i][j] = max(f[i][j], f[ni][j] + 1);
	if (j && h[ni] <= h[i] + 1) f[i][j] = max(f[i][j], f[ni][j - 1] + 1)
}
*/

signed main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) h[i] = read();
	for (int i = 1; i <= n; ++i)
		for (int j = m; j >= 0; --j)
			add(j + 1, h[i] + j, f[i][j] = query(j + 1, h[i] + j) + 1);
	printf("%d\n", query(m + 1, 5500));
	return 0;
}