#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

const int N = 16010, M = 110;

struct Node
{
	int l, p, s;
	bool operator<(const Node &b) const
	{
		return s < b.s;
	}
};

int n, m;
Node peo[M];
int q[N];
int f[M][N];

/*
状态表示：f[i][j] 表示前 i 个粉刷匠粉刷了前 j 块木板的所有方案的集合
状态性质：报酬 MAX
状态计算：f[i][j] = max(f[i - 1][j], f[i][j - 1], for (k = j - 1 - l[i]; k < s[i]; ++k) f[i - 1][k] + (j - k) * p[i])
注意到，当 j 从小到大枚举时，f[i - 1][k] + (j - k) * p[i] 的相对大小关系不变，故我们可以使用单调队列优化 dp
*/

int main(void)
{
	cin >> n >> m;
	for (int i = 1; i <= m; ++i)
		cin >> peo[i].l >> peo[i].p >> peo[i].s;
	sort(peo + 1, peo + 1 + m);

	for (int i = 1; i <= m; ++i) {
		int hh = 0, tt = -1;
		for (int j = 0; j <= n; ++j) {
			f[i][j] = f[i - 1][j];
			if (j) f[i][j] = max(f[i][j], f[i][j - 1]);

			int l = peo[i].l, p = peo[i].p, s = peo[i].s;
			if (hh <= tt && q[hh] < j - l) ++hh;
			if (hh <= tt && j >= s) {
				int k = q[hh];
				f[i][j] = max(f[i][j], f[i - 1][k] + (j - k) * p);
			}
			if (j < s) {
				while (hh <= tt && f[i - 1][j] - j * p >= f[i - 1][q[tt]] - q[tt] * p) --tt;
				q[++tt] = j;
			}
		}
	}
	printf("%d\n", f[m][n]);
	return 0;
}
